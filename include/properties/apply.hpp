#ifndef GUARD_PTY_APPLY_HPP_
#define GUARD_PTY_APPLY_HPP_

#include <tuple>
#include <utility>

namespace pty {
	template<class Op, class ...Args>
	struct apply {
		Op op;
		std::tuple<Args...> arguments;


		private:
		template<class T, size_t ...Is>
			constexpr inline decltype(auto) invoke(const T& t, const std::index_sequence<Is...>&) const {
				return op(t, std::get<Is>(arguments)...);
			}

		template<class T, size_t ...Is>
			constexpr inline decltype(auto) invoke(T& t, const std::index_sequence<Is...>&) const {
				return op(t, std::get<Is>(arguments)...);
			}

		public:
		template<class T>
		constexpr inline decltype(auto) operator()(const T& t) const {
			return invoke(t, std::index_sequence_for<Args...>());
		}

		template<class T>
		constexpr inline decltype(auto) operator()(T& t) const {
			return invoke(t, std::index_sequence_for<Args...>());
		}
	};
}
#endif// GUARD_PTY_APPLY_HPP___
