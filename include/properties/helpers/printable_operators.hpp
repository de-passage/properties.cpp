#ifndef GUARD_PTY_HELPERS_PRINTABLE_OPERATORS
#define GUARD_PTY_HELPERS_PRINTABLE_OPERATORS

#include "properties/operators.hpp"
#include "properties/meta/enable_for.hpp"

#include <iostream>

template<class T, class = pty::meta::enable_for<T, pty::operators::all>>
std::ostream& operator<<(std::ostream& out, const T&) {
	return out << T::name;
}

#endif 
