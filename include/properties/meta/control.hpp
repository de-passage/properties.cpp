#ifndef GUARD_PTY_META_CONTROL_HPP__
#define GUARD_PTY_META_CONTROL_HPP__

namespace pty {
	namespace meta {
		template<bool B, class If, class Else>
		struct if_t {
			typedef Else value;
		};
		template<class If, class Else>
			struct if_t<false, If, Else> {
				typedef If value;
			};

		template<bool Cond, class If, class Else>
			using IF = typename if_t<Cond, If, Else>::value;

	}
}


#endif // GUARD_PTY_META_CONTROL_HPP__
