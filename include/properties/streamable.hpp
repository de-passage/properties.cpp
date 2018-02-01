#ifndef GUARD_PTY_STREAMABLE_HPP__
#define GUARD_PTY_STREAMABLE_HPP__

#include "properties/meta/tuple.hpp"
#include "properties/details/operation.hpp"
#include "properties/details/define_property.hpp"

#include "properties/meta/has_property.hpp"
#include "properties/operators/cast.hpp"
#include "properties/apply.hpp"

namespace pty {
	namespace operators {
		namespace details {
			template<template<class> class Op>
				struct stream_adaptor {
					template<class T, class U, class ...R>
						inline constexpr auto operator()(const T& t, const U& u, const R&... r) const{
							return operator()(Op<T>()(t, u), r...);
						}

					template<class T, class U, class ...R>
						inline constexpr auto& operator()(T& t, const U& u, const R&... r) const {
							return operator()(Op<T>()(t, u), r...);
						}

					template<class T, class U, class ...R>
						inline constexpr auto operator()(const T& t, U& u, R&... r) const {
							return operator()(Op<T>()(t, u), r...);
						}

					template<class T, class U, class ...R>
						inline constexpr auto& operator()(T& t, U& u, R&... r) const {
							return operator()(Op<T>()(t, u), r...);
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
						inline T& operator()(T& iss, U& t) const {
							return iss >> t;
						}
					template<class U>
						inline T& operator()(T& iss, const U&) const {
							return iss;
						}
				};
		}

		using stream_in = details::stream_adaptor<details::stream_in>;
		using stream_out = details::stream_adaptor<details::stream_out>;


		typedef pty::tuple<stream_in, stream_out> stream_operations;


	}

	template<class T>
		struct Streamable : T {
			using T::operator=;
			PTY_FORWARD_OPERATOR_BASE(T)
			template<class S, class U, class>
				friend inline constexpr S& _stream_out(S& t, const Streamable& s);
			template<class S, class U, class>
				friend inline constexpr S& _stream_in(S& t, const Streamable& s);

			template<class S>
			constexpr inline S& operator_base(const pty::operators::stream_in& op, S& stream) {
				return pty::apply<pty::operators::stream_in, S&>{op, stream};
			}
		};
//*
template<class S, class T>
	inline constexpr S& _stream_out(S& s,const Streamable<T>& t) {
	   return downcast(&t).template operator_base_ref(pty::operators::stream_out(), s);
	}

   template<class S, class U, class = std::enable_if_t<pty::meta::has_property<U, pty::Streamable>>>
   inline constexpr S& operator<<(S& t, const U& s) {
	   return _stream_out(t, s);
   }

template<class S, class T>
	inline constexpr S& _stream_in(S& s, Streamable<T>& t) {
	   return downcast(&t).operator_base_ref(pty::operators::stream_in(), s);
	}
   template<class S, class U, class = std::enable_if_t<pty::meta::has_property<U, pty::Streamable>>>
   inline constexpr S& operator>>(S& t, U& s) {
	   return _stream_in(t, s);
   }
  // */
}
#endif // GUARD_PTY_STREAMABLE_HPP__
