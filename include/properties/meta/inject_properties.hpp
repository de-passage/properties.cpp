#ifndef GUARD_PTY_META_INJECT_PROPERTIES_HPP__
#define GUARD_PTY_META_INJECT_PROPERTIES_HPP__

#include "properties.hpp"

namespace pty {
  namespace meta {
    namespace details {

      template<class T, template<class>class... P>
        struct inject_property_t;
      template<class T, template<class>class...Args, template<class>class... P>
        struct inject_property_t<pty::Properties<T, Args...>, P...> {
          typedef pty::Properties<T, P..., Args...> value;
        };

    }
    template<class T, template<class>class ...P>
      using inject_properties = typename details::inject_property_t<T, P...>::value;
  }
}

#endif
