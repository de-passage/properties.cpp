#include "properties.hpp"

#include "properties/iterable.hpp"

#include <iostream>

#include <cassert>



template<class T>
struct MyList : pty::Properties<MyList<T>, pty::Iterable>{

	using Base = pty::Properties<MyList<T>, pty::Iterable>;
	using typename Base::iterator;
	using typename Base::const_iterator;
	struct Node {
		T value;
		Node* next = nullptr;
	};

	MyList() : _list(nullptr) {}
	~MyList() {
		while(_list != nullptr) {
			auto tmp = _list->next;
			delete _list;
			_list = tmp;
		}
	}


	//As of yet pty::Iterable requires operator_base to be public
	Node* operator_base(pty::operators::iteration_start) {
		return _list;
	}

	Node* operator_base(pty::operators::iteration_end) {
		return nullptr;
	}

	Node* operator_base(pty::operators::increment_iterator, Node* iterator) const {
		return iterator->next;
	}

	//*
	template<class Iter>
	int operator_base(pty::operators::dereference_iterator, Iter&& iter) const {
		return iter->value;
	}
	//*/

	template<class Iter>
	int& operator_base(pty::operators::dereference_iterator, Iter&& iter) {
		return iter->value;
	}

	template<class Op>
		bool operator_base(pty::operators::compare_iterators, Op op, const Node* lhv, Node* rhv) const {
			return op(lhv, rhv);
		}

	iterator push_front(T&& value) {
		auto* node = new Node{std::forward<T>(value), Base::begin()};
		_list = node;
		return Base::make_iterator(node);
	};

	iterator push_front(const T& value) {
		auto* node = new Node{value, Base::begin()};
		_list = node;
		return Base::make_iterator(node);
	};


	Node* _list;
	


};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_iterable() {
#else
int main() {
#endif

	MyList<int> list;

	static_assert(std::is_same<decltype(*list.begin()), int&>::value, "");
	static_assert(std::is_same<decltype(*list.cbegin()), int>::value, "");

	for(int j = 0; j < 10 ; ++j)
		list.push_front(j);
	int j = 9, count = 0;
	for(auto i = list.begin(); i != list.end() ; ++i, --j, ++count) {
//		std::cout << count << " " << *i << " " << j << std::endl << std::flush;
		assert(*i == j);
	}
	assert(count == 10);


	static_assert(std::is_same<pty::details::deduce_iterator_tag<MyList<int>, MyList<int>::Node*>, std::forward_iterator_tag>::value, "");
	static_assert(std::is_same<MyList<int>::iterator::iterator_category, std::forward_iterator_tag>::value, "");

	std::cout << "Test `iterable` passed" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
