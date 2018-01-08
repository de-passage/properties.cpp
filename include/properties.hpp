#ifndef GUARD_PTY_PROPERTIES_HPP__
#define GUARD_PTY_PROPERTIES_HPP__

#include "properties/details/properties.hpp"
#include "properties/adaptor.hpp"

namespace pty {

    template<class T, template<class> class ...Args>
        struct Properties : details::Properties<T, Args<T>...> {
        };

    template<class T>
        using Adaptor = details::Self<T>;
}

#endif
