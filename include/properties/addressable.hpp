#ifndef GUARD_PTY_ADDRESSABLE_HPP__
#define GUARD_PTY_ADDRESSABLE_HPP__

#include "properties/details/define_property.hpp"
#include "properties/apply.hpp"

#include <stddef.h>

namespace pty {

	namespace operations {

		struct index {
			template<class T>
			constexpr inline auto& operator()(T& obj, size_t index) const {
				return obj[index];
			}
			template<class T>
			constexpr inline auto operator()(const T& obj, size_t index) const {
				return obj[index];
			}
		};

	}

	template<class T>
		struct Addressable : T {
			using T::operator=;

			constexpr inline auto operator[](size_t index) const {
				return downcast(this).operator_base(apply<operations::index, size_t>{{}, {index}});
			}

			constexpr inline auto& operator[](size_t index) {
				return downcast(this).operator_base(apply<operations::index, size_t>{{}, {index}});
			}
		};


}

#endif // GUARD_PTY_ADDRESSABLE_HPP__
