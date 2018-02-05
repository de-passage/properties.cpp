#ifndef GUARD_PTY_ASSIGNABLE_HPP__
#define GUARD_PTY_ASSIGNABLE_HPP__

#include "properties/meta/property_hierarchy_info.hpp"
#include "properties/operators/assign.hpp"
#include "properties/details/define_operator_base.hpp"
#include "properties/helpers/downcast.hpp"

#include <type_traits>

#define INNER_PROPS\

namespace pty {
	template<class Base>
		struct Assignable : Base {

			PTY_DETAILS_DEFINE_OPERATOR_BASE(assign)

			template<class Q, class = std::enable_if_t<!std::is_same<std::remove_reference_t<Q>, pty::meta::get_base<Base>>::value>>
				inline decltype(auto) operator=(const Q& t) {
					downcast(this).operator_base(pty::operators::assign(), t);
					return *downcast(this).self;
				}

			template<class Q, class = std::enable_if_t<!std::is_same<std::remove_reference_t<Q>, pty::meta::get_base<Base>>::value>>
				inline decltype(auto) operator=(Q&& t) {
					downcast(this).operator_base(pty::operators::assign(), std::forward<Q>(t));
					return *downcast(this).self;
				}

			template<class P, class Q = P, class = std::enable_if_t<std::is_same<std::remove_reference_t<Q>, pty::meta::get_base<Base>>::value>>
				inline decltype(auto) operator=(const Q& t) {
					downcast(this).operator_base(pty::operators::assign(), downcast(t).operator_base(pty::operators::cast()));
					return *downcast(this).self;
				}

			template<class P, class Q = P, class = std::enable_if_t<std::is_same<std::remove_reference_t<Q>, pty::meta::get_base<Base>>::value>>
				inline decltype(auto) operator=(Q&& t) {
					downcast(this).operator_base(pty::operators::assign(), std::move(downcast(t).operator_base(pty::operators::cast())));
					return *downcast(this).self;
				}

		};
#undef INNER_PROPS
}

#define PTY_DEFINE_ASSIGNMENT_OPERATOR(Class) \
	Class& operator=(const Class& t) { \
		operator_base(pty::operators::assign(),t.value); \
		return *this; \
	} \
\
	Class& operator=(Class&& t) {\
		operator_base(pty::operators::assign(),t.value);\
		return *this;\
	}
#endif // GUARD_PTY_ASSIGNABLE_HPP__
