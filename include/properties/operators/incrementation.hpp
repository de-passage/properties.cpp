#ifndef GUARD_PTY_OPERATORS_INCREMENTATION_HPP__
#define GUARD_PTY_OPERATORS_INCREMENTATION_HPP__

#include "properties/meta/tuple.hpp"
#include "properties/details/incrementation_operation_macro.hpp"


#define PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION(op, sym)\
		struct sym {\
			template<class T>\
			inline constexpr T operator()(T& obj) const {\
				return obj op; \
			}	\
			static constexpr const char* const name = "operator_"#sym "(" #op ")"; \
		}; \

#define PTY_DETAILS_DEFINE_PREINCREMENT_OPERATION(op, sym)\
		struct sym {\
			template<class T>\
			inline constexpr T& operator()(T& obj) const {\
				return op obj; \
			}	\
			static constexpr const char* const name = "operator_"#sym "(" #op ")"; \
		}; \

namespace pty {
	namespace operators {
		PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_PREINCREMENT_OPERATION, prefix_)
		PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION, suffix_)

		typedef pty::meta::tuple<pty::operators::prefix_increment, pty::operators::prefix_decrement> prefix_shift;
		typedef pty::meta::tuple<pty::operators::suffix_increment, pty::operators::suffix_decrement> suffix_shift;
        typedef pty::meta::tuple< pty::operators::prefix_increment, pty::operators::suffix_increment, pty::operators::prefix_decrement, pty::operators::suffix_decrement > shift;
	}
}

#endif// GUARD_PTY_OPERATORS_INCREMENTATION_HPP__
