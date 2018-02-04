#ifndef GUARD_PTY_ADDRESSABLE_HPP__
#define GUARD_PTY_ADDRESSABLE_HPP__

#include "properties/meta/enable_for.hpp"
#include "properties/operators/index.hpp"
#include "properties/operators/cast.hpp"
#include "properties/helpers/downcast.hpp"

#include <stddef.h>
#include <utility>

namespace pty {

	template<class T>
		struct Addressable : T {
			using T::operator=;

			template<class U>
			constexpr inline decltype(auto) operator[](U&& index) const {
				return downcast(this).operator_base(operators::index(), std::forward<U>(index));
			}

			template<class U>
			constexpr inline decltype(auto) operator[](U&& index) {
				return downcast(this).operator_base(operators::index(), std::forward<U>(index));
			}

			constexpr inline decltype(auto) operator*() const {
				return downcast(this).operator_base(operators::dereference());
			}
			constexpr inline decltype(auto) operator->() const {
				return downcast(this).operator_base(operators::dereference_member());
			}

			constexpr inline decltype(auto) operator*() {
				return downcast(this).operator_base(operators::dereference());
			}
			constexpr inline decltype(auto) operator->() {
				return downcast(this).operator_base(operators::dereference_member());
			}

			template<class Op, class ...Args, class = pty::meta::enable_for<Op, pty::operators::address>>
            constexpr inline decltype(auto) operator_base(Op op, Args&&... index) {
                return op(downcast(this).operator_base(pty::operators::cast()), std::forward<Args>(index)...);
            }

			template<class Op, class ...Args, class = pty::meta::enable_for<Op, pty::operators::address>>
            constexpr inline decltype(auto) operator_base(Op op, Args&&... index) const {
                return op(downcast(this).operator_base(pty::operators::cast()), std::forward<Args>(index)...);
            }

            template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::address>>
            constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { 
                return T::operator_base(op, std::forward<_pty_Args>(args)...);
            }
            template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::address>>
            constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { 
                return T::operator_base(op, std::forward<_pty_Args>(args)...);
            }
		};


}

#endif // GUARD_PTY_ADDRESSABLE_HPP__
