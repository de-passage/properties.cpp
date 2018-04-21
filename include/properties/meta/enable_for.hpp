#ifndef GUARD_PTY_META_ENABLE_FOR_HPP__
#define GUARD_PTY_META_ENABLE_FOR_HPP__

#include "properties/meta.hpp"


namespace pty {
	namespace meta {
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

		/** \class pty::meta::is_one_of
		 *  \brief Check if the first parameter is of the exact same type as one of the remaining types.
		 *
		 *  pty::meta::tuple contained in the parameter list are expanded to be checked against the target type.
		 *
		 *  \param T the type to check against
		 *  \param Args the type list to seach for T. pty::meta::tuple are searched for a match within their parameter list
		 */
		template<class T, class ...Args>
			constexpr static const bool is_one_of = details::is_one_of_t<T, Args...>::value;

		/** 
		 * \class pty::meta::enable_for
		 * \brief Metafunction that is only defined if its first parameter type is contained in the remaining list
		 *
		 *  This meta function is a basic tool to enable or disable given function overloads. It is meant for use in a SFINAE context.  
		 *  For an unevaluated type, see enable_for_t.
		 *
		 *  Typically this function can be used as a default for an unnamed template parameter of a user-defined operator_base in order to specify
		 *  which operators must be enabled for a given overload of the function. It is a shortcut for pty::meta::enable_if<pty::meta::is_one_of<T, Args...>>.
		 *
		 *  pty::meta::tuple contained in the parameter list are expanded to be checked against the target type.
		 *
		 *  Example
		 *  -------
		 *  ~~~{.cpp}
		 *  // Enable this specialization for Arithmetic operators (+, -, *=, etc)
		 *  template<class Operator, class Operand, class = pty::enable_for<Operator, pty::operators::arithmetic>>
		 *  decltype(auto) operator_base(const Operator& operator, const Operand& operand) {
		 *  	return operator(myDouble + 1, operand);
		 * 	}
		 *
		 *  // Enable this specialization for stream operations to or from a std::i/ostream
		 *  template<class Operator, class Operand, class = pty::enable_for<Operator, pty::operators::stream>, class>
		 *  decltype(auto) operator_base(const Operator& operator, const Operand& stream) {
		 *  	return operator(stream, "a string representation");
		 * 	}
		 * 	~~~
		 *
		 * \param T the type to check against
		 * \param Args the type list to search for T
		 * \sa pty::meta::disable_for, pty::meta::enable_for_t
		 */
		template<class T, class ...Args>
			using enable_for = enable_if<is_one_of<T, Args...>, T>;

		/** \class pty::meta::enable_for_t
		 *  \brief Same as enable_for but doesn't automatically tries to evaluate.
		 *  \sa enable_for
		 */
		template<class T, class ...Args>
			using enable_for_t = details::enable_if_t<is_one_of<T, Args...>, T>;

		/** \class pty::meta::disable_for
		 *  \brief Same as enable_for but is defined only if the type is not in the list of parameters.
		 *  \sa enable_for
		 */
		template<class T, class ...Args>
			using disable_for = enable_if<!is_one_of<T, Args...>, T>;
	}

}

#endif
