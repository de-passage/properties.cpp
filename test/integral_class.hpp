#include "properties.hpp"
#include "properties/arithmetic.hpp"
#include "properties/comparable.hpp"
#include "properties/bitwise.hpp"

#include <cassert>
#include <iostream>

//*
struct Integral : pty::Properties<Integral, pty::Comparable, pty::Arithmetic, pty::Bitwise> {

	typedef pty::Properties<Integral, pty::Comparable, pty::Arithmetic, pty::Bitwise> Base;
	constexpr Integral(int i) : _i(i) {}
	constexpr inline operator int() const { return _i; }

	friend pty::adaptor<Integral>;
	friend pty::adaptor<const Integral>;

	protected:
	PTY_FORWARD_OPERATOR_BASE(Base)
	constexpr inline int operator_base(pty::operators::cast) const {
		return _i;
	}
	constexpr inline int& operator_base(pty::operators::cast) {
		return _i;
	}

	int _i;

};
//*/
#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_integral_class() {
#else
int main() {
#endif

//	/*
	Integral a(1), b(0);
	assert(a > b);
	assert(b < a);
	assert(!(a < b));
	assert(!(b > a));
	assert(a >= b);
	assert(b <= a);
	assert(!(a == b));
	assert(a != b);


	assert(b < 2);
	assert(2 > b);
	assert(!(b > 2));
	assert(2 >= b);
	assert(b <= 2);
	assert(!(2 == b));
	assert(2 != b);

	assert(a == 1);
	assert(1 == a);
	assert(a != 0);
	assert(3 != a);
	assert(a <= 42);
	assert(42 >= a);
	assert(a <= 1);
	assert(a >= 1);
	assert(1 <= a);
	assert(1 >= a);
	assert(!(1 < a));
	assert(!(1 > a));

	assert((a += 1) == 2);
	assert((3 + a) == 5);
	assert((a - 2) == 0);

	assert((Integral(1) & Integral(2)) == Integral(0));
	assert((Integral(1) | Integral(2)) == Integral(3));
	assert((Integral(1) ^ Integral(2)) == Integral(3));
	assert((3 ^ Integral(2)) == 1);
//	*/
	std::cout << "Test `integral_class` passed with success" << std::endl;

#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
