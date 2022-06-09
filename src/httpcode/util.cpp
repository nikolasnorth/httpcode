#include "util.hpp"

#include <sstream>
#include <stdexcept>
#include <tl/expected.hpp>

#include "codes.hpp"

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
                          std::string_view learn_more_url) noexcept {
  std::ostringstream oss;
  oss << code << " " << short_desc << '\n'
      << long_desc << "\n\n"
      << "Learn more: " << learn_more_url << '\n';
  return oss.str();
}

std::string list_all_codes() noexcept {
  std::ostringstream oss;
  oss << "HTTP Status Codes:\n";
  for (const auto& [code, desc] : codes) {
    const auto& [short_desc, _1, _2] = desc;
    oss << code << " " << short_desc << '\n';
  }
  return oss.str();
}

tl::expected<std::string, std::exception> list_all_codes_for_category(
    std::string_view category) noexcept {
  std::ostringstream oss;
  std::map<unsigned int, description>::const_iterator lo;
  std::map<unsigned int, description>::const_iterator hi;
  if (category == "informational") {
    lo = codes.lower_bound(100);
    hi = codes.upper_bound(199);
    oss << "HTTP Status Codes – Informational:\n";
  } else if (category == "success") {
    lo = codes.lower_bound(200);
    hi = codes.upper_bound(299);
    oss << "HTTP Status Codes – Success:\n";
  } else if (category == "redirection") {
    lo = codes.lower_bound(300);
    hi = codes.upper_bound(399);
    oss << "HTTP Status Codes – Success:\n";
  } else if (category == "client-error") {
    lo = codes.lower_bound(400);
    hi = codes.upper_bound(499);
    oss << "HTTP Status Codes – Client Error:\n";
  } else if (category == "server-error") {
    lo = codes.lower_bound(500);
    hi = codes.upper_bound(599);
    oss << "HTTP Status Codes – Server Error:\n";
  } else {
    return tl::make_unexpected(std::invalid_argument("Invalid category name."));
  }

  for (; lo != hi; ++lo) {
    const auto& [code, info] = *lo;
    const auto& [short_desc, _1, _2] = info;
    oss << code << " " << short_desc << '\n';
  }

  return oss.str();
}

}  // namespace httpcode
