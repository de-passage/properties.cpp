#ifndef GUARD_PTY_DOWNCAST_HPP__
#define GUARD_PTY_DOWNCAST_HPP__

#include "properties.hpp"
#include "../adaptor.hpp"

namespace pty {
  namespace details {

    template<class T, class ...Args>
      T only_properties_and_types_inherinting_from_properties_can_be_downcast(const pty::Properties<T>&);
    template<class T, class Args>
      T only_properties_and_types_inherinting_from_properties_can_be_downcast(pty::Properties<T>&);

    template<class T>
      struct _down {
        typedef decltype(only_properties_and_types_inherinting_from_properties_can_be_downcast(std::declval<T>())) value;
      };
    template<class T>
      struct _down<const T> {
        typedef const decltype(only_properties_and_types_inherinting_from_properties_can_be_downcast(std::declval<T>())) value;
      };
    template<class T, template<class> class A, template<class>class ...Args>
      struct _down<A<pty::Properties<T, Args...>>> {
        typedef T value;
      };
    template<class T, template<class> class A, template<class>class ...Args>
      struct _down<const A<pty::Properties<T, Args...>>> {
        typedef const T value;
      };

  }


  template<class P>
    constexpr auto downcast(P* that) {
      return adaptor<typename details::_down<P>::value>(static_cast<typename details::_down<P>::value*>(that));
    }

}
#endif// GUARD_PTY_DOWNCAST_HPP__
