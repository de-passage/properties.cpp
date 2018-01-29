#ifndef GUARD_PTY_ASSIGNABLE_HPP__
#define GUARD_PTY_ASSIGNABLE_HPP__

#include "properties/details/define_property.hpp"
#include "properties/details/define_operation.hpp"

namespace pty {
	PTY_DETAILS_DEFINE_BINARY_MUTABLE_OPERATION(=, assign)	

	PTY_DETAILS_DEFINE_PROPERTY(Assignable, 
		template<class Q>
		auto operator=(const Q& t) {
			return downcast(this).operator_base(pty::assign(), t);
		}
	)
}
#endif // GUARD_PTY_ASSIGNABLE_HPP__
