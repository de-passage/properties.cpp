#ifndef GUARD_PTY_STREAMABLE_HPP__
#define GUARD_PTY_STREAMABLE_HPP__

namespace pty {
	namespace operators {
		template<class T>
			struct stream_out {
				template<class U, class ...R>
					T& operator()(T& oss, const U& t, R... r) const {
						return operator()(oss << t, r...);
					}
				template<class U>
					T& operator()(T& oss, const U& t) const {
						return oss << t;
					}
			};

		template<class T>
			struct stream_in {
				template<class U, class ...R>
					T& operator()(T& oss, U& t, R... r) const {
						return operator()((oss >> t), r...);
					}
				template<class U>
					T& operator()(T& oss, const U& t) const {
						return oss >> t;
					}
			};


	}

	template<class T>
		struct Streamable : T {

			template<class S, class U>
				friend constexpr S& ::operator<<(S&, const Streamable<U>&);

			template<class S, class U>
				friend constexpr S& ::operator>>S&, const Streamable<U>&);

		};
}

template<class S, class Q>
constexpr S& operator<<(S& t, const pty::Streamable<Q>& s) {
	return downcast(&s).operator_base(pty::operators::stream_out<S>(), t);
}

template<class S, class Q>
constexpr S& operator>>S& t, const pty::Streamable<Q>& s) {
	return downcast(&s).operator_base(pty::operators::stream_in<S>(), t);
}
#endif // GUARD_PTY_STREAMABLE_HPP__
