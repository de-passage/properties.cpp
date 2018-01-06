#ifndef GUARD_PTY_ARITHMETIC_HPP__
#define GUARD_PTY_ARITHMETIC_HPP__

#include "properties/details/operation_macros.hpp"

#include "properties/details/define_property.hpp"
#include "properties/meta/tuple.hpp"
#include "properties/meta/tuple_operations.hpp"

#define PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_MUTABLE_OPERATORS(fun) \
	fun(+=, plus_assign)\
	fun(-=, minus_assign)\
	fun(*=, multiply_assign)\
	fun(/=, divide_assign)\
	fun(%=, modulus_assign)

#define PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_CONST_OPERATORS(fun) \
	fun(+, plus)\
	fun(-, minus)\
	fun(*, multiplies)\
	fun(/, divides)\
	fun(%, modulus)

#define PTY_DETAILS_APPLY_TO_ARITHMETIC_UNARY_CONST_OPERATORS(fun) \
	fun(-, negates) \
	fun(+, positivates)

#define PTY_DETAILS_APPLY_TO_ARITHMETIC_TRANSITIVE_OPERATORS(fun) \
	fun(+, Arithmetic) \
	fun(-, Arithmetic)

namespace pty {

	PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION)
	PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_MUTABLE_OPERATORS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION)
	PTY_DETAILS_APPLY_TO_ARITHMETIC_UNARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION)

	PTY_DETAILS_DEFINE_PROPERTY(Arithmetic, 

			PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)
			PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_MUTABLE_OPERATORS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR)
			PTY_DETAILS_APPLY_TO_ARITHMETIC_UNARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR)

			)


	PTY_DETAILS_APPLY_TO_ARITHMETIC_TRANSITIVE_OPERATORS(PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR)

	typedef pty::tuple<
		pty::plus_assign, 
		pty::minus_assign, 
		pty::multiply_assign, 
		pty::divide_assign, 
		pty::modulus_assign
			> mutating_arithmetic_operations;

	typedef pty::tuple< pty::plus, 
		pty::minus, 
		pty::multiplies, 
		pty::divides, 
		pty::modulus, 
		pty::negates, 
		pty::positivates
			> constant_arithmetic_operations;

	typedef pty::meta::concat<
		mutating_arithmetic_operations,
		constant_arithmetic_operations
			> arithmetic_operations;

}


#undef PTY_DETAILS_APPLY_TO_BINARY_MUTABLE_ARITHMETIC_OPERATIONS
#undef PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_CONST_OPERATORS
#undef PTY_DETAILS_APPLY_TO_ARITHMETIC_UNARY_CONST_OPERATORS
#undef PTY_DETAILS_APPLY_TO_ARITHMETIC_TRANSITIVE_OPERATOR

#endif

