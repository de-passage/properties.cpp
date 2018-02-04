#ifndef GUARD_PTY_ASSIGNABLE_HPP__
#define GUARD_PTY_ASSIGNABLE_HPP__

#include "properties/details/define_property.hpp"
#include "properties/operators/assign.hpp"
#include "properties/details/define_operator_base.hpp"


namespace pty {
	PTY_DETAILS_DEFINE_PROPERTY(Assignable, 
		PTY_DETAILS_DEFINE_OPERATOR_BASE(assign)
		template<class Q>
		decltype(auto) operator=(const Q& t) {
			return downcast(this).operator_base(pty::operators::assign(), t);
		}
	)
}
#endif // GUARD_PTY_ASSIGNABLE_HPP__
