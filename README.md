# Properties
Properties is an experimental meta-programmation framework designed to simplify the declaration of common operations such as operator overloads, classic design patterns and so on.  
Properties is currently under intense development, the interface is subject to change.

# Example
The following example defines a class behaving in the exact same way as a built-in integer number.
```cpp
#include "properties.hpp"
#include "properties/numeric.hpp"
#include "properties/streamable.hpp"

#include <iostream>

struct Int : 
	pty::Properties<Int, // Declare our class to the framework
	pty::Numeric,        // Make it numeric, i.e. declare the operators +, +=, -, -=, ^, ^=, ==, <=, etc
	pty::Streamable> {	 // Make it compatible with stream operations. 
	                     // i.e. make it possible to call std::cout << Int() or std::cin >> Int()

	// Ctor
	constexpr Int(int v) : value(v) {}

	protected:

	int value;
	using Base = pty::Properties<Int, pty::Numeric, pty::Streamable>;

	// Without these, the framework can't access private functions and
	// the next declarations would need to be public
	friend pty::adaptor<Int>;
	friend pty::adaptor<const Int>;

	// This part exposes our member to the framework, essentially replacing our class
	// by the return value of this function every time an operator is called
	constexpr inline int& operator_base(const pty::operators::cast&) {
		return value; 
	}

	// const version. May be removed in future iterations of the framework
	constexpr inline int operator_base(const pty::operators::cast&) const {
		return value;
	}
};

int main() {
	Int i(42);
	std::cout << i << std::endl; // print  "42" 
	//int error = i + 10; // error no viable conversion from Int to int. 
	
	std::cout << i + 10 << std::endl; // Print 52

	return 0;
}
```
No special treatment is done so this class is not very useful in itself but it can be easily extended. The following example prints on the standard out buffer the operators and the operands it is called with.
```cpp
#include "properties.hpp"
#include "properties/numeric.hpp"
#include "properties/streamable.hpp"

#include <iostream>

namespace details { // Utility functions. Define how to print operations 

	// The example only uses those two 
	std::string _dispatch(pty::operators::stream_out) {
		return "operator<<";
	}

	std::string _dispatch(pty::operators::plus) {
		return "operator+";
	}

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
			std::cout << _dispatch(op) << "(";
			_print(args...);
			std::cout << ") called." << std::endl;
		}
}

struct Int : pty::Properties<Int, pty::Numeric, pty::Streamable> {

	// Ctor
	constexpr Int(int v) : value(v) {}

	protected:

	int value;
	using Base = pty::Properties<Int, pty::Numeric, pty::Streamable>;

	// Without these, the framework can't access private functions
	// and the next declarations would need to be public
	friend pty::adaptor<Int>;
	friend pty::adaptor<const Int>;

	// The two next functions define how the operations should be handled.
	// In our case we log the operator and the arguments, 
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
	std::cout << i << std::endl; // print "operator<<(std::ostream) called" then "42" 
	//int error = i + 10; // error no viable conversion from Int to int. 
	
	std::cout << i + 10 << std::endl; // Print "operator+(10) called", "operator<<(std::ostream) called", then 52

	return 0;
}
```
More example and documentations to come. For now please refer to the tests for examples of how to use the framework
