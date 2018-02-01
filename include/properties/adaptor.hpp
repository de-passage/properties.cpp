#ifndef GUARD_PTY_ADAPTOR_HPP__
#define GUARD_PTY_ADAPTOR_HPP__

namespace pty {

	namespace details {

		template<class T> struct add_ref_if_not_void_t { typedef T& value; };
		template<> struct add_ref_if_not_void_t<void> { typedef void value; };
		template<class T>
			using add_ref_if_not_void = typename add_ref_if_not_void_t<T>::value;

		template<bool b, class T> struct add_ref_t { typedef T& value; };
		template<class T> struct add_ref_t<false, T> { typedef T value; };
		template<bool b, class T>
			using add_ref = typename add_ref_t<b, T>::value;
	}

	template<class P>
		struct adaptor {
			P* self;

			explicit adaptor(P* p) : self(p) {}


			template<class Op, class ...Operand, bool expects_reference = false>
				inline constexpr auto operator_base(const Op& op, const Operand&... oper) const -> details::add_ref<expects_reference, decltype(self->operator_base(op, oper...))> { 
					return self->operator_base(op, oper...);
				}

			template<class Op, class ...Operand, bool expects_reference = false>
				inline constexpr auto operator_base(const Op& op, const Operand&... oper)  -> details::add_ref<expects_reference, decltype(self->operator_base(op, oper...))> { 
					return self->operator_base(op, oper...);
				}

			template<class Op, class Ref, class ...Operand>
				inline constexpr Ref& operator_base_ref(const Op& op, Ref& r, const Operand&... oper) const {
					return self->operator_base(op, r, oper...);
				}

			template<class Op, class Ref, class ...Operand>
				inline constexpr Ref& operator_base_ref(const Op& op, Ref& r, const Operand&... oper)  {
					return self->operator_base(op, r, oper...);
				}
		};
}
#endif // GUARD_PTY_ADAPTOR_HPP__

