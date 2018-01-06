#ifndef GUARD_PTY_DETAILS_DEFINE_OPERATION_HPP__
#define GUARD_PTY_DETAILS_DEFINE_OPERATION_HPP__

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


#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op, const)
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATION(sym, op,)
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op, const)
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATION(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATION(sym, op,)

#endif
