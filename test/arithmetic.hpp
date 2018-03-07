#include "properties.hpp"
#include "properties/arithmetic.hpp"
#include "properties/details/define_property.hpp"

#include <cassert>
#include <iostream>
#include <utility>

struct ArithmeticTest : pty::Properties<ArithmeticTest, pty::Arithmetic> {
	typedef pty::Properties<ArithmeticTest, pty::Arithmetic> Base;
	constexpr ArithmeticTest() : value(0) {}
	constexpr ArithmeticTest(int i) : value(i) {}
	constexpr ArithmeticTest(const ArithmeticTest& t) = default;
	int value;

	template<class Op, class ...Args>
	constexpr inline ArithmeticTest operator_base(const Op& op, const Args&... args) const {
		return op(value, args...);
	}

	template<class Op, class ...Args>
	constexpr inline ArithmeticTest& operator_base(const Op& op, const Args&... args) {
		op(value, args...);
		return *this;
	}

};

struct ArithFullOpTest : pty::Properties<ArithFullOpTest, pty::Arithmetic> {
	constexpr ArithFullOpTest() : val(0) {}
	int val;
	template<class Op, class ...Args>
		constexpr inline decltype(auto) operator_base(const Op& op, const Args&... args) {
			return op(val, args...);
		}
};

struct ArithmeticOpBase : pty::Properties<ArithmeticOpBase, pty::Arithmetic> {
	typedef pty::Properties<ArithmeticOpBase, pty::Arithmetic> Base;
	PTY_FORWARD_OPERATOR_BASE(Base)
	constexpr ArithmeticOpBase(int i = 0) : value(i) {}
	int value;
	constexpr inline int& operator_base(pty::operators::cast) {
		return value;
	}
	constexpr inline int operator_base(pty::operators::cast) const {
		return value;
	}
};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_arithmetic() {
#else
int main() {
#endif
	ArithmeticTest test;
	assert(test.value == 0);
	assert((test + 1).value == 1);
	assert((1 + test).value == 1);
	assert((test += 5).value == 5);
	assert(test.value == 5);
	assert((-test).value == -5);
	assert((+test).value == 5);
	assert((test - 3).value == 2);
	assert((2 - test).value == -3);
	assert((test -= 1).value == 4);
	assert((test * 6).value == 24);
	assert((-3 * test).value == -12);
	assert((test *= 2).value == 8);
	assert((test / 2).value == 4);
	assert((test /= 2).value == 4);

	static_assert(std::is_same<decltype(test + 1), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(1 + test), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(test += 5), ArithmeticTest&>::value, "");
	static_assert(std::is_same<decltype(-test), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(+test), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(test - 3), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(2 - test), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(test -= 1), ArithmeticTest&>::value, "");
	static_assert(std::is_same<decltype(test * 6), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(-3 * test), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(test *= 2), ArithmeticTest&>::value, "");
	static_assert(std::is_same<decltype(test / 2), ArithmeticTest>::value, "");
	static_assert(std::is_same<decltype(test /= 2), ArithmeticTest&>::value, "");

	ArithFullOpTest t;
	(t+= 5) += 3;
	assert(t.val == 8);

	ArithmeticOpBase aob;
	assert((-(aob + 42)).value == -42);
	assert(((aob += 12) /= 3).value == 4);
	assert(aob.value == 4);
	aob = 0;
	assert(aob.value == 0);
	assert((aob + 1).value == 1);
	assert((1 + aob).value == 1);
	assert((aob += 5).value == 5);
	assert(aob.value == 5);
	assert((-aob).value == -5);
	assert((+aob).value == 5);
	assert((aob - 3).value == 2);
	assert((2 - aob).value == -3);
	assert((aob -= 1).value == 4);
	assert((aob * 6).value == 24);
	assert((-3 * aob).value == -12);
	assert((aob *= 2).value == 8);
	assert((aob / 2).value == 4);
	assert((aob /= 2).value == 4);

//*
	static_assert(std::is_same<decltype(aob + 1), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(1 + aob), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(aob += 5), ArithmeticOpBase&>::value, "");
	static_assert(std::is_same<decltype(-aob), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(+aob), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(aob - 3), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(2 - aob), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(aob -= 1), ArithmeticOpBase&>::value, "");
	static_assert(std::is_same<decltype(aob * 6), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(-3 * aob), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(aob *= 2), ArithmeticOpBase&>::value, "");
	static_assert(std::is_same<decltype(aob / 2), ArithmeticOpBase>::value, "");
	static_assert(std::is_same<decltype(aob /= 2), ArithmeticOpBase&>::value, "");
//	*/
	std::cout << "Test `arithmetic` passed with success" << std::endl;

#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
