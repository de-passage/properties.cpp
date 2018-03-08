#ifndef GUARD_PTY_ARITHMETIC_HPP__
#define GUARD_PTY_ARITHMETIC_HPP__

#include "properties/details/define_property.hpp"

#include "properties/operators/arithmetic.hpp"

#define PTY_DETAILS_APPLY_TO_ARITHMETIC_TRANSITIVE_OPERATORS(fun) \
	fun(+, Arithmetic) \
	fun(*, Arithmetic)

namespace pty {

	PTY_DETAILS_DEFINE_PROPERTY(Arithmetic, 

			PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)
			PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_MUTABLE_OPERATORS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR)
			PTY_DETAILS_APPLY_TO_ARITHMETIC_UNARY_CONST_OPERATORS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR)

			PTY_DETAILS_DEFINE_OPERATOR_BASE(arithmetic)

			)


	PTY_DETAILS_APPLY_TO_ARITHMETIC_TRANSITIVE_OPERATORS(PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR)

	template<class T, class U, class = pty::details::prevent_duplication<T, Arithmetic>>
	inline constexpr auto operator-(const T& lhv, const Arithmetic<U>& rhv) {
		return -(rhv) + lhv;
	}

	template<class T, class U, class = pty::details::prevent_duplication<T, Arithmetic>>
	inline constexpr auto operator/(const T& lhv, const Arithmetic<U>& rhv) {
		return lhv / downcast(&rhv).operator_base(pty::operators::cast());
	}

	template<class T, class U, class = pty::details::prevent_duplication<T, Arithmetic>>
	inline constexpr auto operator%(const T& lhv, const Arithmetic<U>& rhv) {
		return lhv % downcast(&rhv).operator_base(pty::operators::cast());
	}

}


#undef PTY_DETAILS_APPLY_TO_BINARY_MUTABLE_ARITHMETIC_OPERATIONS
#undef PTY_DETAILS_APPLY_TO_ARITHMETIC_BINARY_CONST_OPERATORS
#undef PTY_DETAILS_APPLY_TO_ARITHMETIC_UNARY_CONST_OPERATORS
#undef PTY_DETAILS_APPLY_TO_ARITHMETIC_TRANSITIVE_OPERATOR

#endif

