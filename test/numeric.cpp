#include "properties.hpp"
#include "properties/numeric.hpp"

#include <cassert>
#include <iostream>
#include <type_traits>


//*
struct Int : pty::Properties<Int, pty::Numeric> {
	constexpr Int(int v) : value(v) {}

	constexpr inline operator int() const {
		return value;
	}
	protected:
	int value;
	using Base = pty::Properties<Int, pty::Numeric>;
	PTY_FORWARD_OPERATOR_BASE(Base)
	friend pty::adaptor<Int>;
	friend pty::adaptor<const Int>;

	constexpr inline int operator_base(const pty::operators::cast&) const {
		return value;
	}
	constexpr inline int& operator_base(const pty::operators::cast&) {
		return value;
	}
};
//*/

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_numeric() {
#else
int main() {
#endif

	Int test(0);
	static_assert(std::is_same<decltype(test + 1), Int>::value, "");
	assert(test + 1 == 1);
	static_assert(std::is_same<decltype(1 + test), Int>::value, "");
	assert(1 + test == 1);
	static_assert(std::is_same<decltype(test - 1), Int>::value, "");
	assert(test - 1 == -1);
	static_assert(std::is_same<decltype(1 - test), Int>::value, "");
	assert(1 - test == 1);
	static_assert(std::is_same<decltype(test += 1), Int&>::value, "");
	assert((test += 2) == 2);
	assert(test == 2);
	static_assert(std::is_same<decltype(test -= 1), Int&>::value, "");
	assert((test -= 1) == 1);
	assert(test == 1);
	static_assert(std::is_same<decltype(test * 42), Int>::value, "");
	assert(test * 42 == 42);
	static_assert(std::is_same<decltype(test *= 42), Int&>::value, "");
	assert((test *= 42) == 42);
	assert(test == 42);
	static_assert(std::is_same<decltype(test / 42), Int>::value, "");
	assert(test / 42 == 1);
	static_assert(std::is_same<decltype(test /= 42), Int&>::value, "");
	assert((test /= 42) == 1);
	assert(test == 1);

//	test = (test + 1) * 2;

	

	//*
	Int i1(0), i2(2);
	assert(i1 < i2);
	assert(i2 > i1);
	assert(!(i2 < i1));
	assert(i1 == Int(0)); 
	assert((i1 + i2) == Int(2));
	assert(Int(4) == (i2 + i2));
	assert(Int(6) == Int(3) * Int(2));
	i1 += Int(10);
	assert(i1 == Int(10));
	assert((Int(4) & Int(1)) == Int(0));
	assert((Int(4) | Int(1)) == Int(5));
	assert((Int(5) ^= Int(4)) == Int(1));
	//*/
	//
	std::cout << "Test `numeric` passed with success" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
