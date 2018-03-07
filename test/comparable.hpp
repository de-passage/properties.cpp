#include "properties.hpp"
#include "properties/comparable.hpp"

#include <cassert>
#include <iostream>

struct ComparableTest : pty::Properties<ComparableTest, pty::Comparable> {
	int value;

    ComparableTest(int i = 42) : value(i) {}

	template<class Op, class...Args>
	constexpr inline bool operator_base(const Op& op, Args&&... args) const {
		return op(value, args...);
	}

	template<class Op, class...Args>
	constexpr inline bool operator_base(const Op& op, const ComparableTest& args) const {
		return op(value, args.value);
	}
};

/*
struct ComparableTestApplyOperator : pty::Properties<ComparableTestApplyOperator,pty::Comparable> {
	typedef pty::Properties<ComparableTestApplyOperator,pty::Comparable> Base;
	PTY_FORWARD_OPERATOR_BASE(Base)

	inline constexpr ComparableTestApplyOperator(int i = 42) : value(i) {}

	int value = 42;
	
	template<class Op, class ...Args>
	constexpr inline bool operator_base(const pty::apply<Op, Args...>& op) const {
		return op(value);
	}
}; */

struct ComparableTestCastOperator : pty::Properties<ComparableTestCastOperator,pty::Comparable> {
	typedef pty::Properties<ComparableTestCastOperator,pty::Comparable> Base;
	PTY_FORWARD_OPERATOR_BASE(Base)

	inline constexpr ComparableTestCastOperator(int i = 42) : value(i) {}

	int value;

