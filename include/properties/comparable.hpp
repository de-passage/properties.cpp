#ifndef GUARD_PTY_COMPARABLE_HPP__
#define GUARD_PTY_COMPARABLE_HPP__

#include "properties/details/operation_macros.hpp"
#include "properties/details/define_property.hpp"
#include "properties/meta/tuple.hpp"

#define PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(fun) \
	fun(<, less)\
	fun(<=, less_equal)\
	fun(>, greater)\
	fun(>=, greater_equal)\
	fun(==, equal_to)\
	fun(!=, not_equal_to)

#define PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS(fun) \
	fun(==, Comparable) \
	fun(!=, Comparable)

#define PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS(fun) \
	fun(<, >, Comparable) \
	fun(>, <, Comparable) \
	fun(<=, >=, Comparable) \
	fun(>=, <=, Comparable) \


namespace pty {

	PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION) 

	PTY_DETAILS_DEFINE_PROPERTY(Comparable,

		PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)

		)

	PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR)
	PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_REVERSE_OPERATOR)

	typedef pty::tuple<	pty::less, 
			pty::greater, 
			pty::less_equal, 
			pty::greater_equal, 
			pty::equal_to, 
			pty::not_equal_to
				> comparison_operation;
}

#undef PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS
#undef PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS
#undef PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS

#endif