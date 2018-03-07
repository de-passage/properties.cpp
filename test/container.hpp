#include <stddef.h>
#include <iostream>
#include <functional>
#include "properties.hpp"

#include "properties/attribute.hpp"
#include "properties/apply.hpp"
#include "properties/addressable.hpp"

#include <cassert>
#include <iostream>


template<class Functor>
struct ObserveChange {
	template<class T>
	struct value : T {
		using T::operator=;

		//*
		template<class Op, class ...Q>
			constexpr decltype(auto) operator_base(const Op& op, Q&&... v) const {
				return T::operator_base(op, std::forward<Q>(v)...);
			}
		template<class Op, class ...Q>
			constexpr decltype(auto) operator_base(const Op& op, Q&&... v) {
				return T::operator_base(op, std::forward<Q>(v)...);
			}
		//	*/
		template<class Op, class Q, class = pty::meta::enable_for<Op, pty::operators::mutating_bitwise, pty::operators::mutating_arithmetic, pty::operators::assign>>
			constexpr auto operator_base(const Op& op, Q&& v) {
				auto value = T::operator_base(op, v);
				on_change(value);
				return value;
			}
		Functor on_change;

	};
};

#include "properties/incrementable.hpp"

namespace dpsg {
	template<class T, class U>
		constexpr auto max(const T& t, const U& u) -> std::conditional_t<std::is_convertible<U, T>::value, T, U> {
			return t >= u ? std::conditional_t<std::is_convertible<U, T>::value, T, U>(t) : std::conditional_t<std::is_convertible<U, T>::value, T, U>(u);
		}
	template<class T, class U, class ...Args>
		constexpr auto max(const T& t, const U& u, Args... rest) {
			return max(max(t,u), rest...);
		}
}



namespace pty {
	template<class T>
	struct Container : T {

		protected:
		PTY_FORWARD_OPERATOR_BASE(T)
		struct size_change {
			Container* container;
			inline constexpr size_change(const size_change& s) : container(s.container) {}
			inline constexpr size_change(Container* c = nullptr) : container(c) {}

			inline constexpr auto operator()(size_t size) { downcast(container).operator_base(*this, size); }
		};

		struct capacity_change {
			Container* container;
			inline constexpr capacity_change(const capacity_change& s) : container(s.container) {}
			inline constexpr capacity_change(Container* c = nullptr) : container(c) {}
			inline constexpr auto operator()(size_t size) { downcast(container).operator_base(*this, size); }
		};

		constexpr Container() : size(0), capacity(0) {
			size.on_change = size_change(this);
			capacity.on_change = capacity_change(this);
		}

		template<class Op, class = pty::meta::enable_for<Op, Container::size_change, Container::capacity_change>>
		constexpr inline void operator_base(const Op&, size_t) {
		}

		template<class Op, class = pty::meta::enable_for<Op, Container::size_change, Container::capacity_change>>
		constexpr inline void operator_base(const Op&, size_t) const {}

		public:
		pty::Attribute<size_t, Container, pty::ReadWrite, ObserveChange<size_change>::template value> size;
		pty::Attribute<size_t, Container, pty::ReadWrite, ObserveChange<capacity_change>::template value> capacity;

		protected:
		constexpr inline void set_capacity(size_t nc) {
			capacity.value = nc;
		}
		constexpr inline void set_size(size_t nc) {
			size.value = nc;
		}
	};
}


template<class T>
#define BASE pty::Properties<Vector<T>, pty::Container, pty::Addressable>
class Vector : public BASE{

	typedef BASE Base;
#undef BASE

	friend pty::adaptor<Vector>;
	friend pty::adaptor<const Vector>;

	public:

	using Base::capacity;
	using Base::size;
	typedef T Type;
	typedef T* ArrayType;

	constexpr Vector() : _array(nullptr) {}

	constexpr inline void push_back(T&& t) {
        std::cout << " push_back before" << size << " " << capacity << std::endl;
		if(size == capacity) {
			capacity = (capacity + 1) * 2;
		}
        auto tmp = size++;
		_array[tmp] = std::forward<T>(t);
        std::cout << " push_back after" << size << " " << capacity << std::endl;
	}

	constexpr inline T&& pop_back() {
		return std::forward<T>(_array[--size]);
	}

	constexpr void push_front(T&& t) {
		if(size == capacity) {
			// Changing capacity will force a resize. We substitute the array for a nullptr to avoid unnecessary copy
			T* tmp = nullptr;
			std::swap(tmp, _array);
			capacity = (capacity + 1) * 2;

			// at this point _array is a T[capacity], we place the new first element
			_array[0] = std::forward<T>(t);
			// then the old ones in order
			for(size_t i = 0; i < size; ++i)
				_array[i + 1] = std::forward<T>(tmp[i]);
			// adjust the size property to reflect the change and clean up
			delete[] tmp;
			++size;
		}
		else { // No resizing needed, simply copy the elements to the back then insert the new one
			for(int i = size - 1; i >= 0; --i)
				_array[i + 1] = std::forward<T>(_array[i]);
			_array[0] = std::forward<T>(t);
			size++;
		}
	}

