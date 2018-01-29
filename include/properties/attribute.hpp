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
			struct apply_tuple<pty::tuple<Args...>> {
				template<class T>
					struct value : pty::details::Properties<pty::meta::get_base<T>, Args...> {
						using pty::details::Properties<pty::meta::get_base<T>, Args...>::operator=;
					};
			};

		template<>
			struct apply_tuple<pty::tuple<>> {
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

	template<class T, class Owner, template<class>class ...Args>
		struct Attribute :
			Properties<
				Attribute<T, Owner, Args...>,
				Args...,
				details::AttributeAdaptor<std::is_arithmetic<T>::value, Streamable>::template value,
				details::AttributeAdaptor<std::is_arithmetic<T>::value, Numeric>::template value,
				ReadOnly> {
					private:
						typedef Properties< Attribute<T, Owner, Args...>, Args..., details::AttributeAdaptor<std::is_arithmetic<T>::value, Streamable>::template value, details::AttributeAdaptor<std::is_arithmetic<T>::value, Numeric>::template value, ReadOnly> Base;
					public:
						constexpr Attribute() : value() {}
						constexpr explicit Attribute(const T& t) : value(t) {}
						template<class Q, class O, template<class>class...P>
							constexpr explicit Attribute(const Attribute<Q, O, P...>& t) : value(static_cast<T>(t.value)) {}
						constexpr explicit Attribute(T&& t) : value(std::move(t)) {}

						friend pty::adaptor<Attribute>;
						friend pty::adaptor<const Attribute>;
						friend Owner;
						using Base::operator=;

						constexpr inline operator T() const {
							return value;
						}

					private:


						template<class Op, class Q>
							constexpr auto operator_base(const Op& op, const Q& t) const {
								return Base::operator_base(op, t);
							}
						template<class Op, class Q>
							constexpr auto operator_base(const Op& op, const Q& t) {
								return Base::operator_base(op, t);
							}

						template<class Op>
							constexpr auto operator_base(const Op& op){
								return op(value);
							}

						template<class Op>
							constexpr auto operator_base(const Op& op) const {
								return op(value);
							}


						template<class Op, class In, class = pty::enable_for<Op, pty::comparison_operation>, class U = T, class = std::enable_if_t<std::is_arithmetic<U>::value>>
							constexpr bool operator_base(const pty::apply_left<Op, bool, In>& op) const {
								return op(value);
							}

						template<class Op, class In, class = pty::enable_for<Op, pty::constant_bitwise_operations, pty::constant_arithmetic_operations>, class U = T, class = std::enable_if_t<std::is_arithmetic<U>::value>>
							constexpr Attribute operator_base(const pty::apply_left<Op, Attribute, In>& op) const {
								return Attribute(Op()(value, op.value()));
							}

						template<class Op, class In, class = pty::enable_for<Op, pty::bitwise_operations, pty::arithmetic_operations, pty::assign>, class U = T, class = std::enable_if_t<std::is_arithmetic<U>::value>>
							constexpr Attribute& operator_base(const pty::apply_left<Op, Attribute, In>& op) {
								Op()(value, op.value());
								return *this;
							}

						template<class Ret, class In>
							constexpr Ret operator_base(const pty::apply_left<pty::assign, Ret, In>& op) {
								return this->value = op.value();
							}


						template<class S>
							constexpr S& operator_base(const pty::operators::stream_out& op, S& stream) const {
								return op(stream, value);
							}
						template<class S>
							constexpr S& operator_base(const pty::operators::stream_in& op, S& stream) {
								return op(stream, value);
							}

						constexpr int operator_base(const pty::operators::cast&) const {
							return value;
						}

			private:
				T value;
		};
}

#endif// GUARD_PTY_ATTRIBUTE_HPP__
