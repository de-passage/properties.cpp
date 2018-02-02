#ifndef GUARD_PTY_DETAILS_ARITHMETIC_OPERATION_MACRO
#define GUARD_PTY_DETAILS_ARITHMETIC_OPERATION_MACRO

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

#endif
