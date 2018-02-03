#ifndef GUARD_PTY_OPERATORS_BITWISE_HPP__
#define GUARD_PTY_OPERATORS_BITWISE_HPP__

#include "properties/details/bitwise_operation_macro.hpp"
#include "properties/details/operation_macros.hpp"
#include "properties/meta/tuple.hpp"
#include "properties/meta/tuple_operations.hpp"

namespace pty {
	namespace operators {
		PTY_DETAILS_APPLY_TO_BITWISE_BINARY_CONST_OPERATIONS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION)
		PTY_DETAILS_APPLY_TO_BITWISE_BINARY_MUTABLE_OPERATIONS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION)
		PTY_DETAILS_APPLY_TO_BITWISE_UNARY_OPERATIONS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION)

		typedef pty::meta::tuple< bitwise_and, 
				bitwise_or, 
				bitwise_xor, 
				shift_left, 
				shift_right, 
				bitwise_not > constant_bitwise; 

		typedef pty::meta::tuple< bitwise_or_assign, 
				bitwise_and_assign, 
				bitwise_xor_assign, 
				shift_left_assign, 
				shift_right_assign > mutating_bitwise;

		typedef pty::meta::concat<constant_bitwise, mutating_bitwise> bitwise;
	}
}

#endif// GUARD_PTY_OPERATORS_BITWISE_HPP__
