#ifndef GUARD_PTY_ADAPTOR_HPP__
#define GUARD_PTY_ADAPTOR_HPP__

#include <utility>

#include "properties/meta.hpp"


namespace pty {

	template<class P>
		struct adaptor {
			P* self;

			constexpr explicit adaptor(P* p) : self(p) {}


			template<class Op, class ...Operand>
				inline constexpr decltype(auto) operator_base(const Op& op, Operand&&... oper) const { 
					return self->operator_base(op, std::forward<Operand>(oper)...);
				}

			template<class Op, class ...Operand>
				inline constexpr decltype(auto) operator_base(const Op& op, Operand&&... oper)  { 
					return self->operator_base(op, std::forward<Operand>(oper)...);
				}

			public:
			template<class ...Args>
				inline constexpr bool check_overload(Args&&... args) {
					return self->check_overload(args...);
				}

		};
}
#endif // GUARD_PTY_ADAPTOR_HPP__

