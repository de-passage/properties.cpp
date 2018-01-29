#ifndef GUARD_PTY_HELPERS_APPLY_HPP
#define GUARD_PTY_HELPERS_APPLY_HPP

#include <type_traits>

namespace pty {

	template<class Op, class Return>
		struct apply {
			template<class T>
			inline constexpr Return operator()(const T& t) const {
				return Op()(t);
			}
			template<class T>
			inline constexpr Return operator()(T& t) const {
				return Op()(t);
			}
		};
	
	template<class Op, class Return, class RightHand>
	struct apply_left {
		inline explicit apply_left(const RightHand& r) : val(r) {}

		template<class T>
		inline constexpr Return operator()(const T& t) const {
			return Op()(t,val);
		}

		template<class T>
		inline constexpr Return operator()(T& t) const {
			return Op()(t,val);
		}

		inline constexpr RightHand value() const {
			return val;
		}

		private:
		const RightHand& val;
	};

	template<class Op, class Return, class RightHand>
	struct apply_right {
		inline explicit apply_right(const RightHand& r) : val(r) {}

		template<class T>
		inline constexpr Return operator()(const T& t) const {
			return Op()(val, t);
		}

		template<class T>
		inline constexpr Return operator()(T& t) const {
			return Op()(val,t);
		}

		inline constexpr RightHand value() const {
			return val;
		}
		private:
		const RightHand& val;
	};

}

#endif // GUARD_PTY_HELPERS_APPLY_HPP
