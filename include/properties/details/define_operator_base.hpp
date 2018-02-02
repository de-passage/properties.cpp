#ifndef GUARD_PTY_DETAILS_DEFINE_OPERATOR_BASE_HPP__
#define GUARD_PTY_DETAILS_DEFINE_OPERATOR_BASE_HPP__

#include "properties/operators/cast.hpp"
#include "properties/meta/enable_for.hpp"
#include "properties/meta/property_hierarchy_info.hpp"
#include "properties/apply.hpp"

#define PTY_DETAILS_DEFINE_OPERATOR_BASE(oper) \
	template<class Op, class ...Args, class = pty::meta::enable_for<Op, pty::operators:: oper>> \
		inline constexpr decltype(auto) operator_base(const Op& op, const Args&... args) const { \
			return downcast(this).operator_base(pty::apply<Op, const Args&...>{op, {args...}}); \
		} \
	template<class Op, class ...Args, class = pty::meta::enable_for<Op, pty::operators:: oper>> \
		inline constexpr decltype(auto) operator_base(const Op& op, const Args&... args) { \
			return downcast(this).operator_base(pty::apply<Op, const Args&...>{op, {args...}}); \
		} \
	template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::oper>>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class _pty_Op, class ..._pty_Args, class = pty::meta::disable_for<_pty_Op, pty::operators::oper>>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class Op, class ...Args, class = pty::meta::enable_for<Op, pty::operators::oper>> \
		inline constexpr decltype(auto) operator_base(const pty::apply<Op, Args...>& op) const { \
			auto tmp = op(downcast(this).operator_base(pty::operators::cast())); \
			return pty::meta::get_base<decltype(*this)>(tmp); \
		} \
	template<class Op, class ...Args, class = pty::meta::enable_for<Op, pty::operators::oper>> \
		inline constexpr auto& operator_base(const pty::apply<Op, Args...>& op) { \
			op(downcast(this).operator_base(pty::operators::cast())); \
			return *downcast(this).self; \
		} \
	using Base::operator=;

#endif
