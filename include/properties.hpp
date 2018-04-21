#ifndef GUARD_PTY_PROPERTIES_HPP__
#define GUARD_PTY_PROPERTIES_HPP__

//#include "properties/details/properties.hpp"
#include "properties/meta/has_operator_base_overload.hpp"
#include <utility>


namespace pty {

	/** \brief Property holder. Creates the proper class hierarchy for the framework to do its work
	 *  
	 *  This class creates a list hierarchy of its parameters.
	 *
	 *  From a user point of view, this class is the basis of the Property framework. It is used both to declare the properties to 
	 *  apply to a given type, and the means to communicate with the different layers of the hierarchy.
	 *
	 *  Example
	 *  -------
	 *
	 *  The most general use of Property is as the parent class of a user-defined type :
	 *
	 *  ~~~{.cpp}
	 *  // Defines a type with bitwise operators overloaded and stream operators defined to work with std::stream
	 *  struct  MyPropertizedType :
	 *      pty::Properties<MyPropertizedType, pty::Streamable, pty::Bitwise> {
	 *
	 *      // Boilerplate to enable the framework functionalities
	 * 		friend pty::Adaptor<MyPropertizedType>;
	 * 		friend pty::Adaptor<const MyPropertizedType>;
	 *
	 * 		PTY_FORWARD_OPERATOR_BASE(pty::Properties<MyPropertizedType, pty::Streamable, pty::Bitwise>)
	 *
	 * 		// Forward _value to default operator behavior.
	 *		inline int& operator_base(pty::operators::cast) {
	 *			return value;
	 *		}
	 *
	 * 		// Same for constant operators
	 *		inline int operator_base(pty::operators::cast) const {
	 *			return value;
	 *		}
	 * 		
	 * 		int value;
	 *
	 *  };
	 *  ~~~
	 *
	 *  In this example, given an objet declared as `MyPropertizedType propertizedObject`{.cpp}, a call to `propertizedObject | 0x03`{.cpp} is equivalent to `_value | 0x03`{.cpp}.
	 *
	 *
	 *
	 *  Implementation
	 *  -------------
	 *  Properties create a list hierarchy by alternating itself and a member of its parameter list at a time.
	 *  Concretely, a call to `class Base : pty::Properties<Base, A, B>`,  will result in the following
	 *  hierarchy (namespace omitted):  
	 *  Properties<Base, A, B> -> A<Properties<Base, B>> -> Properties<Base, B> -> B<Properties<Base>> -> Properties<Base>
	 *
	 *  All inheritance is public and the resulting class Base will inherit from A, B and C.
	 *	 
	 */ 
    template<class T, template<class> class ...Args>
        struct Properties;

	/**
	 *	\fn auto pty::Properties::check_overload()
	 *	\memberof pty::Properties
	 *	\brief Check at compile time that the calling type contains an overload of operator_base matching the template parameters
	 *	\return A std::integral_constant<bool, Boolean> with Boolean being `true` if the overload is available, and `false` otherwise.
	 *
	 *	\fn auto pty::Properties::check_overload() const
	 *	\memberof pty::Properties
	 *	\copydoc check_overload()
	 */
	/// \cond INTERNAL
	template<class T, template<class> class Attribute, template<class>class...Args>
		struct Properties<T, Attribute, Args...> : Attribute<Properties<T, Args...>>{
			using Attribute<Properties<T, Args...>>::operator=;
        };

	template<class T>
		struct Properties<T> {
			template<class ...Args>
			constexpr auto check_overload() -> std::integral_constant<bool, ::pty::meta::check_operator_base_public_interface<T, Args...>> {
				return {};
			}

			template<class ...Args>
			constexpr auto check_overload() const -> std::integral_constant<bool, ::pty::meta::check_operator_base_public_interface<T, Args...>> {
				return {};
			}
		};
	/// \endcond

/** \brief Forwards the generic definition of operator_base to the parent
 *
 *  \sa pty::Properties
 */
#define PTY_FORWARD_OPERATOR_BASE(Base) \
	template<class _pty_Op, class ..._pty_Args>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class _pty_Op, class ..._pty_Args>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\

}

#endif
