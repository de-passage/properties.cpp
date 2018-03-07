#include <properties.hpp>
#include <properties/streamable.hpp>

#include <cassert>

#include <iostream>


struct StreamTest : pty::Properties<StreamTest, pty::Streamable> {
	int storage[3];

	constexpr StreamTest() : storage{9, 8, 7} {}

	template<class Op, class Stream>
	inline constexpr decltype(auto) operator_base(const Op& op, Stream& s) {
		return op(s, storage[0], storage[1], storage[2]);
	}

	template<class Op, class Stream>
	inline constexpr decltype(auto) operator_base(const Op& op, Stream& s) const {
		return op(s, storage[0], storage[1], storage[2]);
	}

};

struct stream_in {
	constexpr stream_in() : val(0) {}
	int val;
		inline constexpr stream_in& operator>>(int& t) {
			t = val++;
			return *this;
		}
};

struct stream_out {
	int val[3];
	int counter;

	constexpr stream_out() : val{-1,-1,-1}, counter(0) {}
		inline constexpr stream_out& operator<<(int t) {
			val[counter++] = t;
			return *this;
		}
};

#define BASE pty::Properties<ApplyStreamTest, pty::Streamable>
struct ApplyStreamTest : BASE {
	typedef BASE Base;
#undef BASE
	PTY_FORWARD_OPERATOR_BASE(Base)

	int value;

	constexpr ApplyStreamTest(int i) : value(i) {}

	inline constexpr int operator_base(pty::operators::cast) const {
		return value;
	}

	inline constexpr int& operator_base(pty::operators::cast) {
		return value;
	}
};

struct stream_42 {
	constexpr stream_42() =default;
	constexpr inline stream_42& operator>>(int& i) {
		i = 42;
		return *this;
	}
};

struct storage_stream {
	constexpr storage_stream() : value(0) {}
	constexpr storage_stream(const storage_stream&) = delete;
	int value;
	constexpr inline storage_stream& operator<<(int i) {
		value = i;
		return *this;
	}
};


#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_streamable() {
#else
int main() {
#endif
	StreamTest s;
	stream_in in;
	stream_out out;

	in >> s;
	//*
	assert(s.storage[0] == 0);
	assert(s.storage[1] == 1);
	assert(s.storage[2] == 2);
	//*/

	out << s;

	assert(out.val[0] == 0);
	assert(out.val[1] == 1);
	assert(out.val[2] == 2);

	stream_42 s42;
	storage_stream ss;
	//*
	ApplyStreamTest ast(0);
	assert(ast.value == 0);
	s42 >> ast;

	assert(ast.value == 42);
	assert(ss.value == 0);
	ss << ast;
	assert(ss.value == 42);

	/* works as well
	std::cin >> s;
	std::cout << s << std::endl;
	//*/

	std::cout << "Test `streamable` passed with success" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
