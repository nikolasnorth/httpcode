#pragma once
#include <string_view>

namespace httpcode {

static constexpr std::string_view invalid_num_arguments =
    "Error: Invalid number of arguments given.\n";

static constexpr std::string_view invalid_code =
    "Error: Invalid HTTP status code.\n";

static constexpr std::string_view usage = "Usage: httpcode <code>\n";

}  // namespace httpcode
