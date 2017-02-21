#ifndef GUARD_PTY_DETAILS_ARITHMETIC_OPERATIONS
#define GUARD_PTY_DETAILS_ARITHMETIC_OPERATIONS

#include "details/operation.hpp"

#include <functional>

namespace pty {

	namespace details {
	template<class T>
		struct plus_assign{
			inline constexpr T& operator()(T& lhv, const T& rhv) const {
				return lhv += rhv;
			}
		};
	template<class T>
		struct minus_assign{
			inline constexpr T& operator()(T& lhv, const T& rhv) const {
				return lhv -= rhv;
			}
		};
	template<class T>
		struct multiply_assign{
			inline constexpr T& operator()(T& lhv, const T& rhv) const {
				return lhv *= rhv;
			}
		};
	template<class T>
		struct divide_assign{
			inline constexpr T& operator()(T& lhv, const T& rhv) const {
				return lhv /= rhv;
			}
		};
	template<class T>
		struct modulo_assign {
			inline constexpr T& operator()(T& lhv, const T& rhv) const {
				return lhv %= rhv;
			}
		};
	}

	using plus_assign = details::binary_operator<details::plus_assign>;
	using minus_assign = details::binary_operator<details::minus_assign>;
	using multiply_assign = details::binary_operator<details::multiply_assign>;
	using divide_assign = details::binary_operator<details::divide_assign>;
	using modulo_assign = details::binary_operator<details::modulo_assign>;
	using plus = details::binary_operator<std::plus>;
	using minus = details::binary_operator<std::minus>;
	using multiplies = details::binary_operator<std::multiplies>;
	using divides = details::binary_operator<std::divides>;
	using modulus = details::binary_operator<std::modulus>;
	using negate = details::unary_operator<std::negate>;
}

#endif
