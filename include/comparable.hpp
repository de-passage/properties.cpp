#ifndef GUARD_PTY_COMPARABLE_HPP__
#define GUARD_PTY_COMPARABLE_HPP__

#include "details/comparable_operations.hpp"
#include "details/prevent_duplication.hpp"
#include "details/operation_macros.hpp"

#define PTY_DETAILS_LIST_COMPARABLE_OPERATIONS(fun) \
	fun(<, less)\
fun(<=, less_equal)\
fun(>, greater)\
fun(>=, greater_equal)\
fun(==, equal_to)\
fun(!=, not_equal_to)

namespace pty {

	template<class Base>
		struct Comparable : Base {

			PTY_DETAILS_LIST_COMPARABLE_OPERATIONS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)

			protected:
				using Base::operator_base;
				inline ~Comparable() = default;
		};

	namespace details {
		template<class T, class U>
			using prevent_comp_duplication = pty::details::prevent_duplication<T, U, Comparable>;
	}

	template<class T, class U, class = details::prevent_comp_duplication<T, U>>
		inline constexpr bool operator>=(const T& lhv, const Comparable<U>& rhv) {
			return rhv <= lhv;
		}

	template<class T, class U, class = details::prevent_comp_duplication<T, U>>
		inline constexpr bool operator<=(const T& lhv, const Comparable<U>& rhv) {
			return rhv >= lhv;
		}

	template<class T, class U, class = details::prevent_comp_duplication<T, U>>
		inline constexpr bool operator<(const T& lhv, const Comparable<U>& rhv) {
			return rhv > lhv;
		}

	template<class T, class U, class = details::prevent_comp_duplication<T, U>>
		inline constexpr bool operator>(const T& lhv, const Comparable<U>& rhv) {
			return rhv < lhv;
		}

	template<class T, class U, class = details::prevent_comp_duplication<T, U>>
		inline constexpr bool operator==(const T& lhv, const Comparable<U>& rhv) {
			return rhv == lhv;
		}

	template<typename T, class U, class = details::prevent_comp_duplication<T, U>>
		inline constexpr bool operator!=(const T& lhv, const Comparable<U>& rhv) {
			return rhv != lhv;
		}
}
#endif
