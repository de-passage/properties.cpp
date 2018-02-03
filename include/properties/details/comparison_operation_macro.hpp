#ifndef GUARD_PTY_DETAILS_COMPARISON_OPERATION_MACRO
#define GUARD_PTY_DETAILS_COMPARISON_OPERATION_MACRO

#define PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(fun) \
	fun(<, less)\
	fun(<=, less_equal)\
	fun(>, greater)\
	fun(>=, greater_equal)\
	fun(==, equal_to)\
	fun(!=, not_equal_to)

#endif // GUARD_PTY_DETAILS_COMPARISON_OPERATION_MACRO
