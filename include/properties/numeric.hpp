#ifndef GUARD_PTY_NUMERIC_HPP__
#define GUARD_PTY_NUMERIC_HPP__

#include "properties/details/properties.hpp"
#include "properties/arithmetic.hpp"
#include "properties/comparable.hpp"
#include "properties/bitwise.hpp"
#include "properties/meta/enable_for.hpp"
#include "properties/meta/property_hierarchy_info.hpp"
#include "properties/helpers/downcast.hpp"
#include "properties/helpers/apply.hpp"
#include "properties/operators/cast.hpp"
#include "properties/permissions.hpp"

#include <type_traits>


namespace pty {
	template<class Base>
		struct Numeric;

	template<class ...Args>
	struct NumericCompatible {
		template<class ...>
		struct CompatibleWith;

		template<class Base>
		struct value : Base {
			typedef meta::remove<permissions::Write, meta::remove<permissions::Read, permissions::get<Base>>> Permissions;
		};

	};

	template<class Base, template<class> class ...Args>
		// Forward properties and add comparable, arithmetic and bitwise to them
		struct Numeric<details::Properties<Base, Args<Base>...>> : details::Properties<Base, Comparable<Base>, Arithmetic<Base>, Bitwise<Base>, Args<Base>...>{
			private:
				typedef details::Properties<Base, Args<Base>..., Comparable<Base>, Arithmetic<Base>, Bitwise<Base>> Parent;
				typedef Numeric<details::Properties<Base, Args<Base>...>> Self;

				template<class Ret, class Op, class T>
					constexpr static inline pty::apply_left<Op, Ret, T> apply_left(const Op&, const T& t) {
						return pty::apply_left<Op, Ret, T>(t);
					}
			constexpr static auto cast_to_valid_type(const Numeric& i) {
				return downcast(&i).operator_base(pty::operators::cast());
			}

			using _perms = pty::permissions::get<Parent>;


			protected:
				~Numeric() = default;
				friend pty::adaptor<Base>;
				friend pty::adaptor<const Base>;

			template<class Op, class = pty::enable_for<Op, pty::comparison_operation>>
				constexpr bool operator_base(const Op& op, const Numeric& i) const {
					return downcast(this).operator_base(Numeric::apply_left<bool>(op, Numeric::cast_to_valid_type(i)));
				}

			template<class Op, class = pty::enable_for<Op, pty::arithmetic_operations, pty::bitwise_operations>>
				constexpr auto operator_base(const Op& op, const Numeric& i) const {
					return downcast(this).operator_base(Numeric::apply_left<pty::meta::get_base<Base>>(op, Numeric::cast_to_valid_type(i)));
				}

			template<class Op, class = pty::enable_for<Op, pty::arithmetic_operations, pty::bitwise_operations>>
				constexpr Base operator_base(const Op& op, const Numeric& i) {
					return downcast(this).operator_base(Numeric::apply_left<pty::meta::get_base<Base>>(op, Numeric::cast_to_valid_type(i)));
				}
//*
			template<class Op, class T, class = pty::enable_for<Op, pty::comparison_operation>, class = std::enable_if_t<!std::is_base_of<Numeric, T>::value>>
				constexpr bool operator_base(const Op& op, const T& i) const {
					return downcast(this).operator_base(Numeric::apply_left<bool>(op, i));
				}

			template<class Op, class T, class = pty::enable_for<Op, pty::arithmetic_operations, pty::bitwise_operations>, class = std::enable_if_t<!std::is_base_of<Numeric, T>::value>>
				constexpr auto operator_base(const Op& op, const T& i) const {
					return downcast(this).operator_base(Numeric::apply_left<pty::meta::get_base<Base>>(op, i));
				}

			template<class Op, class T, class = pty::enable_for<Op, pty::arithmetic_operations, pty::bitwise_operations>, class = std::enable_if_t<!std::is_base_of<Numeric, T>::value>>
				constexpr Base operator_base(const Op& op, const T& i) {
					return downcast(this).operator_base(Numeric::apply_left<pty::meta::get_base<Base>>(op, i));
				}
				//*/

		};
}
#endif
