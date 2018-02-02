#ifndef GUARD_PTY_COMPARABLE_HPP__
#define GUARD_PTY_COMPARABLE_HPP__

#include "properties/details/operation_macros.hpp"
#include "properties/details/define_property.hpp"
#include "properties/details/define_operator_base.hpp"
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

    namespace operators {
      PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION) 

      typedef pty::meta::tuple<	pty::operators::less, 
              pty::operators::greater, 
              pty::operators::less_equal, 
              pty::operators::greater_equal, 
              pty::operators::equal_to, 
              pty::operators::not_equal_to
                  > comparison;
    }

	PTY_DETAILS_DEFINE_PROPERTY(Comparable,

		PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)
        PTY_DETAILS_DEFINE_OPERATOR_BASE(comparison)

		)

	PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR)
	PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_REVERSE_OPERATOR)
}

#undef PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS
#undef PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS
#undef PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS

#endif
