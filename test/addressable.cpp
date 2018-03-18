#include "properties.hpp"
#include "properties/addressable.hpp"

#include <cassert>
#include <iostream>

struct AddressTest : pty::Properties<AddressTest, pty::Addressable> {
	constexpr AddressTest() : values{0} {}
	int values[10];

	template<class Op, class ...Args>
		constexpr inline int& operator_base(const Op& op, const Args&... args) {
			return op(values, args...);
		}

	template<class Op, class ...Args>
		constexpr inline int operator_base(const Op& op, const Args&... args) const {
			return op(values, args...);
		}

};

struct AddressTestCastOp : pty::Properties<AddressTestCastOp, pty::Addressable> {
	constexpr AddressTestCastOp() : values{0} {}
	int values[10];
    typedef pty::Properties<AddressTestCastOp, pty::Addressable> Base;
    PTY_FORWARD_OPERATOR_BASE(Base)

    constexpr inline int (&operator_base(pty::operators::cast))[10] {
        return values;
    }

    constexpr inline const int (&operator_base(pty::operators::cast) const)[10] {
        return values;
    }

};

struct InnerAddr { InnerAddr() : value(42) {} InnerAddr(const InnerAddr&) = delete; int value; bool operator==(int i) const { return i == value; }; InnerAddr& operator=(int i) { value = i; return *this; } };

struct AddressableObjCastOp : pty::Properties<AddressableObjCastOp, pty::Addressable> {
	typedef pty::Properties<AddressableObjCastOp, pty::Addressable> Base;
	InnerAddr* member;
	AddressableObjCastOp() : member(new InnerAddr()) {}
	~AddressableObjCastOp() { delete member; }

	PTY_FORWARD_OPERATOR_BASE(Base)

	inline InnerAddr* operator_base(pty::operators::cast) {
		return member;
	}

	inline const InnerAddr* operator_base(pty::operators::cast) const {
		return member;
	}

};

template<class T>
void constant_addressable_test(const T& t) {
	for(int i = 0; i < 10; ++i) {
		assert(t[i] == i + 1);
	}
	assert(*t == 1);
}

template<class T>
void constant_dereference_test(const T& t) {
	static_assert(std::is_same<decltype(*t), const InnerAddr&>::value, "");
	assert((*t) == 24);
	assert(t->value == 24);
}

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_addressable() {
#else
int main() {
#endif
	AddressTest test;
	for(int i = 0; i < 10; ++i)
		assert(test.values[i] == 0);
	for(int i = 0; i < 10; ++i)
		assert(test[i] == 0);

	for(int i = 0; i < 10; ++i) {
		test[i] = i + 1;
		assert(test[i] == i + 1);
	}
		
	AddressTestCastOp test2;
	for(int i = 0; i < 10; ++i) {
		assert(test2.values[i] == 0);
	}

	for(int i = 0; i < 10; ++i)
		assert(test2[i] == 0);

	for(int i = 0; i < 10; ++i) {
		test2[i] = i + 1;
		assert(test2[i] == i + 1);
	}

	assert(*test == 1);
	assert(*test2 == 1);
	constant_addressable_test(test);
	constant_addressable_test(test2);

	AddressableObjCastOp test3;
	static_assert(std::is_same<decltype(*test3), InnerAddr&>::value, "");
	assert((*test3) == 42);
	assert((*test3 = 24) == 24);
	assert((*test3).value == 24);
	assert(test3->value == 24);
	constant_dereference_test(test3);

	std::cout << "Test `addressable` passed with success" << std::endl;

#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
