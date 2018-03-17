#define PTY_TEST_INCLUDE_ALL_TESTS
#include "../test/numeric.hpp"
#include "../test/integral_class.hpp"
#include "../test/container.hpp"
#include "../test/attribute.hpp"
#include "../test/permissions.hpp"
#include "../test/tuple_operations.hpp"
#include "../test/addressable.hpp"
#include "../test/incrementable.hpp"
#include "../test/streamable.hpp"
#include "../test/arithmetic.hpp"
#include "../test/comparable.hpp"
#include "../test/bitwise.hpp"
#include "../test/assignable.hpp"
#include "../test/property_hierarchy_info.hpp"
#include "../test/iterable.hpp"
#include "../test/has_operator_base_overload.hpp"
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

