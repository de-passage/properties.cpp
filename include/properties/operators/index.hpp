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
			constexpr static const char* const name = "operator_index([])";
		};

		struct dereference {
			template<class T>
				constexpr inline decltype(auto) operator()(T&& obj) const {
					return *obj;
				}
			constexpr static const char* const name = "operator_dereference(*)";
		};

		struct dereference_member {
			template<class T>
				constexpr inline decltype(auto) operator()(T* obj) const {
					return obj;
				}
			constexpr static const char* const name = "operator_dereference_member(->)";
		};

		typedef pty::meta::tuple<index, dereference, dereference_member> address;

		

	}
}
#endif // GUARD_PTY_OPERATORS_INDEX
