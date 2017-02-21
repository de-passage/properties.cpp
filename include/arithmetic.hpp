#ifndef GUARD_PTY_ARITHMETIC_HPP__
#define GUARD_PTY_ARITHMETIC_HPP__

#include "details/operation_macros.hpp"
#include "details/aritmetic_operations.hpp"
#include "details/prevent_duplication.hpp"

#define PTY_DETAILS_LIST_ARITH_BIN_OPS(fun) \
	fun(+=, plus_assign)\
	fun(-=, minus_assign)\
	fun(*=, multiply_assign)\
	fun(/=, divide_assign)\
	fun(%=, modulo_assign)

#define PTY_DETAILS_LIST_CONST_ARITH_BIN_OPS(fun) \
	fun(+, plus)\
	fun(-, minus)\
	fun(*, multiplies)\
	fun(/, divides)\
	fun(%, modulus)

#define PTY_DETAILS_LIST_CONST_ARITHMETIC_UNARY_OPERATORS(fun) \
	fun(-, negate)



#define PTY_DETAILS_WRITE_ALL_ARITH_OPERATORS \
	PTY_DETAILS_LIST_CONST_ARITH_BIN_OPS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATOR)\
	PTY_DETAILS_LIST_ARITH_BIN_OPS(PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATOR) \
	PTY_DETAILS_LIST_CONST_ARITHMETIC_UNARY_OPERATORS(PTY_DETAILS_DEFINE_UNARY_CONST_OPERATOR)



namespace pty {
	template<class Base>
		struct Arithmetic : Base {

			PTY_DETAILS_WRITE_ALL_ARITH_OPERATORS

			protected:
			using Base::operator_base;
			~Arithmetic() = default;
		};

	namespace details {
		template<class T, class U>
			using prevent_arit_duplication = prevent_duplication<T, U, Arithmetic>;
	}
	template<typename T, class U, class = details::prevent_arit_duplication<T, U>>
		inline constexpr auto operator+(const T& lhv, const Arithmetic<U>& rhv) {
			return rhv + lhv;
		}

	template<typename T, class U, class = details::prevent_arit_duplication<T, U>>
		inline constexpr auto operator*(const T& lhv, const Arithmetic<U>& rhv) {
			return rhv * lhv;
		}

}


#endif

