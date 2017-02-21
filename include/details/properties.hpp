#ifndef GUARD_PTY_DETAILS_PROPERTIES_HPP__
#define GUARD_PTY_DETAILS_PROPERTIES_HPP__

#include "details/self.hpp"

namespace pty {

	namespace details {
		template<class ...Args>
			struct Properties;
		template<class T, template<class> class A, template<class> class ...Args, class P>
			struct Properties<T, A<P>, Args<P>...> : A<Properties<T, Args<P>...> > {};
		template<class T>
			struct Properties<T> : Self<T> {};
	}

}

#endif
