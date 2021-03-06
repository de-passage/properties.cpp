#ifndef GUARD_PTY_DETAILS_META_HPP__
#define GUARD_PTY_DETAILS_META_HPP__

#include "properties/meta/tuple.hpp"

namespace pty {

	namespace meta {

		namespace details {

			//Placeholder structur
			struct placeholder{};

			//enable_if implementation
			template<bool B, class = placeholder>
				struct enable_if_t;
			template<class T>
				struct enable_if_t<true, T> {typedef T type;};

			//is_same implementation
			template<class T, class U>
				struct is_same_t {
					constexpr static const bool value = false;
				};
			template<class T>
				struct is_same_t<T, T> {
					constexpr static const bool value = true;
				};

			//OR implementation
			template<bool B, bool ...R>
				struct OR_t {
					static constexpr const bool value = B || OR_t<R...>::value;
				};
			template<bool B>
				struct OR_t<B> { 
					static constexpr const bool value = B;
				};

		}

		/** \typedef pty::meta::enable_if
		 *  \brief Metafunction that is undefined if the boolean parameter is false.
		 *  
		 *  Equivalent to std::enable_if_t, with two less characters.
		 */
		template<bool B, class T = details::placeholder>
			using enable_if = typename details::enable_if_t<B, T>::type;

		/** \var pty::meta::OR
		 *  \brief Is true if one of the conditions is true, false otherwise
		 *  Equivalent to (Args || ...) in C++17
		 */
		template<bool... T>
			constexpr static const bool OR = details::OR_t<T...>::value;

		/** \var pty::meta::is_same
		 *  \brief Is true if both parameters are the exact same type, false otherwise
		 */
		template<class T, class U>
			constexpr static const bool is_same = details::is_same_t<T, U>::value;
	}
}
#endif
