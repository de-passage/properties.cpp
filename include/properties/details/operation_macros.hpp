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

#define PTY_DETAILS_DEFINE_UNARY_OPERATION(op, sym, const_q) \
	namespace details { \
		template<class T> \
			struct sym { \
				inline constexpr T operator ()(const_q T& obj) const { \
					return op(obj);	\
				}	\
			}; \
	} \
	using sym = pty::details::unary_operator<details::sym>;


#define PTY_DETAILS_DEFINE_BINARY_OPERATION(op, sym, const_q) \
	namespace details { \
		template<class T> \
			struct sym { \
				inline constexpr T operator ()(const_q T& lhv, const T& rhv) const { \
					return lhv op rhv;	\
				}	\
			};\
	} \
	using sym = pty::details::binary_operator<details::sym>;

#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op, const)
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op,)
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, const)
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op,)

#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op, const)
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op,)
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op, const)
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op,)

#include "properties/details/prevent_duplication.hpp"

#define PTY_DETAILS_DEFINE_REVERSE_OPERATOR(sym, op, klass) \
	template<typename T, class U, class = details::prevent_duplication<T, U, klass>> \
		inline constexpr auto operator sym(const T& lhv, const klass<U>& rhv) { \
			return rhv op lhv; \
		} \

#define PTY_DETAILS_DEFINE_TRANSITIVE_OPERATOR(sym, klass) PTY_DETAILS_DEFINE_REVERSE_OPERATOR(sym, sym, klass)

#endif
