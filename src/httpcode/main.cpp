#include <iostream>
#include <string_view>

#include "codes.hpp"
#include "stdout_messages.hpp"
#include "util.hpp"

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    std::cerr << httpcode::invalid_num_arguments;
    std::cerr << httpcode::usage;
    return 1;
  }

  const auto code = httpcode::to_digit(std::string_view(argv[1]));
  if (!code.has_value() || !httpcode::codes.contains(*code)) {
    std::cerr << httpcode::invalid_code;
    std::cerr << httpcode::usage;
    return 1;
  }

  const auto& [short_desc, long_desc, url] = httpcode::codes.at(*code);
  std::cout << httpcode::format_output(*code, short_desc, long_desc, url);
}
