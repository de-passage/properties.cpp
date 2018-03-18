#include "properties.hpp"
#include "properties/permissions.hpp"

#include "properties/meta.hpp"

#include "properties/meta/printable_tuple.hpp"

#include <iostream>

struct A {};
struct B {typedef pty::meta::tuple<A, A> Permissions;};

struct C : pty::Properties<C, pty::ReadOnly> {};
struct D : pty::Properties<D, pty::WriteOnly> {};
struct E : pty::Properties<E, pty::ReadWrite> {};
struct F : pty::Properties<F, pty::NoAccess> {};

struct G : pty::Properties<G, pty::NoAccess, pty::WriteOnly> {};
struct H : pty::Properties<H, pty::WriteOnly, pty::NoAccess, pty::ReadOnly, pty::WriteOnly> {};

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_permissions() {
#else
int main() {
#endif
	typedef pty::permissions::get<A> T;
	typedef pty::permissions::get<B> T2;

	static_assert(pty::meta::is_same<pty::meta::tuple<>, T>, "detail func should get a new tuple unless one already exists");
	static_assert(pty::meta::is_same<pty::meta::tuple<A, A>, T2>, "detail func should get a new tuple unless one already exists");

	static_assert(pty::permissions::is_readable<C>, "");
	static_assert(!pty::permissions::is_writable<C>, "");

	static_assert(!pty::permissions::is_readable<D>, "");
	static_assert(pty::permissions::is_writable<D>, "");

	static_assert(pty::permissions::is_readable<E>, "");
	static_assert(pty::permissions::is_writable<E>, "");

	static_assert(!pty::permissions::is_readable<F>, "");
	static_assert(!pty::permissions::is_writable<F>, "");

	static_assert(!pty::permissions::is_readable<H>, "");
	static_assert(pty::permissions::is_writable<H>, "");

	//std::cout << "G :  " << pty::permissions::get<G>() << std::endl;
	//std::cout << "H :  " << pty::permissions::get<H>() << std::endl;

	std::cout << "Test `permissions` passed with success`" << std::endl;
#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
