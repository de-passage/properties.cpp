#ifndef GUARD_PTY_PROPERTIES_HPP__
#define GUARD_PTY_PROPERTIES_HPP__

//#include "properties/details/properties.hpp"
#include "properties/adaptor.hpp"
#include <utility>

namespace pty {

    template<class T, template<class> class ...Args>
        struct Properties;
	template<class T, template<class> class Attribute, template<class>class...Args>
		struct Properties<T, Attribute, Args...> : Attribute<Properties<T, Args...>>{
			using Attribute<Properties<T, Args...>>::operator=;
        };
	template<class T>
		struct Properties<T> { };

#define PTY_FORWARD_OPERATOR_BASE(Base) \
	template<class _pty_Op, class ..._pty_Args>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class _pty_Op, class ..._pty_Args>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\

}

#endif
