#ifndef GUARD_PTY_OPERATORS_ARITHMETIC_HPP__
#define GUARD_PTY_OPERATORS_ARITHMETIC_HPP__

#include "properties/details/operation_macros.hpp"
#include "properties/details/define_operator_base.hpp"
#include "properties/meta/tuple.hpp"
#include "properties/meta/tuple_operations.hpp"
#include "properties/details/arithmetic_operation_macro.hpp"

namespace pty {

	namespace operators {
		PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION)
		PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_MUTABLE_OPERATORS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION)
		PTY_DETAILS_APPLY_TO_ARITHMETIC_UNARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION)

		typedef pty::meta::tuple<
			pty::operators::plus_assign, 
			pty::operators::minus_assign, 
			pty::operators::multiply_assign, 
			pty::operators::divide_assign, 
			pty::operators::modulus_assign
				> mutating_arithmetic;

		typedef pty::meta::tuple< pty::operators::plus, 
			pty::operators::minus, 
			pty::operators::multiplies, 
			pty::operators::divides, 
			pty::operators::modulus, 
			pty::operators::negates, 
			pty::operators::positivates
				> constant_arithmetic;

		typedef pty::meta::concat<
			mutating_arithmetic,
			constant_arithmetic
				> arithmetic;
	}
}

#endif // GUARD_PTY_OPERATORS_ARITHMETIC_HPP__


