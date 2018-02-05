#ifndef GUARD_PTY_ITERABLE_HPP__
#define GUARD_PTY_ITERABLE_HPP__

#include "properties.hpp"
#include "properties/operators/iteration.hpp"
#include "properties/meta/enable_for.hpp"
#include "properties/incrementable.hpp"
#include "properties/addressable.hpp"

#include <utility>

namespace pty {
	template<class Base>
		struct Iterable : Base {

			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::iteration>>
				constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { 
					return Base::operator_base(op, std::forward<_pty_Args>(args)...);
				}
			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::iteration>>
				constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { 
					return Base::operator_base(op, std::forward<_pty_Args>(args)...);
				}
			using Base::operator=;

			constexpr inline decltype(auto) begin() const {
				return *downcast(this).operator_base(pty::operators::begin_iteration());
			}

			private:
			template<class Iter>
				struct Iterator : pty::Properties<Iterator<Iter>, pty::Incrementable, pty::Addressable> {
					private:
						Iter* _ref;

						template<class...Args>
							constexpr inline decltype(auto) _forward_to_ref(Args&&... args) {
								return downcast(_ref).operator_base(std::forward<Args>(args)...);

							}

						typedef decltype(std::declval<Iterator>()._forward_to_ref(pty::operators::begin_iteration())) _iterator_type;

						_iterator_type* iter;

					public:
						constexpr Iterator(_iterator_type* source = nullptr, Iterable* = nullptr) : _ref(source) {}

						constexpr inline decltype(auto) operator_base(pty::operators::prefix_shift) const {
						}

						constexpr inline decltype(auto) operator_base(pty::operators::suffix_shift) const {
						}


				};
			public:
			typedef Iterator<Iterable> iterator;
			typedef Iterator<const Iterable> const_iterator;

		};
}

#endif// GUARD_PTY_ITERABLE_HPP__
