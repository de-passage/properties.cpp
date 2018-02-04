#ifndef GUARD_PTY_OPERATORS_ASSIGN_HPP__
#define GUARD_PTY_OPERATORS_ASSIGN_HPP__

#include "properties/details/define_operation.hpp"

#include <utility>

namespace pty {
	namespace operators {
		struct assign {
			template<class T, class Q>
				constexpr inline decltype(auto) operator()(T&& receiver, const Q& model) const {
					return receiver = model;
				}
			template<class T, class Q>
				constexpr inline decltype(auto) operator()(T&& receiver, Q&& model) const {
					return receiver = std::forward<Q>(model);
				}
		};
	}
}

#endif
