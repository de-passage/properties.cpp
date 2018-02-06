#ifndef GUARD_PTY_DETAILS_DEDUCE_ITERATOR_TAG_HPP__
#define GUARD_PTY_DETAILS_DEDUCE_ITERATOR_TAG_HPP__

#include "properties/helpers/downcast.hpp"

#include <type_traits>

namespace pty {
	namespace details {

		template<class Class, class ...Arguments>
			struct has_operator_base_overload_t {
				template<class Source, class...Args>
					static constexpr auto _can_operator_base_be_called_with(Source* s) -> decltype(pty::downcast(s).operator_base(std::declval<Args>()...), std::true_type());
				template<class,class...>
					static constexpr std::false_type _can_operator_base_be_called_with(...);

				typedef decltype(_can_operator_base_be_called_with<Class, Arguments...>(0)) value;
			};

	}

	template<class Class, class ...Args>
		static constexpr bool has_operator_base_overload = details::has_operator_base_overload_t<Class, Args...>::value;

	namespace details {
		template<class Class>
			struct deduce_iterator_tag_t {
				typedef void value;
			};

		template<class C>
			using deduce_iterator_tag = typename deduce_iterator_tag_t<C>::value;
	}
}


#endif // GUARD_PTY_DETAILS_DEDUCE_ITERATOR_TAG_HPP__