	constexpr T&& pop_front() {
		auto& tmp = _array[0];
		for(size_t i = 1; i < size; ++i)
			_array[i - 1] = std::forward<T>(_array[i]);
		size--;
		return std::forward<T>(tmp);
	}

	constexpr inline T& operator[](long int i) {
		return i >= 0 ? _array[i] : _array[size + i];
	}

	constexpr inline const T& operator[](long int i) const {
		return i >= 0 ? _array[i] : _array[size + i];
	}


	private:

	using typename Base::capacity_change;
	using typename Base::size_change;

	PTY_FORWARD_OPERATOR_BASE(Base)

	constexpr inline void operator_base(const size_change&, size_t s) {
      std::cout << " size changed " << s << std::endl << std::flush;
		if(s > capacity) {
			_resize(s);
			Base::set_capacity(s);
		}
	}

	constexpr inline void operator_base(const capacity_change&, size_t c) {
      std::cout << " capacity changed " << c << std::endl << std::flush;
		if(c < size) {
			Base::set_size(c);
		}
		_resize(c);
	}

	template<class R, class U>
	constexpr inline auto operator_base(const R& op, const U& v) {
		return pty::Properties<Vector, pty::Container>::operator_base(op, v);
	}

	constexpr void _resize(size_t s) {
		T* newArray = new T[s];

        std::cout << " Resized " << s << std::endl << std::flush;

		if(_array != nullptr) {
			size_t max_index = dpsg::max(size, s, capacity);
			for(size_t t = 0; t < max_index ; ++t) {
				newArray[t] = std::forward<T>(_array[t]);
			}
		}
		std::swap(newArray, _array);
		if(newArray != nullptr && capacity > (size_t)0) {
			delete[] newArray;
		}
	}

	T* _array;
};

struct UniqueStruct {
	int v = 0;
	constexpr UniqueStruct() = default;
	constexpr UniqueStruct(int i) : v(i) {}
	constexpr UniqueStruct(const UniqueStruct&) = delete;
	constexpr UniqueStruct(UniqueStruct&&) = default;
	constexpr UniqueStruct& operator=(UniqueStruct&&) = default;
	constexpr UniqueStruct& operator=(const UniqueStruct&) = delete;
};

struct ImmovableStruct {
	int v = 0;
	constexpr ImmovableStruct() = default;
	constexpr ImmovableStruct(int i) : v(i) {}
	constexpr ImmovableStruct(const ImmovableStruct&) = default;
	constexpr ImmovableStruct(ImmovableStruct&&) = delete;
	constexpr ImmovableStruct& operator=(ImmovableStruct&&) = default;
	constexpr ImmovableStruct& operator=(const ImmovableStruct&) = delete;
};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_container() {
#else
int main() {
#endif
	Vector<int> v;
	assert(v.size == size_t(0));
	assert(v.capacity == size_t(0));
	v.capacity = 2;
	assert(v.size == size_t(0));
	assert(v.capacity == size_t(2));
	v.push_back(10);
	assert(v.capacity == size_t(2));
	assert(v.size == size_t(1));
	assert(v[0] == 10);
	v[0] = 8;
	assert(v[0] == 8);
	v.push_back(42);
	assert(v[0] == 8);
	assert(v[1] == 42);
	assert(v.size == size_t(2));
	assert(v.capacity == size_t(2));
	v.push_back(-1);
	assert(v.size == size_t(3));
	assert(v.capacity == size_t(6));
	assert(v[2] == -1);
	v.push_front(-42);
	assert(v[0] == -42);
	assert(v[1] == 8);
	assert(v[2] == 42);
	assert(v[3] == -1);
	assert(v[-1] == -1);
	assert(v[-2] == 42);
	assert(v[-3] == 8);
	assert(v[-4] == -42);
    std::cout << "Done with v<int>" << std::endl << std::flush;

	Vector<UniqueStruct> v2;
	UniqueStruct u(17);
	UniqueStruct uu;
	v2.push_back(std::move(u));
	UniqueStruct u2 = v2.pop_front();
	v2.push_front(std::move(u2));
	UniqueStruct u3 = v2.pop_back();
	assert(u3.v == 17);

	Vector<ImmovableStruct> v3;
	ImmovableStruct im;
	//v3.push_front(im);


	std::cout << "Test `container` passed with success" << std::endl;



#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
