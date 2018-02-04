#ifndef GUARD_PTY_COMPARABLE_HPP__
#define GUARD_PTY_COMPARABLE_HPP__

#include "properties/details/operation_macros.hpp"
#include "properties/details/define_property.hpp"
#include "properties/details/define_operator_base.hpp"
#include "properties/operators/comparison.hpp"

#define PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS(fun) \
	fun(==, Comparable) \
	fun(!=, Comparable)

#define PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS(fun) \
	fun(<, >, Comparable) \
	fun(>, <, Comparable) \
	fun(<=, >=, Comparable) \
	fun(>=, <=, Comparable) \

#define PTY_DETAILS_DEFINE_INNER_PROPS \
	template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::comparison>>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::comparison>>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class Op, class ...Args, class = pty::meta::enable_for<Op, pty::operators::comparison>> \
		inline constexpr bool operator_base(const Op& op, Args&&... args) const { \
			return op(downcast(this).operator_base(pty::operators::cast()), std::forward<Args>(args)...); \
		} \


namespace pty {

	PTY_DETAILS_DEFINE_PROPERTY(Comparable,

		PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)
		PTY_DETAILS_DEFINE_INNER_PROPS

		)

	PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR)
	PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_REVERSE_OPERATOR)
}

#undef PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS
#undef PTY_DETAILS_APPLY_TO_TRANSITIVE_COMPARISON_OPERATORS
#undef PTY_DETAILS_APPLY_TO_REVERSABLE_COMPARISON_OPERATORS
#undef PTY_DETAILS_DEFINE_INNER_PROPS

#endif
