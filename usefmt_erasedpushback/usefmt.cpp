#include <usefmt/usefmt.h>

namespace usefmt {

nonstdstring internal_vformat(fmt::string_view format_string,
                              fmt::basic_format_args<cont> format_args) {
  nonstdstring s;
  fmt::vformat_to(std::back_inserter(s), format_string, format_args);
  return s;
}

nonstdstring internal_vprintf(fmt::string_view format_string,
                              fmt::basic_format_args<printf_cont> format_args) {
  nonstdstring s;
  printf_cont(std::back_inserter(s), format_string, format_args).format();
  return s;
}

}  // namespace usefmt