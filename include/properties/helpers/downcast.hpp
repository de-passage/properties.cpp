#ifndef GUARD_PTY_DOWNCAST_HPP__
#define GUARD_PTY_DOWNCAST_HPP__

#include "properties/details/properties.hpp"
#include "../adaptor.hpp"

namespace pty {
  namespace details {

    template<class T>
      struct _down;
    template<class T, template<class> class A, template<class>class ...Args>
      struct _down<A<pty::details::Properties<T, Args<T>...>>> {
        typedef T value;
      };
    template<class T, template<class> class A, template<class>class ...Args>
      struct _down<const A<pty::details::Properties<T, Args<T>...>>> {
        typedef const T value;
      };

  }


  template<class P>
    auto downcast(P* that) {
      return adaptor<typename details::_down<P>::value>(static_cast<typename details::_down<P>::value*>(that));
    }
}
#endif// GUARD_PTY_DOWNCAST_HPP__
