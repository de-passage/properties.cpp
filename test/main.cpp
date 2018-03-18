//#define PTY_TEST_INCLUDE_ALL_TESTS

#include "../test/include/numeric.hpp"
#include "../test/include/integral_class.hpp"
#include "../test/include/container.hpp"
#include "../test/include/attribute.hpp"
#include "../test/include/permissions.hpp"
#include "../test/include/tuple_operations.hpp"
#include "../test/include/addressable.hpp"
#include "../test/include/incrementable.hpp"
#include "../test/include/streamable.hpp"
#include "../test/include/arithmetic.hpp"
#include "../test/include/comparable.hpp"
#include "../test/include/bitwise.hpp"
#include "../test/include/assignable.hpp"
#include "../test/include/property_hierarchy_info.hpp"
#include "../test/include/iterable.hpp"
#include "../test/include/has_operator_base_overload.hpp"
#include "../test/include/printable_operations.hpp"

int main() {
	test_assignable();
	test_container(); //Need to test attribute and implement Observer correctly first
    test_attribute();
	test_integral_class();
	test_permissions();
	test_tuple_operations();
	test_incrementable();
	test_addressable();
	test_streamable();
	test_arithmetic();
	test_comparable();
	test_property_hierarchy_info();
	test_bitwise();
	test_numeric();
	test_iterable();
	test_has_operator_base_overload();
	test_printable_operations();

	return 0;
}

