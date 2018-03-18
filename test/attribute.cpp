#include "properties.hpp"

#include "properties/attribute.hpp"

#include <cassert>
#include <iostream>

struct TestAttribute {
  template<class T, template<class>class...Args> using Attribute = pty::Attribute<T, TestAttribute, Args...>;
  Attribute<int> int_value;
};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_attribute() {
#else
int main() {
#endif

    TestAttribute t;
    assert(t.int_value == 0);

	std::cout << "Test `attribute` passed with success" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
