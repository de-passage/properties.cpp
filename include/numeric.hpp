#ifndef GUARD_PTY_NUMERIC_HPP__
#define GUARD_PTY_NUMERIC_HPP__

#include "details/properties.hpp"
#include "arithmetic.hpp"
#include "comparable.hpp"
#include "bitwise.hpp"
#include "meta/enable_for.hpp"

namespace pty {
	template<class Base>
		struct Numeric;
	template<class Base, template<class> class ...Args>
		struct Numeric<details::Properties<Base, Args<Base>...>> : details::Properties<Base, Args<Base>..., Comparable<Base>, Arithmetic<Base>, Bitwise<Base>>{
			private:
				typedef details::Properties<Base, Args<Base>..., Comparable<Base>, Arithmetic<Base>, Bitwise<Base>> Parent;
			protected:
				using Parent::self;
				friend pty::details::Self<Base>;

			template<class Op, class = pty::enable_for<Op, pty::comparison_operation>>
				constexpr bool operator_base(const Op& op, const Numeric& i) const {
					return op(value(),  i.value());
				}

			template<class Op, class = pty::enable_for<Op, pty::arithmetic_operations>>
				constexpr Base operator_base(const Op& op, const Numeric& i) const {
					return Base(op(value(), i.value()));
				}

			template<class Op, class = pty::enable_for<Op, pty::arithmetic_operations>>
				constexpr Base operator_base(const Op& op, const Numeric& i) {
					return Base(op(value(), i.value()));
				}

			private:
				constexpr auto value() const {
					return self().value;
				}
				constexpr auto& value() {
					return self().value;
				}
		};
}
#endif
