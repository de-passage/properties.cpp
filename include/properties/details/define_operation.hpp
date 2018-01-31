#ifndef GUARD_PTY_DETAILS_DEFINE_OPERATION_HPP__
#define GUARD_PTY_DETAILS_DEFINE_OPERATION_HPP__

#include "properties/details/operation.hpp"


#define PTY_DETAILS_DEFINE_UNARY_OPERATION(op, sym, const_q, ref) \
		struct sym { \
			template<class T> \
			inline constexpr T ref operator ()(const_q T& obj) const { \
				return op(obj);	\
			}	\
		}; \


#define PTY_DETAILS_DEFINE_BINARY_OPERATION(op, sym, const_q, ref) \
		struct sym { \
			template<class T, class U> \
			inline constexpr T ref operator ()(const_q T& lhv, const U& rhv) const { \
				return lhv op rhv;	\
			}	\
		};\


#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op, const,)
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op,,&)
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op, const,)
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op,,&)

#endif
