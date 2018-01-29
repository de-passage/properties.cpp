#ifndef GUARD_PTY_PERMISSIONS_HPP__
#define GUARD_PTY_PERMISSIONS_HPP__

#include "properties/details/define_property.hpp"

#include "properties/meta/tuple_operations.hpp"
#include "properties/meta/control.hpp"

namespace pty {

	namespace permissions {
#define PTY_DEFINE_PERMISSION(perm) \
		struct perm { struct name { constexpr static const char* const value = #perm; }; };

#define PTY_DETAILS_PERMISSION_LIST(a) \
		a(Read) \
		a(Write)

		PTY_DETAILS_PERMISSION_LIST(PTY_DEFINE_PERMISSION)

			namespace details {

				template<class T>
					struct get_permissions_or_new_tuple_t {
						typedef char yes;
						typedef struct {char d[2];} no;
						template<typename T1>
							static yes test(typename T1::Permissions*);
						template<typename T1>
							static no test(...);

						constexpr static const bool _value = ( sizeof(test<T>(0)) == sizeof(yes) );

						template<class R, bool Cond>
							struct extract_if_possible {
								typedef tuple<> value;
							};
						template<class R>
							struct extract_if_possible<R, true> {
								typedef typename R::Permissions value;
							};


						typedef typename extract_if_possible<T, _value>::value value;

					};
			}
		template<class T>
			using get = typename pty::permissions::details::get_permissions_or_new_tuple_t<T>::value;

	}


	template<class Base>
		struct ReadOnly : Base {
			using Base::operator=;
			typedef meta::prepend<permissions::Read, meta::remove<permissions::Write, permissions::get<Base>>> Permissions;
		};

	template<class Base>
		struct WriteOnly : Base {
			using Base::operator=;
			typedef meta::prepend<permissions::Write, meta::remove<permissions::Read, permissions::get<Base>>> Permissions;
		};

	template<class Base>
		struct ReadWrite : Base {
			using Base::operator=;
			typedef meta::prepend<permissions::Write, meta::prepend<permissions::Read, permissions::get<Base>>> Permissions;
		};

	template<class Base>
		struct NoAccess : Base {
			using Base::operator=;
			typedef meta::remove<permissions::Write, meta::remove<permissions::Read, permissions::get<Base>>> Permissions;
		};

	// Permission access meta-functions
	namespace permissions {

		namespace details {
			template<class P>
				struct is_readable_t {
					constexpr static const bool value =  meta::contains<Read, pty::permissions::get<P>>;
				};
		}

		template<class P>
			constexpr static const bool is_readable = details::is_readable_t<P>::value;

		namespace details {
			template<class P>
				struct is_writable_t {
					constexpr static const bool value =  meta::contains<Write, pty::permissions::get<P>>;
				};
		}

		template<class P>
			constexpr static const bool is_writable = details::is_writable_t<P>::value;

		template<class P>
			constexpr static const bool is_readable_and_writable = is_writable<P> && is_readable<P>;

		template<class P>
			constexpr static const bool is_read_write_protected = !is_writable<P> && !is_readable<P>;

		template<class P>
			constexpr static const bool is_read_only = is_readable<P> && !is_writable<P>;

	}


}

#undef PTY_DEFINE_PERMISSION
#undef PTY_DETAILS_PERMISSION_LIST
#undef PTY_DETAILS_PERMISSION_PROPERTY_LIST
#undef PTY_DETAILS_DEFINE_PERMISSION_PROPERTY

#endif // GUARD_PTY_PERMISSIONS_HPP__
