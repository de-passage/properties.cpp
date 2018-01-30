#ifndef GUARD_PTY_STREAMABLE_HPP__
#define GUARD_PTY_STREAMABLE_HPP__

#include "properties/meta/tuple.hpp"
#include "properties/details/operation.hpp"

namespace pty {
	namespace operators {
		namespace details {
			template<template<class> class Op>
				struct stream_adaptor {
					template<class T, class U, class ...R>
						inline constexpr auto operator()(const T& t, const U& u, R... r) const{
							return operator()(Op<T>(t, u), r...);
						}

					template<class T, class U, class ...R>
						inline constexpr auto& operator()(T& t, const U& u, R... r) const {
							return operator()(Op<T>(t, u), r...);
						}

					template<class T, class U, class ...R>
						inline constexpr auto operator()(const T& t, U& u, R... r) const {
							return operator()(Op<T>(t, u), r...);
						}

					template<class T, class U, class ...R>
						inline constexpr auto& operator()(T& t, U& u, R... r) const {
							return operator()(Op<T>(t, u), r...);
						}

					template<class T, class U>
						inline constexpr auto operator()(const T& t, const U& u) const {
							return Op<T>()(t, u);
						}

					template<class T, class U>
						inline constexpr auto operator()(const T& t, U& u) const {
							return Op<T>()(t, u);
						}

					template<class T, class U>
						inline constexpr auto& operator()(T& t, U& u) const {
							return Op<T>()(t, u);
						}

					template<class T, class U>
						inline constexpr auto& operator()(T& t, const U& u) const {
							return Op<T>()(t, u);
						}
				};
			template<class T>
				struct stream_out {
					template<class U>
						inline T& operator()(T& oss, const U& t) const {
							return oss << t;
						}
				};

			template<class T>
				struct stream_in {
					template<class U>
						inline T& operator()(T& oss, U& t) const {
							return oss >> t;
						}
					template<class U>
						inline T& operator()(T& oss, const U&) const {
							return oss;
						}
				};
		}

		using stream_in = details::stream_adaptor<details::stream_in>;
		using stream_out =details::stream_adaptor<details::stream_out>;


		typedef pty::tuple<stream_in, stream_out> stream_operations;


	}

	template<class T>
		struct Streamable : T {
			template<class S, class U>
				friend inline constexpr S& operator<<(S& t, const Streamable<U>& s);/* {
					return downcast(&s).operator_base(pty::operators::stream_out(), t);
				}*/

			template<class S, class U>
				friend inline constexpr S& operator>>(S& t, pty::Streamable<U>& s);/* {
					return downcast(&s).operator_base(pty::operators::stream_in(), t);
				}*/

		};
//*
   template<class S, class U>
   inline constexpr S& operator<<(S& t, const pty::Streamable<U>& s) {
   return downcast(&s).operator_base(pty::operators::stream_out(), t);
   }

   template<class S, class U>
   inline constexpr S& operator>>(S& t, pty::Streamable<U>& s) {
   return downcast(&s).operator_base(pty::operators::stream_in(), t);
   }
  // */
}
#endif // GUARD_PTY_STREAMABLE_HPP__
