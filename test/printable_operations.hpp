#include "properties/helpers/printable_operators.hpp"

#include <iostream>

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_printable_operations() {
#else
int main() {
#endif

	std::ostream out;

	out << pty::operators::plus() << std::endl;
	out << pty::operators::shift_left() << std::endl;

#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
