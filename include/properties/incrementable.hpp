#ifndef GUARD_PTY_INCREMENTABLE_HPP__
#define GUARD_PTY_INCREMENTABLE_HPP__

#include "properties/details/define_property.hpp"
#include "properties/details/operation_macros.hpp"
#include "properties/meta/tuple.hpp"
#include "properties/meta/property_hierarchy_info.hpp"
#include "properties/meta/enable_for.hpp"
#include "properties/operators/cast.hpp"

namespace pty {

#define PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(op, pref) \
	op(++, pref## increment) \
	op(--, pref## decrement)


#define PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION(op, name)\
		struct name {\
			template<class T>\
			inline constexpr T operator()(T& obj) const {\
				return obj op; \
			}	\
		}; \


#define PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR(op, name) \
			inline constexpr auto operator op (int) { \
				return downcast(this).operator_base(pty:: name ()); \
			}

#define PTY_DETAILS_DEFINE_INNER_PROPS() \
		template<class Op, class = pty::enable_for<Op, pty::suffix_increment>> \
			constexpr inline pty::meta::get_base<Base> operator_base(const Op& op) { \
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast()))); \
			}\
		template<class Op, class = pty::enable_for<Op, pty::prefix_increment>> \
			constexpr inline pty::meta::get_base<Base>& operator_base(const Op& op) { \
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast()))); \
			}

	PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATION, prefix_)
	PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION, suffix_)

	typedef pty::tuple<pty::prefix_increment, pty::prefix_decrement> prefix_increment_operations;
	typedef pty::tuple<pty::suffix_increment, pty::suffix_decrement> suffix_increment_operations;

	PTY_DETAILS_DEFINE_PROPERTY(Incrementable,
			PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATOR, prefix_)
			PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR, suffix_)
			PTY_DETAILS_DEFINE_INNER_PROPS()
			constexpr inline pty::meta::get_base<Base> operator_base(const pty::suffix_decrement& op) {
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast())));
			}
			constexpr inline pty::meta::get_base<Base> operator_base(const pty::suffix_increment& op) {
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast())));
			}
			constexpr inline pty::meta::get_base<Base>& operator_base(const pty::prefix_increment& op) {
				op(downcast(this).operator_base(pty::operators::cast()));
				return *downcast(this).self;
			}
			constexpr inline pty::meta::get_base<Base>& operator_base(const pty::prefix_decrement& op) {
				op(downcast(this).operator_base(pty::operators::cast()));
				return *downcast(this).self;
			}

			)

	typedef pty::tuple< pty::prefix_increment, pty::suffix_increment, pty::prefix_decrement, pty::suffix_decrement > increment_operations;

}

#undef PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS
#undef PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION
#undef PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR


#endif

