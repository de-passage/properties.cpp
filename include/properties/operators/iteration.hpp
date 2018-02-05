#ifndef GUARD_PTY_OPERATORS_ITERATION_HPP__
#define GUARD_PTY_OPERATORS_ITERATION_HPP__

#include "properties/meta/tuple.hpp"

namespace pty {
	namespace operators {
		struct offset_iterator {
			template<class U, class T>
			constexpr inline decltype(auto) operator()(T&& iterator, U&& offset) const {
				return iterator + offset;
			}
		};

		struct begin_iteration {
			template<class U>
				constexpr inline decltype(auto) operator()(U&& iterable) const {
					return iterable.begin();
				}
		};

		struct end_iteration {
			template<class U>
				constexpr inline decltype(auto) operator()(U&& iterable) const {
					return iterable.end();
				}
		};

		struct compare_iterators {
			template<class Op, class U>
				constexpr inline decltype(auto) operator()(Op op, U&& lhv, U&& rhv) const {
					return op(lhv, rhv);
				}
		};

		struct dereference_iterator {
			template<class T>
				constexpr inline decltype(auto) operator()(T&& iterator) const {
					return *iterator;
				}
		};

		typedef pty::meta::tuple<offset_iterator, compare_iterators, begin_iteration, end_iteration> iteration;
	}
}

#endif // GUARD_PTY_OPERATORS_ITERATION_HPP__
