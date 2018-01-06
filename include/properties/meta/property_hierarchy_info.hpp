#ifndef GUARD_PTY_META_GET_BASE_HPP__
#define GUARD_PTY_META_GET_BASE_HPP__

namespace pty {
// Retrieve the base type to which properties are applied
  namespace meta {
    namespace details {
      template<class T>
        struct get_base_t;
      template<class T, class ...Args>
        struct get_base_t<pty::details::Properties<T, Args...>> {
          typedef T value;
        };

      template<class T>
        struct get_properties_t;
      template<class T, class ...Args>
        struct get_properties_t<pty::details::Properties<T, Args...>> {
          typedef pty::tuple<Args...> value;
        };
    }

    template<class T>
      using get_base = typename details::get_base_t<T>::value;
    template<class T>
      using get_properties = typename details::get_properties_t<T>::value;
  }
}

#endif // GUARD_PTY_META_GET_BASE_HPP__
