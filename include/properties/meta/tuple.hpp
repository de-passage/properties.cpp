#ifndef GUARD_PTY_META_TUPLE_HPP__
#define GUARD_PTY_META_TUPLE_HPP__

namespace pty {
	namespace meta {
		template<class ...N>
			struct tuple {};
		template<template<class>class ...N>
			struct template_tuple {};
	}
}

#endif
