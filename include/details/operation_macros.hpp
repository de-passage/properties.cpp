#ifndef GUARD_PTY_DETAILS_OPERATION_MACROS_HPP__
#define GUARD_PTY_DETAILS_OPERATION_MACROS_HPP__

#define PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op, const_q) \
	template<class T> \
		inline constexpr auto operator sym (const T& t) const_q{\
			return operator_base(pty::op(),t);\
		}

#define PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, const_q) \
		inline constexpr auto operator sym () const_q{\
			return operator_base(pty::op());\
		}

#define PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op, const)
#define PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_BINARY_OPERATOR(sym, op,)
#define PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op, const)
#define PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATOR(sym, op) PTY_DETAILS_DEFINE_UNARY_OPERATOR(sym, op,)

#endif
