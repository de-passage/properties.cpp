#include "properties.hpp"
#include "properties/numeric.hpp"
#include "properties/meta/property_hierarchy_info.hpp"

#include <iostream>

struct PHITest : pty::Properties<PHITest, pty::Numeric> {
};

template<class T>
void test_on_arbitrary_class(const pty::Arithmetic<T>&) {
	static_assert(std::is_same<pty::meta::get_base<pty::Arithmetic<T>>, PHITest>::value, "");
	static_assert(std::is_same<pty::meta::get_base<T>, PHITest>::value, "");
}

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_property_hierarchy_info() {
#else
int main() {
#endif
	PHITest t;
	test_on_arbitrary_class(t);

#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
