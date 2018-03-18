#include "properties/meta/tuple_operations.hpp"

#include "properties/meta.hpp"

struct A;
struct B;

void bar(A&) {}

#ifdef PTY_TEST_INCLUDE_ALL_TESTS
void test_tuple_operations() {
#else
int main() {
#endif
	typedef pty::meta::prepend<A, pty::meta::prepend<B, pty::meta::tuple<>>> T1;
	static_assert(pty::meta::is_same<pty::meta::tuple<A, B>, T1>, "T1 should be t<A, B>");
	typedef pty::meta::concat<T1, T1> T2;
	static_assert(pty::meta::is_same<pty::meta::tuple<A, B, A, B>, T2>, "T2 should be t<A,B,A,B>");
	typedef pty::meta::remove<B, T2> T3;
	static_assert(pty::meta::is_same<pty::meta::tuple<A,A>, T3>, "T3 should be t<A,A>");
	typedef pty::meta::remove<A, T3> T4;
	static_assert(pty::meta::is_same<pty::meta::tuple<>, T4>, "T4 should be empty");
	static_assert(pty::meta::contains<A, pty::meta::tuple<A, B>>, "contains should find elements on 1st place");
	static_assert(pty::meta::contains<B, pty::meta::tuple<A, B>>, "contains should find elements on any place");
	static_assert(!pty::meta::contains<B, T3>, "contains should not find non existent elements");
	static_assert(pty::meta::is_same<pty::meta::flatten<pty::meta::tuple<pty::meta::tuple<A, B>, pty::meta::tuple<B, A>>>, pty::meta::tuple<A, B, B, A>>, "");

#ifndef PTY_TEST_INCLUDE_ALL_TESTS
	return 0;
#endif
}
