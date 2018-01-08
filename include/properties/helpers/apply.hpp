#ifndef GUARD_PTY_HELPERS_APPLY_HPP
#define GUARD_PTY_HELPERS_APPLY_HPP

#include <type_traits>

namespace pty {

	template<class Op, class Return>
		struct apply {
			template<class T>
			constexpr Return operator()(const T& t) const {
				return Op()(t);
			}
			template<class T>
			constexpr Return operator()(T& t) const {
				return Op()(t);
			}
		};
	
	template<class Op, class Return, class RightHand>
	struct apply_left {
		explicit apply_left(const RightHand& r) : val(r) {}

		template<class T>
		constexpr Return operator()(const T& t) const {
			return Op()(t,val);
		}

		template<class T>
		constexpr Return operator()(T& t) const {
			return Op()(t,val);
		}

		constexpr RightHand value() const {
			return val;
		}

		private:
		const RightHand& val;
	};

	template<class Op, class Return, class LeftHand>
	struct apply_right {
		explicit apply_right(const LeftHand& r) : val(r) {}

		template<class T>
		constexpr Return operator()(const std::remove_cv_t<T>& t) const {
			return Op()(val, t);
		}

		template<class T>
		constexpr Return operator()(std::remove_cv_t<T>& t) const {
			return Op()(val,t);
		}

		constexpr LeftHand value() const {
			return val;
		}
		private:
		const LeftHand& val;
	};

}

#endif // GUARD_PTY_HELPERS_APPLY_HPP
