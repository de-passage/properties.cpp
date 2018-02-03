#ifndef GUARD_PTY_DETAILS_BITWISE_OPERATION_MACRO_HPP__
#define GUARD_PTY_DETAILS_BITWISE_OPERATION_MACRO_HPP__

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
  
#endif// GUARD_PTY_DETAILS_BITWISE_OPERATION_MACRO_HPP__
