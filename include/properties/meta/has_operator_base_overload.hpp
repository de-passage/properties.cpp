#ifndef GUARD_PTY_META_HAS_OPERATOR_BASE_OVERLOAD_HPP__
#define GUARD_PTY_META_HAS_OPERATOR_BASE_OVERLOAD_HPP__

//#include "properties/helpers/downcast.hpp"
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
			static constexpr bool check_operator_base_public_interface = details::has_operator_base_overload_t<Class, Args...>::value;

		template<class Class, class ...Args>
			static constexpr bool has_operator_base_overload = details::has_operator_base_overload_t<Class, Args...>::value;
		
		template<class Class, class ...Args>
			static constexpr bool has_non_const_operator_base_overload = decltype(std::declval<Class>().template check_overload<Args...>())::value; // <- this is what I want but fails to compile because incorrectly detects non const functions

	}
}

#define PTY_DEFINE_CHECK_OVERLOAD \
	private: \
	template<class ...Args> \
	constexpr auto _pty_impl__check_overload(Args&&... args) -> decltype(operator_base(std::forward<Args>(args)...), std::true_type()) { \
		return std::true_type(); \
	} \
 \
	constexpr std::false_type _pty_impl__check_overload(...) { \
		return std::false_type(); \
	} \
	public: \
 \
	template<class ...Args> \
	constexpr auto check_overload() { \
		return decltype(_pty_impl__check_overload(std::declval<Args>()...))(); \
	} \
 \
	template<class ...Args> \
	constexpr auto check_overload() const { \
		return decltype(_pty_impl__check_overload(std::declval<Args>()...))(); \
	} \

#endif // GUARD_PTY_META_HAS_OPERATOR_BASE_OVERLOAD_HPP__

