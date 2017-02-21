#ifndef GUARD_PTY_DETAILS_PREVENT_DUPLICATION_HPP__
#define GUARD_PTY_DETAILS_PREVENT_DUPLICATION_HPP__

#include <type_traits>

namespace pty {
	namespace details {
		template<class T, class U, template<class> class Pty>
			using prevent_duplication = std::enable_if_t<!std::is_base_of<Pty<U>, T>::value, void>;
	}
}

#endif
