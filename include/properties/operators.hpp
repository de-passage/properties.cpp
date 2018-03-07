#ifndef GUARD_PTY_OPERATORS_HPP__
#define GUARD_PTY_OPERATORS_HPP__

#include "properties/operators/arithmetic.hpp"
#include "properties/operators/assign.hpp"
#include "properties/operators/bitwise.hpp"
#include "properties/operators/cast.hpp"
#include "properties/operators/comparison.hpp"
#include "properties/operators/incrementation.hpp"
#include "properties/operators/index.hpp"
#include "properties/operators/iteration.hpp"
#include "properties/operators/stream.hpp"

namespace pty { namespace operators {
typedef pty::meta::tuple<
	arithmetic,
	assign,
	bitwise,
	cast,
	comparison,
	shift,
	index,
	iteration,
	stream
		>	 all;
} }

#endif // GUARD_PTY_OPERATORS_HPP__
