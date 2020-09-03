#include <usefmt/usefmt.h>

namespace usefmt {

nonstdstring internal_vformat(
    fmt::string_view format_string,
    fmt::basic_format_args<truncated_cont> format_args_trunc,
    fmt::basic_format_args<cont> format_args) {
  BufferArray buffer;
  const auto it_size = fmt::vformat_to_n(std::begin(buffer), buffer.size(),
                                         format_string, format_args_trunc);
  if (it_size.size <= buffer.size()) {
    return nonstdstring(std::begin(buffer), it_size.out);
  } else {
    nonstdstring s(it_size.size);
    using af = fmt::detail::arg_formatter<decltype(s.data()), char>;
    fmt::vformat_to<af>(s.data(), format_string, format_args);
    return s;
  }
}

nonstdstring internal_vprintf(
    fmt::string_view format_string,
    fmt::basic_format_args<truncated_printf_cont> format_args_trunc,
    fmt::basic_format_args<printf_cont> format_args) {
  BufferArray buffer;
  const auto truncit =
      truncated_printf_cont(
          fmt::detail::truncating_iterator<BufferArray::iterator>(
              std::begin(buffer), buffer.size()),
          format_string, format_args_trunc)
          .format();
  if (truncit.count() <= buffer.size()) {
    return nonstdstring(std::begin(buffer), truncit.count());
  } else {
    nonstdstring s(truncit.count());
    printf_cont(s.data(), format_string, format_args).format();
    return s;
  }
}

}  // namespace usefmt