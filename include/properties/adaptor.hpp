#ifndef GUARD_PTY_ADAPTOR_HPP__
#define GUARD_PTY_ADAPTOR_HPP__

#include <utility>


namespace pty {

	template<class P>
		struct adaptor {
			P* self;

			explicit adaptor(P* p) : self(p) {}


			template<class Op, class ...Operand>
				inline constexpr decltype(auto) operator_base(const Op& op, Operand&&... oper) const { 
					return self->operator_base(op, std::forward<Operand>(oper)...);
				}

			template<class Op, class ...Operand>
				inline constexpr decltype(auto) operator_base(const Op& op, Operand&&... oper)  { 
					return self->operator_base(op, std::forward<Operand>(oper)...);
				}

			/*
			template<class Op>
				inline constexpr decltype(auto) operator_base(const Op& op) const { 
					return self->operator_base(op);
				}

			template<class Op>
				inline constexpr decltype(auto) operator_base(const Op& op) { 
					return self->operator_base(op);
				}
				*/

		};
}
#endif // GUARD_PTY_ADAPTOR_HPP__

