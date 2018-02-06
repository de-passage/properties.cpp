#ifndef GUARD_PTY_DETAILS_DEDUCE_ITERATOR_TAG_HPP__
#define GUARD_PTY_DETAILS_DEDUCE_ITERATOR_TAG_HPP__

#include "properties/meta/has_operator_base_overload.hpp"
#include "properties/meta/property_hierarchy_info.hpp"
#include "properties/operators/iteration.hpp"
#include "properties/operators/comparison.hpp"

#include <iterator>

namespace pty {
	namespace details {

		template<class Class, class Iterator>
			static constexpr bool meets_minimum_iterator_requirements =
				pty::meta::has_operator_base_overload<Class, pty::operators::dereference_iterator, Iterator> &&
				(pty::meta::has_operator_base_overload<Class, pty::operators::increment_iterator, Iterator> ||
				 pty::meta::has_operator_base_overload<Class, pty::operators::offset_iterator, Iterator, int>);

		template<class Class, class Iterator>
			static constexpr bool meets_input_iterator_requirements = 
				pty::meta::has_operator_base_overload<Class, pty::operators::compare_iterators, pty::operators::equal_to, Iterator, Iterator>;

		template<class Class, class Iterator>
			static constexpr bool meets_forward_iterator_requirements = std::is_default_constructible<Class>::value;

		template<class Class, class Iterator>
			static constexpr bool meets_bidirectional_iterator_requirements =
				pty::meta::has_operator_base_overload<Class, pty::operators::decrement_iterator, Iterator> ||
				pty::meta::has_operator_base_overload<Class, pty::operators::offset_iterator, Iterator, int>;

		template<class Class, class Iterator>
			static constexpr bool meets_random_access_iterator_requirements = false;

		template<class Class, class Iterator>
			static constexpr bool meets_output_iterator_requirements =
				std::is_class<Class>::value || std::is_pointer<Class>::value;

		struct minimum_iterator_requirement_not_met;
		template<class Class, class Iterator>
			struct deduce_iterator_tag_t {
				typedef 
					std::conditional_t< 
						meets_minimum_iterator_requirements<Class, Iterator>,
						std::conditional_t<
							meets_input_iterator_requirements<Class, Iterator>,
							std::conditional_t<
								meets_forward_iterator_requirements<Class, Iterator>,
								std::conditional_t<
									meets_bidirectional_iterator_requirements<Class, Iterator>,
									std::conditional_t<
										meets_random_access_iterator_requirements<Class, Iterator>,
										std::random_access_iterator_tag,
										std::bidirectional_iterator_tag>,
									std::forward_iterator_tag>,
								std::input_iterator_tag>,
							std::conditional_t<
								meets_output_iterator_requirements<Class, Iterator>,
								std::output_iterator_tag,
								minimum_iterator_requirement_not_met> >,
						minimum_iterator_requirement_not_met>
					value;
			};

		template<class C, class Iterator>
			using deduce_iterator_tag = typename deduce_iterator_tag_t<C, Iterator>::value;
	}
}


#endif // GUARD_PTY_DETAILS_DEDUCE_ITERATOR_TAG_HPP__

