#ifndef GUARD_PTY_CONDITIONAL_PROPERTIES_HPP__
#define GUARD_PTY_CONDITIONAL_PROPERTIES_HPP__

#include "properties/meta/inject_properties.hpp"

namespace pty {

		template<bool B, template<class> class ...T>
			struct ConditionalProperties {
				template<class R>
					struct value : R {
						using R::operator=;
					};
			};
		template<template<class>class ...T>
			struct ConditionalProperties<true, T...> {
				template<class R>
					struct value : meta::inject_properties<R, T...> {
						typedef meta::inject_properties<R, T...> Base;
						using Base::operator=;
					};
			};
}

#endif //GUARD_PTY_CONDITIONAL_PROPERTIES_HPP__
