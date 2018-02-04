#ifndef GUARD_PTY_NUMERIC_HPP__
#define GUARD_PTY_NUMERIC_HPP__

#include "properties/arithmetic.hpp"
#include "properties/assignable.hpp"
#include "properties/bitwise.hpp"
#include "properties/comparable.hpp"
#include "properties/incrementable.hpp"
#include "properties/meta/inject_properties.hpp"

namespace pty {
	template<class Base>
		struct Numeric : meta::inject_properties<Base, Arithmetic, Comparable, Bitwise, Incrementable, Assignable> {
			using meta::inject_properties<Base, Arithmetic, Comparable, Bitwise, Incrementable, Assignable>::operator=;
		};
}
#endif
