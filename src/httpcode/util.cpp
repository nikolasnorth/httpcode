#include "util.hpp"

#include <sstream>
#include <string>

namespace httpcode {

tl::expected<int, std::exception> to_digit(std::string_view s) noexcept {
  try {
    return std::stoi(std::string(s));
  } catch (const std::exception& e) {
    return tl::make_unexpected(e);
  }
}

std::string format_output(unsigned int code, std::string_view short_desc,
                          std::string_view long_desc,
                          std::string_view learn_more_url) {
  std::ostringstream oss;
  oss << code << " " << short_desc << '\n'
      << long_desc << "\n\n"
      << "Learn more: " << learn_more_url << '\n';
  return oss.str();
}

}  // namespace httpcode
