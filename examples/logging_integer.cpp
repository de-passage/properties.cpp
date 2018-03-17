#include "properties.hpp"
#include "properties/numeric.hpp"
#include "properties/streamable.hpp"

#include "properties/helpers/printable_operators.hpp"

#include <iostream>

namespace details {

	template<class T>
	void _print(const T& t) { std::cout << t; }
	void _print(const std::ostream&) {
			std::cout << "std::ostream";
		}
	template<class T, class ...Args>
		void _print(const T& t, const Args&... args) {
			_print(t);
			std::cout << ", ";
			_print(args...);
		}

	template<class Op, class ...Args>
		void print_operation(const Op& op, const Args&... args) {
			std::cout << op << "(";
			_print(args...);
			std::cout << ") called." << std::endl;
		}
}

struct Int : 
	pty::Properties<Int,	// Declare our class to the framework
	pty::Numeric,			// Make it numeric, i.e. declare the operators +, +=, -, -=, ^, ^=, ==, <=, etc
	pty::Streamable> {		// Make it compatible with stream operations. Make it possible to call std::cout << Int() or std::cin >> Int()

	// Ctor
	constexpr Int(int v) : value(v) {}

	using Base = pty::Properties<Int, pty::Numeric, pty::Streamable>;
	using Base::operator=; // Required to enable default assignment behavior.

	protected:

	int value;

	// Without these, the framework can't access private functions and the next declarations would need to be public
	friend pty::adaptor<Int>;
	friend pty::adaptor<const Int>;

	// The two next functions define how the operations should be handled. In our case we log the operator and the arguments, 
	// then forward to the default behaviour
	template<class Operator, class...Args>
		constexpr inline decltype(auto) operator_base(const Operator& op, Args&&... args) {

			details::print_operation(op, args...); // Log
			return Base::operator_base(op, std::forward<Args>(args)...); // and forward

		}
	// Const version of above. May be removed in future iterations of the framework
	template<class Operator, class...Args>
		constexpr inline decltype(auto) operator_base(const Operator& op, Args&&... args) const {
			details::print_operation(op, args...);
			return Base::operator_base(op, std::forward<Args>(args)...);
		}

	// Conversion operation required to use the default behaviour of operations
	constexpr inline int& operator_base(const pty::operators::cast&) {
		return value; //
	}
	// const version. May be removed in future iterations of the framework
	constexpr inline int operator_base(const pty::operators::cast&) const {
		return value;
	}
};

int main() {
	Int i(42);
	std::cout << i << std::endl; // prints "operator_stream_out(<<)(std::ostream) called" then "42" 
	// int error = i + 10; // error no viable conversion from Int to int. 
	
	std::cout << i + 10 << std::endl; // Prints "operator_plus(+)(10) called", "operator_stream_out(<<)(std::ostream) called", then 52

	std::cout << i * 2 << std::endl; // Prints "operator_plus(*)(2) called", "operator_stream_out(<<)(std::ostream) called", then 84

	std::cout << std::boolalpha << (i >= 0) << std::endl; // Prints "operator_greater_equal(>=)(0) called" then true

	i = 9; // Prints "operator_assign(=)(9)

	// Operations return an object of the custom class 
	// so we can safely chain them and get the expected result 
	// (in this case it will print the addition then the comparison)
	std::cout << (i + 1 == 10) << std::endl;

	return 0;
}
