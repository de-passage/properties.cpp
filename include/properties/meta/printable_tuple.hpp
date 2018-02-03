#ifndef GUARD_PTY_META_PRINTABLE_TUPLE_HPP__
#define GUARD_PTY_META_PRINTABLE_TUPLE_HPP__

#include "properties/meta/tuple.hpp"

#include <type_traits>
#include <ostream>


namespace pty {
	namespace details {
		template<class T>
			struct string_for {
			typedef char yes;
			typedef struct {char d[2];} no;
			template<typename T1>
				static yes test(typename T1::name*);
			template<typename T1>
				static no test(...);

			constexpr static const bool _value = ( sizeof(test<T>(0)) == sizeof(yes) );

			template<class R, bool Cond>
			struct extract_if_possible {
				constexpr static const char* const value = "unknown_type";
			};
			template<class R>
				struct extract_if_possible<R, true> {
					constexpr static const char* const value = R::name::value;
				};

			constexpr static const char* const value = extract_if_possible<T, _value>::value;

			};
	template<class ...Args>
		struct print_permission_list;

	template<class T, class U, class ...Args>
		struct print_permission_list<pty::meta::tuple<T, U, Args...>> {
			static void into(std::ostream& oss) {
				oss << string_for<T>::value << ", ";
				print_permission_list<pty::meta::tuple<Args...>>::into(oss);
			}
		};

	template<class T>
		struct print_permission_list<pty::meta::tuple<T>> {
			static void into(std::ostream& oss) {
				oss << string_for<T>::value;
			}
		};

	template<>
		struct print_permission_list<pty::meta::tuple<>> {
			static void into(std::ostream&) {}
		};
}
}

template<class ...bosArgs, class ...Args>
std::basic_ostream<bosArgs...>& operator<<(std::basic_ostream<bosArgs...>& oss, pty::meta::tuple<Args...>) {
	oss << "{";
	pty::details::print_permission_list<pty::meta::tuple<Args...>>::into(oss);
	oss << "}";
	return oss;
}

#endif // GUARD_PTY_META_PRINTABLE_TUPLE_HPP__
