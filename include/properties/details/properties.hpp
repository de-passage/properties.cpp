#ifndef GUARD_PTY_DETAILS_PROPERTIES_HPP__
#define GUARD_PTY_DETAILS_PROPERTIES_HPP__

#include "properties/details/self.hpp"

namespace pty {

	namespace details {
		template<class ...Args>
			struct Properties;
		template<class T, template<class> class A, template<class> class ...Args, class P>
			struct Properties<T, A<P>, Args<P>...> : A<Properties<T, Args<P>...> > {
				using  A<Properties<T, Args<P>...> >::operator=;
			};
		template<class T>
			struct Properties<T> : Self<T> {
				struct you_need_to_properly_define_operator_base {};
				template<class ...Args>
					constexpr inline you_need_to_properly_define_operator_base operator_base(Args...) { return {}; }
				template<class ...Args>
					constexpr inline you_need_to_properly_define_operator_base operator_base(Args...) const {return {};};
			};
	}

}

#endif
