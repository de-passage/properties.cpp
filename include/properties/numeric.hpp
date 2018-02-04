#ifndef GUARD_PTY_NUMERIC_HPP__
#define GUARD_PTY_NUMERIC_HPP__

#include "properties/apply.hpp"
#include "properties/arithmetic.hpp"
#include "properties/assignable.hpp"
#include "properties/bitwise.hpp"
#include "properties/comparable.hpp"
#include "properties/incrementable.hpp"
#include "properties/details/properties.hpp"
#include "properties/helpers/downcast.hpp"
#include "properties/meta/enable_for.hpp"
#include "properties/meta/property_hierarchy_info.hpp"
#include "properties/operators/cast.hpp"
#include "properties/permissions.hpp"

#include <type_traits>


namespace pty {
	template<class Base>
		struct Numeric;

	template<class ...Args>
	struct NumericCompatible {
		template<class ...>
		struct CompatibleWith;

		template<class Base>
		struct value : Base {
			typedef meta::remove<permissions::Write, meta::remove<permissions::Read, permissions::get<Base>>> Permissions;
		};

	};

	template<class Base, template<class> class ...Args>
		// Forward properties and add comparable, arithmetic and bitwise to them
		struct Numeric<details::Properties<Base, Args<Base>...>> : details::Properties<Base, Comparable<Base>, Arithmetic<Base>, Bitwise<Base>, Incrementable<Base>, Args<Base>...>{
			protected:
				typedef details::Properties<Base, Comparable<Base>, Arithmetic<Base>, Bitwise<Base>, Incrementable<Base>, Args<Base>...> Parent;
				using Parent::operator=;


		};
}
#endif
