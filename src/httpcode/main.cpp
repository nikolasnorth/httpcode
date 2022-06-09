#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tl/expected.hpp>

#include "codes.hpp"

namespace httpcode {

/// STDOUT Messages

static constexpr std::string_view invalid_num_arguments =
    "Error: Invalid number of arguments given.\n";

static constexpr std::string_view invalid_code =
    "Error: Invalid HTTP status code.\n";

static constexpr std::string_view invalid_category =
    "Error: Invalid HTTP status category name. Valid names are informational, "
    "success, redirection, client-error, and server-error.\n";

static constexpr std::string_view usage = "Usage: httpcode <code>\n";

/// Utility functions

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

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << httpcode::invalid_num_arguments;
    std::cerr << httpcode::usage;
    return 1;
  }

  const std::string_view arg1 = argv[1];
  const auto code = httpcode::to_digit(arg1);
  if (code.has_value() && httpcode::codes.contains(*code)) {
    const auto& [short_desc, long_desc, url] = httpcode::codes.at(*code);
    std::cout << httpcode::format_output(*code, short_desc, long_desc, url);
    return 0;
  } else if (code.has_value()) {
    std::cerr << httpcode::invalid_code;
    std::cerr << httpcode::usage;
    return 1;
  }

  if (arg1 == "list" && argc == 3) {
    const std::string_view category = argv[2];
    const auto output = httpcode::list_all_codes_for_category(category);
    if (!output.has_value()) {
      std::cerr << httpcode::invalid_category;
    }
    std::cout << *output;
    return 0;
  } else if (arg1 == "list") {
    std::cout << httpcode::list_all_codes();
    return 0;
  } else {
    std::cerr << "Error: Invalid command " << arg1 << '\n';
    std::cerr << httpcode::usage;
  }
}
