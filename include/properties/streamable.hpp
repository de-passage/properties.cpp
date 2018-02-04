#ifndef GUARD_PTY_STREAMABLE_HPP__
#define GUARD_PTY_STREAMABLE_HPP__

#include "properties/details/operation.hpp"
#include "properties/details/define_property.hpp"

#include "properties/meta/has_property.hpp"
#include "properties/operators/cast.hpp"
#include "properties/helpers/downcast.hpp"

#include "properties/operators/stream.hpp"
#include "properties/details/define_operator_base.hpp"

namespace pty {

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
