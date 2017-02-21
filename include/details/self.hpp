#ifndef GUARD_PTY_DETAILS_SELF_HPP__
#define GUARD_PTY_DETAILS_SELF_HPP__

namespace pty {
	namespace details {
		template<class Base>
			struct Self {
				protected:
					inline ~Self() = default;

					inline constexpr const Base& self() const {
						return *static_cast<const Base*>(this);
					}

					inline constexpr Base& self() {
						return *static_cast<Base*>(this);
					}

					template<class Op, class Operand>
						inline constexpr auto operator_base(const Op& op, const Operand& oper) const { 
							return self().operator_base(op, oper);
						}

					template<class Op, class Operand>
						inline constexpr auto operator_base(const Op& op, const Operand& oper) { 
							return self().operator_base(op, oper);
						}

					template<class Op>
						inline constexpr auto operator_base(const Op& op) const { 
							return self().operator_base(op);
						}

					template<class Op, class Operand>
						inline constexpr auto operator_base(const Op& op) { 
							return self().operator_base(op);
						}
			};
	}
}
#endif
