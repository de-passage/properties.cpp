#include "properties/meta/has_operator_base_overload.hpp"

#include "properties.hpp"
#include "properties/assignable.hpp"
#include "properties/operators.hpp"
#include "properties/meta/property_hierarchy_info.hpp"

struct TestHOBO : pty::Properties<TestHOBO, pty::Assignable>{
	constexpr int operator_base(pty::operators::cast) const {
		return 0;
	};
};

struct TestHOBOTemplateOp : pty::Properties<TestHOBOTemplateOp, pty::Assignable> {
	template<class Op, class = pty::meta::enable_for<Op, pty::operators::assign>>
	constexpr int operator_base(Op) { return 0; }
};

struct TestHOBOPrivate : pty::Properties<TestHOBOTemplateOp, pty::Assignable> {
	private:
		constexpr inline int operator_base(pty::operators::assign) {return 0;}
};


void foo(int) {}

template<bool b, bool c, class T>
void check_test_on_const(const pty::Assignable<T>&) {
	using namespace pty::meta;
	static_assert(has_operator_base_overload<const pty::meta::get_base<T>, pty::operators::cast> == b, "");
	static_assert(has_operator_base_overload<const pty::meta::get_base<T>, pty::operators::assign> == c, "");
}

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_has_operator_base_overload () {
#else
int main() {
#endif
	using namespace pty::meta;
	static_assert(has_operator_base_overload<TestHOBO, pty::operators::cast>, "");
	static_assert(!has_operator_base_overload<TestHOBO, pty::operators::assign>, "");
	
	static_assert(!has_operator_base_overload<TestHOBOTemplateOp, pty::operators::cast>, "");
	static_assert(has_operator_base_overload<TestHOBOTemplateOp, pty::operators::assign>, "");

	check_test_on_const<true, false>(TestHOBO());
	check_test_on_const<false, false>(TestHOBOTemplateOp());
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
