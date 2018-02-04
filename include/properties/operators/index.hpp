#ifndef GUARD_PTY_OPERATORS_INDEX
#define GUARD_PTY_OPERATORS_INDEX

#include <stddef.h>
#include <utility>
#include "properties/meta/tuple.hpp"

namespace pty {
	namespace operators {

		struct index {
			template<class T, class I>
			constexpr inline decltype(auto) operator()(T&& obj, I&& index) const {
				return obj[std::forward<I>(index)];
			}
		};

		struct dereference {
			template<class T>
				constexpr inline decltype(auto) operator()(T&& obj) const {
					return *obj;
				}
		};

		struct dereference_member {
			template<class T>
				constexpr inline decltype(auto) operator()(T* obj) const {
					return obj;
				}
		};

		typedef pty::meta::tuple<index, dereference, dereference_member> address;

		

	}
}
#endif // GUARD_PTY_OPERATORS_INDEX
