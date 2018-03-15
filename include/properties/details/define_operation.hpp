#ifndef GUARD_PTY_DETAILS_DEFINE_OPERATION_HPP__
#define GUARD_PTY_DETAILS_DEFINE_OPERATION_HPP__

#include "properties/details/operation.hpp"


#define PTY_DETAILS_DEFINE_UNARY_OPERATION(op, sym) \
		struct sym { \
			template<class T> \
			inline constexpr decltype(auto) operator ()(T&& obj) const { \
				return op(obj);	\
			}	\
			static constexpr const char* const name = #sym; \
		}; \


#define PTY_DETAILS_DEFINE_BINARY_OPERATION(op, sym) \
		struct sym { \
			template<class T, class U> \
			inline constexpr decltype(auto) operator ()(T&& lhv, U&& rhv) const { \
				return lhv op rhv;	\
			}	\
			static constexpr const char* const name = "operator_"#sym "(" #op ")"; \
		};\


#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op)
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op)
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op)
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op)

#endif
