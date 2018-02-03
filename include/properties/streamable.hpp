#ifndef GUARD_PTY_STREAMABLE_HPP__
#define GUARD_PTY_STREAMABLE_HPP__

#include "properties/details/operation.hpp"
#include "properties/details/define_property.hpp"

#include "properties/meta/has_property.hpp"
#include "properties/operators/cast.hpp"
//#include "properties/apply.hpp"
#include "properties/helpers/downcast.hpp"

#include "properties/operators/stream.hpp"
#include "properties/details/define_operator_base.hpp"

namespace pty {
	/* Not needed anymore
	template<class Stream>
		struct apply<pty::operators::stream_in, Stream> {
			Stream& stream;
			template<class ...T>
			constexpr inline decltype(auto) operator()(T&&... t) const {
				return pty::operators::stream_in()(stream, std::forward<T>(t)...);
			}
		};

	template<class Stream>
		struct apply<pty::operators::stream_out, Stream> {
			Stream& stream;
			template<class ...T>
			constexpr inline decltype(auto) operator()(T&&... t) const {
				return pty::operators::stream_out()(stream, std::forward<T>(t)...);
			}
		};
	//*/



	template<class Base>
		struct Streamable : Base {
			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::stream>>
			constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { 
				return Base::operator_base(op, std::forward<_pty_Args>(args)...);
			}
			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::stream>>
			constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { 
				return Base::operator_base(op, std::forward<_pty_Args>(args)...);
			}
			template<class Op, class Stream, class O = Op, class = pty::meta::enable_for<O, pty::operators::stream>> 
				inline constexpr Stream& operator_base(const Op& op, Stream&& stream) const { 
					return op(std::forward<Stream>(stream), downcast(this).operator_base(pty::operators::cast())); 
				} 
			template<class Op, class Stream, class O = Op, class = pty::meta::enable_for<Op, pty::operators::stream>> 
				inline constexpr Stream& operator_base(const Op& op, Stream&& stream) { 
					return op(std::forward<Stream>(stream), downcast(this).operator_base(pty::operators::cast()));
				} 
			using Base::operator=;
		};
//*
	namespace details {
		/*
		template<class S, class T>
			inline constexpr decltype(auto) _stream_out(S& s,const Streamable<T>& t) {
			   return downcast(&t).operator_base(pty::apply<pty::operators::stream_out, S&>{s});
			}

		template<class S, class T>
			inline constexpr decltype(auto) _stream_in(S& s, Streamable<T>& t) {
			   return downcast(&t).operator_base(pty::apply<pty::operators::stream_in, S&>{s});
			}
			*/
		template<class S, class T>
			inline constexpr decltype(auto) _stream_out(S& stream,const Streamable<T>& streamable) {
			   return downcast(&streamable).operator_base(pty::operators::stream_out(), stream);
			}

		template<class S, class T>
			inline constexpr decltype(auto) _stream_in(S& stream, Streamable<T>& streamable) {
			   return downcast(&streamable).operator_base(pty::operators::stream_in(), stream);
			}
	}

   template<class S, class U, class = std::enable_if_t<pty::meta::has_property<U, pty::Streamable>>>
   inline constexpr decltype(auto) operator<<(S& t, const U& s) {
	   return details::_stream_out(t, s);
   }

   template<class S, class U, class = std::enable_if_t<pty::meta::has_property<U, pty::Streamable>>>
   inline constexpr decltype(auto) operator>>(S& t, U& s) {
	   return details::_stream_in(t, s);
   }
  // */
}
#endif // GUARD_PTY_STREAMABLE_HPP__
