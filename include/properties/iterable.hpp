#ifndef GUARD_PTY_ITERABLE_HPP__
#define GUARD_PTY_ITERABLE_HPP__

#include "properties.hpp"
#include "properties/operators/iteration.hpp"
#include "properties/meta/enable_for.hpp"
#include "properties/incrementable.hpp"
#include "properties/addressable.hpp"
#include "properties/details/deduce_iterator_tag.hpp"
#include "properties/meta/property_hierarchy_info.hpp"

#include <utility>

namespace pty {
	namespace details { template<class> struct Iterator; }

	template<class Base>
		struct Iterable : Base {

			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::iteration>>
				constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { 
					return Base::operator_base(op, std::forward<_pty_Args>(args)...);
				}

			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::iteration>>
				constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { 
					return Base::operator_base(op, std::forward<_pty_Args>(args)...);
				}

			using Base::operator=;

			typedef details::Iterator<Iterable> iterator;
			typedef details::Iterator<const Iterable> const_iterator;

			constexpr inline const_iterator begin() const;
			constexpr inline const_iterator end() const;
			constexpr inline const_iterator cbegin() const;
			constexpr inline const_iterator cend() const;
			constexpr inline iterator begin();
			constexpr inline iterator end();

		};

	template<class T>
		constexpr inline typename Iterable<T>::const_iterator Iterable<T>::begin() const {
			return const_iterator(downcast(const_cast<Iterable*>(this)).operator_base(pty::operators::iteration_start()), this);
		}

	template<class T>
		constexpr inline typename Iterable<T>::const_iterator Iterable<T>::end() const {
			return const_iterator(downcast(const_cast<Iterable*>(this)).operator_base(pty::operators::iteration_end()), this);
		}

	template<class T>
		constexpr inline typename Iterable<T>::iterator Iterable<T>::begin() {
			return iterator(downcast(this).operator_base(pty::operators::iteration_start()), this);
		}

	template<class T>
		constexpr inline typename Iterable<T>::iterator Iterable<T>::end() {
			return iterator(downcast(this).operator_base(pty::operators::iteration_end()), this);
		}

	template<class T>
		constexpr inline typename Iterable<T>::const_iterator Iterable<T>::cbegin() const {
			return begin();
		}

	template<class T>
		constexpr inline typename Iterable<T>::const_iterator Iterable<T>::cend() const {
			return end();
		}

	namespace details {

		template<class Iter>
			struct Iterator : pty::Properties<Iterator<Iter>, pty::Incrementable, pty::Addressable> {

				private:
					friend pty::adaptor<Iterator>;
					friend pty::adaptor<const Iterator>;
					template<class...Args>
						constexpr inline decltype(auto) _forward_to_ref(Args&&... args) {
							return downcast(_ref).operator_base(std::forward<Args>(args)...);

						}

					template<class...Args>
						constexpr inline decltype(auto) _forward_to_ref(Args&&... args) const {
							return downcast(_ref).operator_base(std::forward<Args>(args)...);
						}

					typedef decltype(downcast(std::declval<std::remove_const_t<Iter>*>()).operator_base(pty::operators::iteration_start())) _iterator_type;

					Iter* _ref;
					_iterator_type _iter;

				public:
					typedef std::remove_reference_t<decltype(downcast(std::declval<Iter*>()).operator_base(pty::operators::dereference_iterator(), std::declval<_iterator_type>()))> value_type;
					typedef details::deduce_iterator_tag<pty::meta::get_base<Iter>, _iterator_type> iterator_category;

					constexpr Iterator(_iterator_type target = _iterator_type(), Iter* source = nullptr) : _ref(source), _iter(target) {}
					constexpr Iterator(const Iterator& source) : _ref(source._ref), _iter(source._iter) {}

				private:
					template<class Op, class = pty::meta::enable_for<Op, pty::operators::address>>
						constexpr inline value_type& operator_base(Op) {
							return _forward_to_ref(pty::operators::dereference_iterator(), _iter);
						}
					template<class Op, class = pty::meta::enable_for<Op, pty::operators::address>>
						constexpr inline value_type operator_base(Op) const {
							return _forward_to_ref(pty::operators::dereference_iterator(), _iter);
						}

			};
	}
}

#endif// GUARD_PTY_ITERABLE_HPP__
