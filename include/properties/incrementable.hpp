#ifndef GUARD_PTY_INCREMENTABLE_HPP__
#define GUARD_PTY_INCREMENTABLE_HPP__

#include "properties/details/define_property.hpp"
#include "properties/details/operation_macros.hpp"
#include "properties/meta/tuple.hpp"

namespace pty {

#define PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(op, pref) \
	op(++, pref## increment) \
	op(--, pref## decrement)


#define PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION(op, name)\
	namespace details { \
		template<class T>\
			struct name {\
				inline constexpr T operator()(T& obj) const {\
					return obj op; \
				}	\
			}; \
	}\
	using name = pty::details::unary_operator<details:: name>;\


#define PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR(op, name) \
			inline constexpr auto operator op (int) { \
				return downcast(this).operator_base(pty:: name ()); \
			}



	PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATION, prefix_)
	PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATION, suffix_)

	PTY_DETAILS_DEFINE_PROPERTY(Incrementable,
			PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_UNARY_MUTABLE_OPERATOR, prefix_)
			PTY_DETAILS_APPLY_TO_INCREMENT_OPERATORS(PTY_DETAILS_DEFINE_POSTINCREMENT_OPERATOR, suffix_)

			)

	typedef pty::tuple< pty::prefix_increment, pty::suffix_increment, pty::prefix_decrement, pty::suffix_decrement > increment_operations;

}

#endif

