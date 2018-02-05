#ifndef GUARD_PTY_DETAILS_DEFINE_OPERATOR_BASE_HPP__
#define GUARD_PTY_DETAILS_DEFINE_OPERATOR_BASE_HPP__

#include "properties/operators/cast.hpp"
#include "properties/meta/enable_for.hpp"
#include "properties/meta/property_hierarchy_info.hpp"
//#include "properties/apply.hpp"

#define PTY_DETAILS_DEFINE_OPERATOR_BASE(oper) \
	template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::oper>>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::oper>>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class Op, class ...Args, class O = Op, class = pty::meta::enable_for<O, pty::operators::oper>> \
		inline constexpr auto operator_base(const Op& op, Args&&... args) const { \
			auto tmp = op(downcast(this).operator_base(pty::operators::cast()), std::forward<Args>(args)...); \
			return decltype(*downcast(this).self)(tmp); \
		} \
	template<class Op, class ...Args, class O = Op, class = pty::meta::enable_for<O, pty::operators::oper>> \
		inline constexpr auto& operator_base(const Op& op, Args&&... args) { \
			op(downcast(this).operator_base(pty::operators::cast()), std::forward<Args>(args)...); \
			return *downcast(this).self; \
		} \
	using Base::operator=;

#endif
