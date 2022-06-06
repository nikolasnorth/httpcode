#pragma once

#include <exception>
#include <string>
#include <string_view>
#include <tl/expected.hpp>

namespace httpcode {

tl::expected<int, std::exception> to_digit(std::string_view s) noexcept;

std::string format_output(unsigned int code, std::string_view short_desc,
                          std::string_view long_desc,
                          std::string_view learn_more_url);

}  // namespace httpcode
