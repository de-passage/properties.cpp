#ifndef GUARD_PTY_ATTRIBUTE_HPP__
#define GUARD_PTY_ATTRIBUTE_HPP__

#include <type_traits>
#include <utility>

#include "properties.hpp"

#include "properties/permissions.hpp"
#include "properties/streamable.hpp"
#include "properties/numeric.hpp"
#include "properties/conditional_properties.hpp"


namespace pty {

	template<class T, class Owner, template<class>class ...Args>
#define BASE \
	pty::Properties< Attribute<T, Owner, Args...>,\
		Args...,\
		ConditionalProperties<std::is_arithmetic<T>::value, Numeric, Streamable>::template value >
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
				constexpr Attribute(Attribute&& t) : value(std::move(t.value)) {}
				constexpr Attribute(const Attribute& t) : value(t.value) {}

				friend pty::adaptor<Attribute>;
				friend pty::adaptor<const Attribute>;
				friend Owner;

				using Base::operator=;

				inline Attribute& operator=(const Attribute& attr) {
					operator_base(pty::operators::assign(), attr);
					return *this;
				}

				inline Attribute& operator=(Attribute&& attr) {
					operator_base(pty::operators::assign(), std::move(attr.value));
					return  *this;
				}

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
