#ifndef GUARD_PTY_DETAILS_OPERATION_MACROS_HPP__
#define GUARD_PTY_DETAILS_OPERATION_MACROS_HPP__

#include "properties/helpers/downcast.hpp"

#define PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op, const_q, ret) \
	template<class T> \
		inline constexpr ret operator sym (T&& t) const_q { \
			return downcast(this).operator_base(pty::operators:: op(), std::forward<T>(t));\
		}

#define PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, const_q, ret) \
		inline constexpr ret operator sym () const_q { \
			return downcast(this).operator_base(pty::operators:: op());\
		}

#include "properties/details/define_operation.hpp"

#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op, const, decltype(auto))
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op,, decltype(auto))
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, const, decltype(auto))
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, decltype(auto))

#include "properties/details/prevent_duplication.hpp"

#define PTY_DETAILS_DEFINE_REVERSE_OPERATOR(sym, op, klass) \
	template<typename T, class U, class = details::prevent_duplication<T, klass>> \
		inline constexpr decltype(auto) operator sym(const T& lhv, const klass<U>& rhv) { \
			return rhv op lhv; \
		} \

#define PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR(sym, klass) PTY_DETAILS_DEFINE_REVERSE_OPERATOR(sym, sym, klass)

#endif
