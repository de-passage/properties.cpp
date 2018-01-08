#ifndef GUARD_PTY_DETAILS_SELF_HPP__
#define GUARD_PTY_DETAILS_SELF_HPP__

namespace pty {
	namespace details {
		template<class Base>
			struct Self {
				protected:
					inline ~Self() = default;

					inline constexpr const Base& self() const {
						return *static_cast<const Base*>(this);
					}

					inline constexpr Base& self() {
						return *static_cast<Base*>(this);
					}
			};
	}
}
#endif
