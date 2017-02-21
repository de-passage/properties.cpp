#ifndef GUARD_PTY_META_ENABLE_FOR_HPP__
#define GUARD_PTY_META_ENABLE_FOR_HPP__

#include "meta.hpp"


namespace pty {
	// is_one_of Implementation
	namespace details {
		// Default case
		template<class T, class A, class ...Args>
			struct is_one_of_t {
				static constexpr const bool value = OR<is_same<T, A>, is_one_of_t<T, Args...>::value>;
			};

		// Terminal calse
		template<class T, class A>
			struct is_one_of_t<T, A> {
				static constexpr const bool value = is_same<T, A>;
			};

		// The current parameter is a tuple
		template<class T, class ...A1, class ...N>
			struct is_one_of_t<T, tuple<N...>, A1...> {
				static constexpr const bool value = is_one_of_t<T, N..., A1...>::value;
			};
		// The last parameter is a tuple
		template<class T, class ...N>
			struct is_one_of_t<T, tuple<N...>> {
				static constexpr const bool value = is_one_of_t<T, N...>::value;
			};
	}

	// is_one_of< typename test, typename ...args >
	// Returns true if test is of the exact same type as one of the types given as args.
	// pty::tuple contained in args are expanded to be checked against test
	template<class T, class ...Args>
		constexpr static const bool is_one_of = details::is_one_of_t<T, Args...>::value;

	template<class T, class ...Args>
		using enable_for = enable_if<is_one_of<T, Args...>, T>;
	template<class T, class ...Args>
		using disable_for = enable_if<!is_one_of<T, Args...>, T>;

}

#endif
