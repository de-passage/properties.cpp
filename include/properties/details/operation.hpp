#ifndef GUARD_PTY_DETAILS_OPERATION_HPP__
#define GUARD_PTY_DETAILS_OPERATION_HPP__

namespace pty {
	namespace details {
	template<template<class> class Op>
		struct binary_operator {
			template<class T>
				inline constexpr auto operator()(const T& t, const T& u) const {
					return Op<T>()(t, u);
				}

			template<class T>
				inline constexpr auto operator()(T& t, const T& u) const {
					return Op<T>()(t, u);
				}
		};
	template<template<class> class Op>
		struct unary_operator {
			template<class T>
				inline constexpr auto operator()(const T& t) const {
					return Op<T>()(t);
				}

			template<class T>
				inline constexpr auto operator()(T& t) const {
					return Op<T>()(t);
				}
		};
	}
}
#endif

