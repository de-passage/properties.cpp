
#ifndef GUARD_PTY_DETAILS_COMPARABLE_OPERATIONS_HPP__
#define GUARD_PTY_DETAILS_COMPARABLE_OPERATIONS_HPP__

#include "details/operation.hpp"
#include <functional>

namespace pty {
	using less = details::binary_operator<std::less>;
	using greater = details::binary_operator<std::greater>;
	using less_equal = details::binary_operator<std::less_equal>;
	using greater_equal = details::binary_operator<std::greater_equal>;
	using equal_to = details::binary_operator<std::equal_to>;
	using not_equal_to = details::binary_operator<std::not_equal_to>;
}
#endif
