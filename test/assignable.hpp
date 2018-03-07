#include "properties.hpp"
#include "properties/assignable.hpp"

#include <cassert>
#include <iostream>

struct AssignTest : pty::Properties<AssignTest, pty::Assignable> {
 	typedef pty::Properties<AssignTest, pty::Assignable> Base;
	
	constexpr AssignTest(float f = 0.f) : called(false), move_assigned(false), value(f) {}
	bool called;
	bool move_assigned;
	float value;
	using Base::operator=;

	private:
	template<class Op, class ...Args>
		constexpr inline AssignTest& operator_base(const Op& op, Args&&... args) {
			called = true;
			op(value, args...);
			return *this;
		}
	friend pty::adaptor<AssignTest>;
	friend pty::adaptor<const AssignTest>;

	public:
	AssignTest& operator=(const AssignTest& t) {
		operator_base(pty::operators::assign(), t.value);
		return *this;
	}
	AssignTest& operator=(AssignTest&& t) {
		move_assigned = true;
		operator_base(pty::operators::assign(), t.value);
		return *this;
	}

};

struct AssignTestCastOp : pty::Properties<AssignTestCastOp, pty::Assignable> {
	bool called;
	bool move_assigned;
	double value;

	constexpr AssignTestCastOp(double d = 0) : called(false), move_assigned(false), value(d) {}
	typedef pty::Properties<AssignTestCastOp, pty::Assignable> Base;
	using Base::operator=;

	private:
	PTY_FORWARD_OPERATOR_BASE(Base)

	constexpr inline double& operator_base(pty::operators::cast) {
		called = true;
		return value;
	}
	friend pty::adaptor<AssignTestCastOp>;
	friend pty::adaptor<const AssignTestCastOp>;

	public:

	AssignTestCastOp& operator=(const AssignTestCastOp& t) {
		operator_base(pty::operators::assign(),t.value);
		return *this;
	}

	AssignTestCastOp& operator=(AssignTestCastOp&& t) {
		move_assigned = true;
		operator_base(pty::operators::assign(),t.value);
		return *this;
	}

};

AssignTest create_AssignTest() { return {}; }
AssignTestCastOp create_AssignTestCastOp() { return {}; }

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_assignable() {
#else
int main() {
#endif
	AssignTest t;
	t = 42;
	assert(t.value == 42);
	assert(t.called);
	t.called = false;
	((t = 54) = 5);
	assert(t.value == 5);
	assert(t.called);
	t.called = false;

	AssignTestCastOp t2;
	t2 = 42;
	assert(t2.called);
	t2.called = false;
	assert(t2.value == 42);
	((t2 = 54) = 5);
	assert(t2.value == 5);
	assert(t2.called);
	t2.called = false;

	AssignTest t3(5);
	t = 0;
	assert(t.value == 0);
	assert(t.called);
	t.called = false;
	assert(!t3.called);
	t = t3;
	assert(t.value == 5);
	assert(t.called);
	assert(!t3.called);
	t.called = false;
	

	static_assert(std::is_same<decltype(t = 0), AssignTest&>::value, "");
	static_assert(std::is_same<decltype(t2 = 0), AssignTestCastOp&>::value, "");

	assert(!t.move_assigned && !t2.move_assigned);
	t = create_AssignTest();
	assert(t.called);
	assert(t.move_assigned);
	t2 = create_AssignTestCastOp();
	assert(t2.called);
	assert(t2.move_assigned);

	std::cout << "Test `assignable` passed with success" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
