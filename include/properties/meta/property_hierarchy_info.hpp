#ifndef GUARD_PTY_META_GET_BASE_HPP__
#define GUARD_PTY_META_GET_BASE_HPP__

#include "properties/details/properties.hpp"
#include "properties/meta/tuple.hpp"

namespace pty {
  namespace meta {
    namespace details {
      template<class T>
        struct get_base_t {
			// Required to side-step anticipated instanciation of functions during the property building process.
			// Dummy property<T> classes are created so removing this line will generate an error if it is used in a function return type deduction
			typedef T value;
		};
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

// Retrieve the base type to which properties are applied
    template<class T>
      using get_base = typename details::get_base_t<T>::value;

// Retrieve the property list of a Property class
    template<class T>
      using get_properties = typename details::get_properties_t<T>::value;
  }
}

#endif // GUARD_PTY_META_GET_BASE_HPP__
