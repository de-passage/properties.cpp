#ifndef GUARD_PTY_DETAILS_DEFINE_PROPERTY_HPP__
#define GUARD_PTY_DETAILS_DEFINE_PROPERTY_HPP__

#include <utility>

#define PTY_FORWARD_OPERATOR_BASE(Base) \
	template<class _pty_Op, class ..._pty_Args>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	template<class _pty_Op, class ..._pty_Args>\
	constexpr inline decltype(auto) operator_base(const _pty_Op& op, _pty_Args&&... args) const { \
		return Base::operator_base(op, std::forward<_pty_Args>(args)...);\
	}\
	using Base::operator=;

#define PTY_DETAILS_DEFINE_PROPERTY(name, in_processing) \
	template<class Base> struct name : Base { \
		protected: \
			using Base::self; \
			inline ~name() = default; \
		public: \
			in_processing\
	};

#endif
