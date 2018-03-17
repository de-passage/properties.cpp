#ifndef GUARD_PTY_OPERATORS_CAST_HPP__
#define GUARD_PTY_OPERATORS_CAST_HPP__
namespace pty {
	namespace operators {
		struct cast {
			template<class Ret, class In>
			constexpr Ret operator()(const In& obj) const {
				return static_cast<Ret>(obj);
			}
			constexpr static const char* const name = "operator_cast";
		};
	}
}

#endif //GUARD_PTY_OPERATORS_CAST_HPP__
