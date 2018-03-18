#include "include/printable_operations.hpp"
#include "properties/helpers/printable_operators.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

struct TestPrintableOperations : std::streambuf {

	TestPrintableOperations() : buffer(1) {}

	int_type overflow(int_type c) {
		if( c != (int_type)'\n')
			(*buffer.rbegin()) += c;
		else
			buffer.push_back("");
		return c;
	}
	
	std::vector<std::string> buffer;
};

struct OutStream {

	OutStream(std::ostream& out) : out(out) {}

	template<class T>
	void operator()(const T& t, int) {
		out << t << std::endl;
	}

	std::ostream& out;

};

struct TestOutStream {
	TestOutStream(const TestPrintableOperations& t) : values(t) {}

	template<class T>
	void operator()(const T&, int i) {
//		std::cout << i << " " << std::string(T::name) << " == " << values.buffer.at(i) << std::endl;
		assert(values.buffer.at(i) == std::string(T::name));
	}

	const TestPrintableOperations& values;
};

template<class Functor, class Tuple, int i, int max>
std::enable_if_t<i == max> for_each_element(const Tuple&, Functor&&) {}

template<class Functor, class Tuple, int max = std::tuple_size<Tuple>::value, int i = 0>
std::enable_if_t<(i < max)> for_each_element(const Tuple& args, Functor&& f) {
	f(std::get<i>(args), i);
	for_each_element<Functor, Tuple, max, i + 1>(args, std::forward<Functor>(f));
}

template<class ...T>
auto make_tuple(pty::meta::tuple<T...>) {
	return std::make_tuple(T()...);
}

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_printable_operations() {
#else
int main() {
#endif

	using namespace pty::operators;

	TestPrintableOperations buf;
	auto values = make_tuple(pty::operators::all());

	std::ostream out(&buf);

	for_each_element(values, OutStream(out));

	TestOutStream f(buf);

	for_each_element(values, f);


	std::cout << "Test `printable operations` passed with success" << std::endl;

#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
