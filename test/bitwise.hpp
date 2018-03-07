#include "properties.hpp"
#include "properties/bitwise.hpp"

#include <cassert>
#include <iostream>

struct BitwiseTest : pty::Properties<BitwiseTest, pty::Bitwise> {
	char value;
	constexpr inline BitwiseTest(int i = 0) : value(i) {}

	template<class Op, class...Args>
	constexpr inline BitwiseTest operator_base(const Op& op, const Args&... args) const {
		return op(value, args...);
	}

	template<class Op, class...Args>
	constexpr inline BitwiseTest& operator_base(const Op& op, const Args&... args) {
		op(value, args...);
		return *this;
	}
};

struct BitwiseTestCastOperator : pty::Properties<BitwiseTestCastOperator, pty::Bitwise> {
	typedef pty::Properties<BitwiseTestCastOperator, pty::Bitwise> Base;
	char value;
	constexpr inline BitwiseTestCastOperator(int i = 0) : value(i) {}

	PTY_FORWARD_OPERATOR_BASE(Base)
	
	constexpr inline char& operator_base(pty::operators::cast) {
		return value;
	}
	constexpr inline char operator_base(pty::operators::cast) const {
		return value;
	}
};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_bitwise() {
#else
int main() {
#endif
	BitwiseTest test;
	assert((test | 1).value == 1);
	assert((test |= 1).value == 1);
	assert((test & 1).value == 1);
	assert((test &= 2).value == 0);
	assert((test ^ 3).value == 3);
	assert((test ^= 3).value == 3);
	assert((test << 1).value == 6);
	assert((test <<= 1).value == 6);
	assert((test >> 1).value == 3);
	assert((test >>= 1).value == 3);
	assert((~test).value == ~3);

	BitwiseTestCastOperator test2;
	assert((test2 | 1).value == 1);
	assert((test2 |= 1).value == 1);
	assert((test2 & 1).value == 1);
	assert((test2 &= 2).value == 0);
	assert((test2 ^ 3).value == 3);
	assert((test2 ^= 3).value == 3);
	assert((test2 << 1).value == 6);
	assert((test2 <<= 1).value == 6);
	assert((test2 >> 1).value == 3);
	assert((test2 >>= 1).value == 3);
	assert((~test2).value == ~3);

	std::cout << "Test `bitwise` passed with success" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
