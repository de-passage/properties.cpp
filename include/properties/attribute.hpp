#ifndef GUARD_PTY_ATTRIBUTE_HPP__
#define GUARD_PTY_ATTRIBUTE_HPP__

#include <type_traits>
#include <utility>

#include "properties.hpp"

#include "properties/permissions.hpp"
#include "properties/streamable.hpp"
#include "properties/numeric.hpp"
#include "properties/meta/property_hierarchy_info.hpp"


namespace pty {
	namespace meta {
		template<typename Tuple>
			struct apply_tuple;

		template<typename ...Args>
			struct apply_tuple<pty::meta::tuple<Args...>> {
				template<class T>
					struct value : pty::details::Properties<pty::meta::get_base<T>, Args...> {
						using pty::details::Properties<pty::meta::get_base<T>, Args...>::operator=;
					};
			};

		template<>
			struct apply_tuple<pty::meta::tuple<>> {
				template<class T>
					struct value : pty::details::Properties<pty::meta::get_base<T>> {
						using pty::details::Properties<pty::meta::get_base<T>>::operator=;
					};
			};
	}

	namespace details {

		template<bool B, template<class> class T>
			struct AttributeAdaptor {
				template<class R>
					struct value : R{
						using R::operator=;
					};
			};
		template<template<class>class T>
			struct AttributeAdaptor<true, T> {
				template<class R>
					struct value : pty::details::Properties<meta::get_base<R>, T<meta::get_base<R>>, typename meta::apply_tuple<::pty::meta::get_properties<R>>::template value<meta::get_base<R>>> {
						typedef pty::details::Properties<meta::get_base<R>, T<meta::get_base<R>>, typename meta::apply_tuple<::pty::meta::get_properties<R>>::template value<meta::get_base<R>>> Base;
						using Base::operator=;
					};
			};
	}

#define BASE \
	pty::Properties<Attribute<T, Owner, Args...>, Args..., Numeric, Streamable>

	/*
	Properties< \
	Attribute<T, Owner, Args...>, \
	Args..., \
	details::AttributeAdaptor<std::is_arithmetic<T>::value, Streamable>::template value, \
	details::AttributeAdaptor<std::is_arithmetic<T>::value, Numeric>::template value, \
	ReadOnly>  */

	template<class T, class Owner, template<class>class ...Args>
		struct Attribute : BASE {
			private:
				typedef BASE Base;
#undef BASE
			public:
				PTY_FORWARD_OPERATOR_BASE(Base)
				constexpr Attribute() : value() {}
				constexpr explicit Attribute(const T& t) : value(t) {}
				template<class Q, class O, template<class>class...P>
					constexpr explicit Attribute(const Attribute<Q, O, P...>& t) : value(static_cast<T>(t.value)) {}
				constexpr explicit Attribute(T&& t) : value(std::move(t)) {}

				friend pty::adaptor<Attribute>;
				friend pty::adaptor<const Attribute>;
				friend Owner;

				inline constexpr Attribute& operator=(const Attribute& a) {Base::operator=(a.value); return *this; }
				inline constexpr Attribute& operator=(const T& a) {Base::operator=(a); return *this; }

				constexpr inline operator T() const {
					return value;
				}

			private:

				constexpr T& operator_base(pty::operators::cast) {
					return value;
				}

				constexpr const T& operator_base(pty::operators::cast) const {
					return value;
				}

			private:
				T value;
		};
}

#endif// GUARD_PTY_ATTRIBUTE_HPP__
