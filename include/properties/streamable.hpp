#ifndef GUARD_PTY_STREAMABLE_HPP__
#define GUARD_PTY_STREAMABLE_HPP__

#include "properties/operators/cast.hpp"
#include "properties/helpers/downcast.hpp"

#include "properties/operators/stream.hpp"
#include "properties/meta/enable_for.hpp"

namespace pty {

	/** \brief Property enabling the use of stream operators (`<<` and `>>`)
	 *
	 *  Adding this property to a class will give it the capability to interface with utilities such as std::cin, std::cout and other
	 *  streams.
	 *
	 *  The only requirement is to treat the operator in an operator_base function in the base class, either directly or by returning an 
	 *  appropriate type (for which the stream operator already makes sense) from the pty::operators::cast overload.
	 *
	 *  Stream operators functors defined by the framework take a variadic number of arguments, allowing to stream several values in or out
	 *  of the class in a single line.
	 *
	 *  Example
	 *  -------
	 *  ~~~{.cpp}
	 *  struct Example : pty::Properties<pty::Streamable> {
	 *
	 * 		PTY_FORWARD_OPERATOR_BASE(pty::Properties<pty::Streamable>)
	 *
	 * 		template<class Stream>
	 * 		decltype(auto) operator_base(pty::operators::stream_out op, Stream& stream) const {
	 * 			op(stream, x, " ", y, " ", z);
	 * 		}
	 *
	 * 		template<class Stream>
	 * 		decltype(auto) operator_base(pty::operators::stream_out op, Stream& stream) {
	 * 			op(stream, x, y, z);
	 * 		}
	 *
	 * 		int x, y, z;
	 * 	}
	 *
	 * 	Example example;
	 * 	std::cin >> example; // Waits for 3 values to be typed in
	 * 	std::cout << example;  // Prints the 3 values separated by whitespaces
	 *  ~~~
	 *
	 *  Hopefully future iterations of the framework will allow for a single overload to handle both operators.
	 *  
	 *  \sa pty::operators::stream_in, pty::operators::stream_out, pty::operators::stream
	 *
	 *  \todo 
	 *   + Hunt for potential conflicts over operator<</>> in classes with both the Streamable and Bitwise properties
	 *   + Implement a unified interface for Streamable allowing a single function to define both in and out streaming operations.\n
	 *  Use const_cast && make stream_in::operator() do nothing on pointers and constant values
	 */
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

    template<class S, class U>
        inline constexpr decltype(auto) operator<<(S& stream, const Streamable<U>& streamable) {
            return downcast(&streamable).operator_base(pty::operators::stream_out(), stream);
        }

    template<class S, class U>
        inline constexpr decltype(auto) operator>>(S& stream, Streamable<U>& streamable) {
            return downcast(&streamable).operator_base(pty::operators::stream_in(), stream);
        }
}
#endif // GUARD_PTY_STREAMABLE_HPP__
