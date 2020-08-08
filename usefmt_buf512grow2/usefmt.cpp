#include <usefmt/usefmt.h>

namespace usefmt {

nonstdstring internal_vformat(fmt::string_view format_string,
                              fmt::basic_format_args<cont> format_args) {
  buffer buf;
  using af =
      fmt::detail::arg_formatter<decltype(std::back_inserter(buf)), char>;
  fmt::vformat_to<af>(std::back_inserter(buf), format_string, format_args);
  return nonstdstring(buf.begin(), buf.size());
}

nonstdstring internal_vprintf(fmt::string_view format_string,
                              fmt::basic_format_args<printf_cont> format_args) {
  buffer buf;
  printf_cont(std::back_inserter(buf), format_string, format_args).format();
  return nonstdstring(buf.begin(), buf.size());
}

}  // namespace usefmt