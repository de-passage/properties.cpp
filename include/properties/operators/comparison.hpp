#ifndef GUARD_PTY_OPERATORS_COMPARISON_HPP__
#define GUARD_PTY_OPERATORS_COMPARISON_HPP__

#include "properties/meta/tuple.hpp"
#include "properties/details/comparison_operation_macro.hpp"

namespace pty {

    namespace operators {
      PTY_DETAILS_APPLY_TO_COMPARISON_OPERATORS(PTY_DETAILS_DEFINE_BINARY_CONST_OPERATION) 

      typedef pty::meta::tuple<	pty::operators::less, 
              pty::operators::greater, 
              pty::operators::less_equal, 
              pty::operators::greater_equal, 
              pty::operators::equal_to, 
              pty::operators::not_equal_to
                  > comparison;
    }
}
#endif// GUARD_PTY_OPERATORS_COMPARISON_HPP__
