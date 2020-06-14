#include <usefmt/usefmt.h>

namespace usefmt {

nonstdstring internal_vformat(fmt::string_view format_string,
                              fmt::basic_format_args<cont> format_args) {
  fmt::memory_buffer buf;
  fmt::vformat_to(std::back_inserter(buf), format_string, format_args);
  return nonstdstring(buf.data(), buf.size());
}

nonstdstring internal_vprintf(fmt::string_view format_string,
                              fmt::basic_format_args<printf_cont> format_args) {
  fmt::memory_buffer buf;
  printf_cont(std::back_inserter(buf), format_string, format_args).format();
  return nonstdstring(buf.data(), buf.size());
}

}  // namespace usefmt