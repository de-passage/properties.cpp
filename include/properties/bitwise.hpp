#ifndef GUARD_PTY_BITWISE_HPP__
#define GUARD_PTY_BITWISE_HPP__

#include "properties/details/operation_macros.hpp"
#include "properties/details/define_property.hpp"
#include "properties/meta/tuple.hpp"
#include "properties/meta/tuple_operations.hpp"

#define PTY_DETAILS_APPLY_TO_TRANSITIVE_BITWISE_OPERATIONS(op) \
	op(&, Bitwise)\
	op(|, Bitwise)\
	op(^, Bitwise)\

#define PTY_DETAILS_APPLY_TO_BITWISE_BINARY_CONST_OPERATIONS(op) \
	op(&, bitwise_and) \
	op(|, bitwise_or) \
	op(^, bitwise_xor) \
	op(<<, shift_left) \
	op(>>, shift_right)

#define PTY_DETAILS_APPLY_TO_BITWISE_BINARY_MUTABLE_OPERATIONS(op) \
	op(&=, bitwise_and_assign) \
	op(|=, bitwise_or_assign) \
	op(^=, bitwise_xor_assign) \
	op(<<=, shift_left_assign) \
	op(>>=, shift_right_assign)

#define PTY_DETAILS_APPLY_TO_BITWISE_UNARY_OPERATIONS(op) \
	op(~, bitwise_not)


namespace pty {

PTY_DETAILS_APPLY_TO_BITWISE_BINARY_CONST_OPERATIONS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION)
PTY_DETAILS_APPLY_TO_BITWISE_BINARY_MUTABLE_OPERATIONS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION)
PTY_DETAILS_APPLY_TO_BITWISE_UNARY_OPERATIONS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION)

PTY_DETAILS_DEFINE_PROPERTY(Bitwise, 
		PTY_DETAILS_APPLY_TO_BITWISE_BINARY_CONST_OPERATIONS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)
		PTY_DETAILS_APPLY_TO_BITWISE_BINARY_MUTABLE_OPERATIONS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR)
		PTY_DETAILS_APPLY_TO_BITWISE_UNARY_OPERATIONS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR)
		)

PTY_DETAILS_APPLY_TO_TRANSITIVE_BITWISE_OPERATIONS(PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR)



typedef tuple< bitwise_and, 
		bitwise_or, 
		bitwise_xor, 
		shift_left, 
		shift_right, 
		bitwise_not > constant_bitwise_operations; 

typedef tuple< bitwise_or_assign, 
		bitwise_and_assign, 
		bitwise_xor_assign, 
		shift_left_assign, 
		shift_right_assign > mutating_bitwise_operations;
typedef meta::concat<constant_bitwise_operations, mutating_bitwise_operations> bitwise_operations;

}

#undef PTY_DETAILS_APPLY_TO_TRANSITIVE_BITWISE_OPERATIONS
#undef PTY_DETAILS_APPLY_TO_BITWISE_BINARY_CONST_OPERATIONS
#undef PTY_DETAILS_APPLY_TO_BITWISE_BINARY_MUTABLE_OPERATIONS

#endif
