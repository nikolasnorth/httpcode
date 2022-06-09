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

  const std::string_view arg1 = argv[1];
  const auto code = httpcode::to_digit(arg1);
  if (code.has_value() && httpcode::codes.contains(*code)) {
    const auto& [short_desc, long_desc, url] = httpcode::codes.at(*code);
    std::cout << httpcode::format_output(*code, short_desc, long_desc, url);
    return 0;
  } else if (code.has_value()) {
    // HTTP code does not exist.
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
