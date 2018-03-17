#ifndef GUARD_PTY_META_TUPLE_OPERATIONS_HPP__
#define GUARD_PTY_META_TUPLE_OPERATIONS_HPP__

#include "properties/meta/tuple.hpp"

namespace pty {
	namespace meta {

		/*
		 * Add the given class-value to the begining of the tuple
		 */
		template<class A, class Tuple>
		struct prepend_t;

		template<class A, class ...Args>
			struct prepend_t<A, tuple<Args...>> {
				typedef tuple<A, Args...> value;
			};

		template<class A, class T>
			using prepend = typename prepend_t<A, T>::value;

		/*
		 * Concatenate two tuples into one
		 */
		template<class T1, class T2>
			struct concat_t;

		template<class ...Args1, class...Args2>
			struct concat_t<tuple<Args1...>, tuple<Args2...>> {
				typedef tuple<Args1..., Args2...> value;
			};

		template<class T1, class T2>
			using concat = typename concat_t<T1, T2>::value;


		/*
		 * Remove all instances of a class-value from a tuple
		 */
		template<class A, class Tuple, class Tuple2>
		struct remove_t;

		template<class A, class T>
			using remove = typename remove_t<A, T, tuple<>>::value;

		template<class A, class ...Args, class ...Args2>
			struct remove_t<A, tuple<A, Args...>, tuple<Args2...>> {
				typedef concat<tuple<Args2...>, remove<A, tuple<Args...>>> value;
			};

		template<class A, class ...Args>
			struct remove_t<A, tuple<>, tuple<Args...>> {
				typedef tuple<Args...> value;
			};

		template<class A, class B, class... Args, class ...Args2>
			struct remove_t<A, tuple<B, Args...>, tuple<Args2...>> {
				typedef concat<tuple<Args2..., B>, remove<A, tuple<Args...>>> value;
			};
		
		/* 
		 * Return true if the element is in the tuple, false otherwise
		 */
		template<class A, class Tuple>
			struct contains_t;
		template<class A, class Tuple>
			constexpr static const bool contains = contains_t<A, Tuple>::value;
		template<class A, class ...Args>
			struct contains_t<A, tuple<A, Args...>> {
				constexpr static const bool value = true;
			};
		template<class A, class B, class ...Args>
			struct contains_t<A, tuple<B, Args...>> {
				constexpr static const bool value = contains<A, tuple<Args...>>;
			};
		template<class A>
			struct contains_t<A, tuple<>> {
				constexpr static const bool value = false;
			};

		/*
		 * Flatten recursively all nested meta::tuple 
		 */
				
		template<class ...Args>
			struct flatten_t;

		template<class ...A1, class ...A2>
			struct flatten_t<pty::meta::tuple<A1...>, A2...> {
				typedef typename flatten_t<A1..., A2...>::value value;
			};

		template<class T, class ...A>
			struct flatten_t<T, A...> {
				typedef concat<tuple<T>, typename flatten_t<A...>::value> value;
			};

		template<>
		struct flatten_t<> {
			typedef pty::meta::tuple<> value;
		};

		template<class...Args>
			using flatten = typename flatten_t<Args...>::value;

	}
}

#endif // GUARD_PTY_META_TUPLE_OPERATIONS_HPP__
