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

			static constexpr const char* const name = "operator_offset_iterator";
		};

		struct increment_iterator {
			template<class U, class T>
			constexpr inline decltype(auto) operator()(T&& iterator) const {
				return ++iterator;
			}
			static constexpr const char* const name = "operator_increment_iterator";
		};

		struct decrement_iterator {
			template<class U, class T>
			constexpr inline decltype(auto) operator()(T&& iterator) const {
				return --iterator;
			}
			static constexpr const char* const name = "operator_decrement_iterator";
		};

		struct iteration_start {
			template<class U>
				constexpr inline decltype(auto) operator()(U&& iterable) const {
					return iterable.begin();
				}
			static constexpr const char* const name = "operator_iteration_start";
		};

		struct iteration_end {
			template<class U>
				constexpr inline decltype(auto) operator()(U&& iterable) const {
					return iterable.end();
				}
			static constexpr const char* const name = "operator_iteration_end";
		};

		struct compare_iterators {
			template<class Op, class U>
				constexpr inline decltype(auto) operator()(Op op, U&& lhv, U&& rhv) const {
					return op(lhv, rhv);
				}
			static constexpr const char* const name = "operator_compare_iterators";
		};

		struct dereference_iterator {
			template<class T>
				constexpr inline decltype(auto) operator()(T&& iterator) const {
					return *iterator;
				}
			static constexpr const char* const name = "operator_dereference_iterators";
		};

		typedef pty::meta::tuple<offset_iterator, increment_iterator, decrement_iterator, dereference_iterator, compare_iterators, iteration_end, iteration_start> iteration;
	}
}

#endif // GUARD_PTY_OPERATORS_ITERATION_HPP__
