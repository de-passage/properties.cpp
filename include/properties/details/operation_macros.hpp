#ifndef GUARD_PTY_DETAILS_OPERATION_MACROS_HPP__
#define GUARD_PTY_DETAILS_OPERATION_MACROS_HPP__

#define PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op, const_q) \
	template<class T> \
		inline constexpr auto operator sym (const T& t) const_q -> decltype(operator_base(op(), t)) {\
			return operator_base(op(),t);\
		}

#define PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, const_q) \
		inline constexpr auto operator sym () const_q{\
			return operator_base(op());\
		}

#include "properties/details/operation.hpp"

#include "properties/details/define_operation.hpp"

#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op, const)
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op,)
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, const)
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op,)

#include "properties/details/prevent_duplication.hpp"

#define PTY_DETAILS_DEFINE_REVERSE_OPERATOR(sym, op, klass) \
	template<typename T, class U, class = details::prevent_duplication<T, U, klass>> \
		inline constexpr auto operator sym(const T& lhv, const klass<U>& rhv) { \
			return rhv op lhv; \
		} \

#define PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR(sym, klass) PTY_DETAILS_DEFINE_REVERSE_OPERATOR(sym, sym, klass)

#endif
