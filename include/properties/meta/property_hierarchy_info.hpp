#ifndef GUARD_PTY_META_GET_BASE_HPP__
#define GUARD_PTY_META_GET_BASE_HPP__

#include "properties/details/properties.hpp"
#include "properties/meta/tuple.hpp"

namespace pty {
  namespace meta {
    namespace details {
      template<class T>
        struct get_base_t;
      template<class T, class ...Args>
        struct get_base_t<pty::details::Properties<T, Args...>> {
          typedef T value;
        };
      template<template<class> class Prop, class T, class ...Args>
        struct get_base_t<const Prop<pty::details::Properties<T, Args...>>&> {
          typedef T value;
        };
      template<template<class> class Prop, class T, class ...Args>
        struct get_base_t<Prop<pty::details::Properties<T, Args...>>> {
          typedef T value;
        };

      template<class T>
        struct get_properties_t;
      template<class T, class ...Args>
        struct get_properties_t<pty::details::Properties<T, Args...>> {
          typedef pty::meta::tuple<Args...> value;
        };
      template<template<class> class Prop, class T, class ...Args>
        struct get_properties_t<Prop<pty::details::Properties<T, Args...>>> {
          typedef pty::meta::tuple<Args...> value;
        };
      template<template<class> class Prop, class T, class ...Args>
        struct get_properties_t<const Prop<pty::details::Properties<T, Args...>>&> {
          typedef pty::meta::tuple<Args...> value;
        };
    }

// Retrieve the base type to which properties are applied
    template<class T>
      using get_base = typename details::get_base_t<T>::value;

// Retrieve the property list of a Property class
    template<class T>
      using get_properties = typename details::get_properties_t<T>::value;
  }
}

#endif // GUARD_PTY_META_GET_BASE_HPP__
