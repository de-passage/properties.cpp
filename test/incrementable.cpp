#include "properties.hpp"
#include "properties/incrementable.hpp"
#include "properties/comparable.hpp"
#include "properties/streamable.hpp"
#include "properties/meta/enable_for.hpp"

#include <cassert>
#include <iostream>

struct IncTest2 : pty::Properties<IncTest2, pty::Incrementable, pty::Comparable> {
	typedef pty::Properties<IncTest2, pty::Incrementable, pty::Comparable> Base;
	constexpr IncTest2(int i = 0) : value(i) {}
	int value;

	template<class Op, class ...Args>
	inline constexpr decltype(auto) operator_base(const Op& op, Args&&... args) const {
		return op(value, args...);
	}
	
	template<class Op, class ...Args>
	inline constexpr decltype(auto) operator_base(const Op& op, Args&&... args) {
		return op(value, args...);
	}
	

};

struct IncTest : pty::Properties<IncTest, pty::Incrementable, pty::Comparable> {
	typedef pty::Properties<IncTest, pty::Incrementable, pty::Comparable> Base;
	constexpr IncTest(int i = 0) : value(i) {}
	int value;

	PTY_FORWARD_OPERATOR_BASE(Base)

	inline constexpr int& operator_base(pty::operators::cast) { return value; }

	template<class Op, class T, class = pty::meta::enable_for<Op, pty::operators::comparison> >
	inline constexpr bool operator_base(const Op& op, T&& arg) const {
		return op(value, arg);
	}
};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_incrementable() {
#else
int main() {
#endif
	IncTest t;
	assert(t == 0);
	assert((++t).value == 1);
	assert(t == 1);
	assert(t++.value == 1);
	assert(t == 2);
	assert((--t).value == 1);
	assert(t == 1);
	assert((t--).value == 1);
	assert(t == 0);

	IncTest t2;
	assert(t2 == 0);
	assert((++t2).value == 1);
	assert(t2 == 1);
	assert(t2++.value == 1);
	assert(t2 == 2);
	assert((--t2).value == 1);
	assert(t2 == 1);
	assert((t2--).value == 1);
	assert(t2 == 0);

	std::cout << "Test `incrementable` passed with success" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
