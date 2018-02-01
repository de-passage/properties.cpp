#ifndef GUARD_PTY_DETAILS_PREVENT_DUPLICATION_HPP__
#define GUARD_PTY_DETAILS_PREVENT_DUPLICATION_HPP__

#include <type_traits>

#include "properties/meta/has_property.hpp"

namespace pty {
	namespace details {
		template<class T, class U, template<class> class Pty>
			using prevent_duplication = std::enable_if_t<!::pty::meta::has_property<T, Pty>, void>;
	}
}

#endif
