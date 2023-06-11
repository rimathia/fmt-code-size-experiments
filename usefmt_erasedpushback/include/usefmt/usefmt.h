#ifndef USEFMT_H
#define USEFMT_H

#include <fmt/format.h>
#include <fmt/printf.h>
#include <nonstdstring/nonstdstring.h>

namespace usefmt {
template <typename... Args>
nonstdstring format(fmt::v10::format_string<Args...> format_string,
                    Args&&... args) {
  nonstdstring s;
  fmt::vformat_to(std::back_inserter(s), format_string,
                  fmt::make_format_args(std::forward<Args>(args)...));
  return s;
}

template <typename... Args>
nonstdstring sprintf(fmt::string_view format_string, Args&&... args) {
  // from what I can see, there is no interface like vformat_to which would take
  // a back_inserter
  using context = fmt::v10::basic_printf_context_t<char>;
  auto buf = fmt::v10::basic_memory_buffer<char>();
  fmt::v10::detail::vprintf<char, context>(
      buf, fmt::v10::detail::to_string_view(format_string),
      fmt::make_format_args<context>(args...));
  return nonstdstring(std::begin(buf), std::end(buf));
}
}  // namespace usefmt

#endif
