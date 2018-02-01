#ifndef GUARD_PTY_ADAPTOR_HPP__
#define GUARD_PTY_ADAPTOR_HPP__

#include <utility>


namespace pty {

	template<class P>
		struct adaptor {
			P* self;

			explicit adaptor(P* p) : self(p) {}


			template<class Op, class ...Operand, bool expects_reference = false>
				inline constexpr auto operator_base(const Op& op, Operand&&... oper) const -> decltype(self->operator_base(op,  std::forward<Operand>(oper)...)) { 
					return self->operator_base(op, std::forward<Operand>(oper)...);
				}

			template<class Op, class ...Operand, bool expects_reference = false>
				inline constexpr auto operator_base(const Op& op, Operand&&... oper)  -> decltype(self->operator_base(op,  std::forward<Operand>(oper)...)) { 
					return self->operator_base(op, std::forward<Operand>(oper)...);
				}
		};
}
#endif // GUARD_PTY_ADAPTOR_HPP__

