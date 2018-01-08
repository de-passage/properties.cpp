#ifndef GUARD_PTY_ADAPTOR_HPP__
#define GUARD_PTY_ADAPTOR_HPP__

namespace pty {
	template<class P>
		struct adaptor {
			P* self;

			explicit adaptor(P* p) : self(p) {}


			template<class Op, class Operand>
				inline constexpr auto operator_base(const Op& op, const Operand& oper) const { 
					return self->operator_base(op, oper);
				}

			template<class Op, class Operand>
				inline constexpr auto operator_base(const Op& op, const Operand& oper) { 
					return self->operator_base(op, oper);
				}

			template<class Op, class Operand>
				inline constexpr auto& operator_base(const Op& op, Operand& oper) const {
					return self->operator_base(op, oper);
				}

			template<class Op, class Operand>
				inline constexpr auto& operator_base(const Op& op, Operand& oper) { 
					return self->operator_base(op, oper);
				}

			template<class Op>
				inline constexpr auto operator_base(const Op& op) const { 
					return self->operator_base(op);
				}

			template<class Op, class Operand>
				inline constexpr auto operator_base(const Op& op) { 
					return self->operator_base(op);
				}
		};
}
#endif // GUARD_PTY_ADAPTOR_HPP__