	constexpr inline int operator_base(pty::operators::cast) const {
		return value;
	}
};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_comparable() {
#else
int main() {
#endif
	ComparableTest test;
	assert(test == 42);
	assert(42 == test);
	assert(test != 24);
	assert(24 != test);
	assert(test > 24);
	assert(84 > test);
	assert(test < 84);
	assert(24 < test);
	assert(test >= 24);
	assert(24 <= test);
	assert(test <= 42);
	assert(42 <= test);
	assert(test >= 42);
	assert(42 >= test);
	static_assert(std::is_same<decltype(test == 42), bool>::value, "");
	static_assert(std::is_same<decltype(42 == test), bool>::value, "");
	static_assert(std::is_same<decltype(test != 24), bool>::value, "");
	static_assert(std::is_same<decltype(24 != test), bool>::value, "");
	static_assert(std::is_same<decltype(test > 24), bool>::value, "");
	static_assert(std::is_same<decltype(84 > test), bool>::value, "");
	static_assert(std::is_same<decltype(test < 84), bool>::value, "");
	static_assert(std::is_same<decltype(24 < test), bool>::value, "");
	static_assert(std::is_same<decltype(test >= 24), bool>::value, "");
	static_assert(std::is_same<decltype(24 <= test), bool>::value, "");
	static_assert(std::is_same<decltype(test <= 42), bool>::value, "");
	static_assert(std::is_same<decltype(42 <= test), bool>::value, "");
	static_assert(std::is_same<decltype(test >= 42), bool>::value, "");
	static_assert(std::is_same<decltype(42 >= test), bool>::value, "");

    ComparableTest test_24{24}, test_84{84}, test_42{42};
	assert(test == test_42);
	assert(test_42 == test);
	assert(test != test_24);
	assert(test_24 != test);
	assert(test > test_24);
	assert(test_84 > test);
	assert(test < test_84);
	assert(test_24 < test);
	assert(test >= test_24);
	assert(test_24 <= test);
	assert(test <= test_42);
	assert(test_42 <= test);
	assert(test >= test_42);
	assert(test_42 >= test);

	static_assert(std::is_same<decltype(test == test_42), bool>::value, "");
	static_assert(std::is_same<decltype(test_42 == test), bool>::value, "");
	static_assert(std::is_same<decltype(test != test_24), bool>::value, "");
	static_assert(std::is_same<decltype(test_24 != test), bool>::value, "");
	static_assert(std::is_same<decltype(test > test_24), bool>::value, "");
	static_assert(std::is_same<decltype(test_84 > test), bool>::value, "");
	static_assert(std::is_same<decltype(test < test_84), bool>::value, "");
	static_assert(std::is_same<decltype(test_24 < test), bool>::value, "");
	static_assert(std::is_same<decltype(test >= test_24), bool>::value, "");
	static_assert(std::is_same<decltype(test_24 <= test), bool>::value, "");
	static_assert(std::is_same<decltype(test <= test_42), bool>::value, "");
	static_assert(std::is_same<decltype(test_42 <= test), bool>::value, "");
	static_assert(std::is_same<decltype(test >= test_42), bool>::value, "");
	static_assert(std::is_same<decltype(test_42 >= test), bool>::value, "");
	/*
	ComparableTestApplyOperator test2;
	assert(test2 == 42);
	assert(42 == test2);
	assert(test2 != 24);
	assert(24 != test2);
	assert(test2 > 24);
	assert(84 > test2);
	assert(test2 < 84);
	assert(24 < test2);
	assert(test2 >= 24);
	assert(24 <= test2);
	assert(test2 <= 42);
	assert(42 <= test2);
	assert(test2 >= 42);
	assert(42 >= test2);
	*/

	ComparableTestCastOperator test3;
	assert(test3 == 42);
	assert(42 == test3);
	assert(test3 != 24);
	assert(24 != test3);
	assert(test3 > 24);
	assert(84 > test3);
	assert(test3 < 84);
	assert(24 < test3);
	assert(test3 >= 24);
	assert(24 <= test3);
	assert(test3 <= 42);
	assert(42 <= test3);
	assert(test3 >= 42);
	assert(42 >= test3);

    ComparableTestCastOperator test2_24{24}, test2_84{84}, test2_42{42};
	assert(test == test2_42);
	assert(test2_42 == test3);
	assert(test3 != test2_24);
	assert(test2_24 != test3);
	assert(test3 > test2_24);
	assert(test2_84 > test3);
	assert(test3 < test2_84);
	assert(test2_24 < test3);
	assert(test3 >= test2_24);
	assert(test2_24 <= test3);
	assert(test3 <= test2_42);
	assert(test2_42 <= test3);
	assert(test3 >= test2_42);
	assert(test2_42 >= test3);

	static_assert(std::is_same<decltype(test3 == 42), bool>::value, "");
	static_assert(std::is_same<decltype(42 == test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 != 24), bool>::value, "");
	static_assert(std::is_same<decltype(24 != test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 > 24), bool>::value, "");
	static_assert(std::is_same<decltype(84 > test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 < 84), bool>::value, "");
	static_assert(std::is_same<decltype(24 < test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 >= 24), bool>::value, "");
	static_assert(std::is_same<decltype(24 <= test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 <= 42), bool>::value, "");
	static_assert(std::is_same<decltype(42 <= test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 >= 42), bool>::value, "");
	static_assert(std::is_same<decltype(42 >= test3), bool>::value, "");

	static_assert(std::is_same<decltype(test == test2_42), bool>::value, "");
	static_assert(std::is_same<decltype(test2_42 == test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 != test2_24), bool>::value, "");
	static_assert(std::is_same<decltype(test2_24 != test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 > test2_24), bool>::value, "");
	static_assert(std::is_same<decltype(test2_84 > test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 < test2_84), bool>::value, "");
	static_assert(std::is_same<decltype(test2_24 < test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 >= test2_24), bool>::value, "");
	static_assert(std::is_same<decltype(test2_24 <= test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 <= test2_42), bool>::value, "");
	static_assert(std::is_same<decltype(test2_42 <= test3), bool>::value, "");
	static_assert(std::is_same<decltype(test3 >= test2_42), bool>::value, "");
	static_assert(std::is_same<decltype(test2_42 >= test3), bool>::value, "");
	std::cout << "Test `comparable` passed with success" << std::endl;
}
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif

