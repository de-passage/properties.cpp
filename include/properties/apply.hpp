#ifndef GUARD_PTY_APPLY_HPP_
#define GUARD_PTY_APPLY_HPP_

#include <tuple>

namespace pty {
	template<class Op, class ...Args>
	struct apply {
		Op op;
		std::tuple<Args...> arguments;

		template<class T>
		constexpr inline auto operator()(const T& t) const {
			return invoke(t, std::index_sequence_for<Args...>());
		}

		template<class T>
		constexpr inline auto operator()(T& t) const {
			return invoke(t, std::index_sequence_for<Args...>());
		}

		private:
		template<class T, size_t ...Is>
			constexpr inline auto invoke(const T& t, const std::index_sequence<Is...>&) const {
				return op(t, std::get<Is>(arguments)...);
			}

		template<class T, size_t ...Is>
			constexpr inline auto invoke(T& t, const std::index_sequence<Is...>&) const {
				return op(t, std::get<Is>(arguments)...);
			}
	};
}
#endif// GUARD_PTY_APPLY_HPP___
