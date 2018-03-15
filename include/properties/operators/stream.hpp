#ifndef GUARD_PTY_OPERATOR_STREAM_HPP__
#define GUARD_PTY_OPERATOR_STREAM_HPP__

#include "properties/meta/tuple.hpp"
#include <utility>

namespace pty {
	namespace operators {
		namespace details { 
			// Allows the user of the stream operators to send multiple values at once
			template<template<class> class Op>
				struct stream_adaptor {
					template<class T, class U, class ...R>
						inline constexpr decltype(auto) operator()(T&& t, U&& u, R&&...r) const {
							return operator()(Op<T>()(std::forward<T>(t), std::forward<U>(u)), std::forward<R>(r)...);
						}
						
					template<class T, class U>
						inline constexpr decltype(auto) operator()(T&& t, U&& u) const {
							return Op<T>()(std::forward<T>(t), std::forward<U>(u));
						}

					constexpr static const char * const name = Op<stream_adaptor>::name;
				};

			// Actual operators
			template<class T>
				struct stream_out {
					template<class U>
						inline decltype(auto) operator()(T&& oss, U&& t) const {
							return std::forward<T>(oss) << std::forward<U>(t);
						}
					constexpr static const char* const name = "operator_stream_out(<<)";
				};

			template<class T>
				struct stream_in {
					template<class U>
						inline decltype(auto) operator()(T&& iss, U&& t) const {
							return std::forward<T>(iss) >> std::forward<U>(t);
						}
					constexpr static const char* const name = "operator_stream_out(>>)";
				};
		}

		using stream_in = details::stream_adaptor<details::stream_in>;
		using stream_out = details::stream_adaptor<details::stream_out>;


		typedef pty::meta::tuple<stream_in, stream_out> stream;


	}
}
#endif // GUARD_PTY_OPERATOR_STREAM_HPP__
