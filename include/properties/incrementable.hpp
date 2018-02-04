#ifndef GUARD_PTY_INCREMENTABLE_HPP__
#define GUARD_PTY_INCREMENTABLE_HPP__

#include "properties/details/define_property.hpp"
#include "properties/details/define_operator_base.hpp"
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

#define PTY_DETAILS_DEFINE_PREINCREMENT_OPERATION(op, name)\
		struct name {\
			template<class T>\
			inline constexpr T& operator()(T& obj) const {\
				return op obj; \
			}	\
		}; \

#define PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR(op, name) \
			inline constexpr decltype(auto)operator op (int) { \
				return downcast(this).operator_base(pty::operators:: name ()); \
			}

#define PTY_DETAILS_DEFINE_PREINCREMENT_OPERATOR(op, name) \
			inline constexpr decltype(auto) operator op() { \
				return downcast(this).operator_base(pty::operators:: name ()); \
			}
#define PTY_DETAILS_DEFINE_INNER_PROPS() \
		template<class Op, class = pty::meta::enable_for<Op, pty::operators::suffix_shift>> \
			constexpr inline pty::meta::get_base<Base> operator_base(const Op& op) { \
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast()))); \
			}\
		template<class Op, class = pty::meta::enable_for<Op, pty::operators::prefix_shift>> \
			constexpr inline pty::meta::get_base<Base>& operator_base(const Op& op) { \
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast()))); \
			}

	namespace operators {
		PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_PREINCREMENT_OPERATION, prefix_)
		PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION, suffix_)

		typedef pty::meta::tuple<pty::operators::prefix_increment, pty::operators::prefix_decrement> prefix_shift;
		typedef pty::meta::tuple<pty::operators::suffix_increment, pty::operators::suffix_decrement> suffix_shift;
        typedef pty::meta::tuple< pty::operators::prefix_increment, pty::operators::suffix_increment, pty::operators::prefix_decrement, pty::operators::suffix_decrement > shift;
	}

	template<class Base>
		struct Incrementable : Base {

            //PTY_FORWARD_OPERATOR_BASE(Base)
			using Base::operator=;
			PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_PREINCREMENT_OPERATOR, prefix_)
			PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR, suffix_)
            /*
            PTY_DETAILS_DEFINE_OPERATOR_BASE(shift)
            */
			PTY_DETAILS_DEFINE_INNER_PROPS()
			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::shift>>
			constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { 
				return Base::operator_base(op, std::forward<_pty_Args>(args)...);
			}
			template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::shift>>
			constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { 
				return Base::operator_base(op, std::forward<_pty_Args>(args)...);
			}
			constexpr inline pty::meta::get_base<Base> operator_base(pty::operators::suffix_decrement op) {
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast())));
			}
			constexpr inline pty::meta::get_base<Base> operator_base(pty::operators::suffix_increment op) {
				return pty::meta::get_base<Base>(op(downcast(this).operator_base(pty::operators::cast())));
			}
			constexpr inline pty::meta::get_base<Base>& operator_base(pty::operators::prefix_increment op) {
				op(downcast(this).operator_base(pty::operators::cast()));
				return *downcast(this).self;
			}
			constexpr inline pty::meta::get_base<Base>& operator_base(pty::operators::prefix_decrement op) {
				op(downcast(this).operator_base(pty::operators::cast()));
				return *downcast(this).self;
			}

		};


}

#undef PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS
#undef PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION
#undef PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR
#undef PTY_DETAILS_DEFINE_INNER_PROPS


#endif

