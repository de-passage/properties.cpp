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
			// Allows the user of the stream operators to send multiple values at once
			template<template<class> class Op>
				struct stream_adaptor {
					template<class T, class U, class ...R>
						inline constexpr auto&& operator()(T&& t, U&& u, R&&...r) const {
							return operator()(Op<T>()(std::forward<T>(t), std::forward<U>(u)), std::forward<R>(r)...);
						}
						
					template<class T, class U>
						inline constexpr auto&& operator()(T&& t, U&& u) const {
							return Op<T>()(std::forward<T>(t), std::forward<U>(u));
						}
				};

			// Actual operators
			template<class T>
				struct stream_out {
					template<class U>
						inline auto&& operator()(T&& oss, U&& t) const {
							return std::forward<T>(oss) << std::forward<U>(t);
						}
				};

			template<class T>
				struct stream_in {
					template<class U>
						inline auto&& operator()(T&& iss, U&& t) const {
							return std::forward<T>(iss) >> std::forward<U>(t);
						}
				};
		}

		using stream_in = details::stream_adaptor<details::stream_in>;
		using stream_out = details::stream_adaptor<details::stream_out>;


		typedef pty::tuple<stream_in, stream_out> stream_operations;


	}

	// Specialize the apply structure to account for the need to return a reference
	template<class Stream>
		struct apply<pty::operators::stream_in, Stream> {
			Stream& stream;
			template<class T>
			constexpr inline auto&& operator()(T&& t) const {
				return pty::operators::stream_in()(stream, std::forward<T>(t));
			}
		};

	template<class Stream>
		struct apply<pty::operators::stream_out, Stream> {
			Stream& stream;
			template<class T>
			constexpr inline auto&& operator()(T&& t) const {
				return pty::operators::stream_out()(stream, std::forward<T>(t));
			}
		};




	template<class T>
		struct Streamable : T {
			using T::operator=;

			PTY_FORWARD_OPERATOR_BASE(T)

			template<class S>
			constexpr inline auto&& operator_base(const pty::operators::stream_in&, S& stream) {
				return downcast(this).operator_base(pty::apply<pty::operators::stream_in, S&>{stream});
			}

			template<class S>
			constexpr inline auto&& operator_base(const pty::operators::stream_out&, S& stream) const {
				return downcast(this).operator_base(pty::apply<pty::operators::stream_out, S&>{stream});
			}
			template<class S>
			constexpr inline auto&& operator_base(const pty::apply<pty::operators::stream_in, S&>& op) {
				return op(downcast(this).operator_base(pty::operators::cast()));
			}

		};
//*
template<class S, class T>
	inline constexpr auto&& _stream_out(S& s,const Streamable<T>& t) {
	   return downcast(&t).operator_base(pty::operators::stream_out(), s);
	}

   template<class S, class U, class = std::enable_if_t<pty::meta::has_property<U, pty::Streamable>>>
   inline constexpr auto&& operator<<(S& t, const U& s) {
	   return _stream_out(t, s);
   }

template<class S, class T>
	inline constexpr auto&& _stream_in(S& s, Streamable<T>& t) {
	   return downcast(&t).operator_base(pty::operators::stream_in(), s);
	}
   template<class S, class U, class = std::enable_if_t<pty::meta::has_property<U, pty::Streamable>>>
   inline constexpr auto&& operator>>(S& t, U& s) {
	   return _stream_in(t, s);
   }
  // */
}
#endif // GUARD_PTY_STREAMABLE_HPP__
