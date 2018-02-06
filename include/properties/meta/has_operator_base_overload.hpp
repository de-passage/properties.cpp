#ifndef GUARD_PTY_META_HAS_OPERATOR_BASE_OVERLOAD_HPP__
#define GUARD_PTY_META_HAS_OPERATOR_BASE_OVERLOAD_HPP__

#include <type_traits>

namespace pty {
	namespace meta {
		namespace details {
			template <typename T, typename... Args>
				class has_operator_base_overload_t
				{
					template <typename C,
							 typename = decltype( std::declval<C>().operator_base(std::declval<Args>()...) )>
								 static std::true_type test(int);
					template <typename C>
						static std::false_type test(...);

					public:
					static constexpr bool value = decltype(test<T>(0))::value;
				};
		}

		template<class Class, class ...Args>
			static constexpr bool has_operator_base_overload = details::has_operator_base_overload_t<Class, Args...>::value;

	}
}
#endif // GUARD_PTY_META_HAS_OPERATOR_BASE_OVERLOAD_HPP__

