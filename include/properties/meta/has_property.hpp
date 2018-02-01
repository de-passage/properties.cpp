#ifndef GUARD_PTY_META_HAS_PROPERTY_HPP__
#define GUARD_PTY_META_HAS_PROPERTY_HPP__

#include <type_traits>

namespace pty {
	namespace meta {
		namespace details {
			template<template<class>class Prop, typename Base>
				std::true_type check_if_has_property(const volatile Prop<Base>*);
			template<template<class>class Prop>
				std::false_type check_if_has_property(const volatile void*);
			template<typename Class, template<class>class Prop>
				using class_has_property = decltype(check_if_has_property<Prop>(std::declval<Class*>()));
		}

		template <typename Klass, template<typename> class Prop>
			constexpr bool has_property = details::class_has_property<Klass, Prop>::value;
	}
}
#endif // GUARD_PTY_META_HAS_PROPERTY_HPP__
