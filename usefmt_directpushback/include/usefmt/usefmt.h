#ifndef USEFMT_H
#define USEFMT_H

#include <fmt/format.h>
#include <fmt/printf.h>
#include <nonstdstring/nonstdstring.h>

namespace usefmt {
template <typename... Args>
nonstdstring format(fmt::string_view format_string, Args&&... args) {
  nonstdstring s;
  fmt::format_to(std::back_inserter(s), format_string,
                 std::forward<Args>(args)...);
  return s;
}

template <
    typename S, typename... Args,
    typename = std::enable_if_t<std::is_base_of<fmt::compile_string, S>::value>>
nonstdstring format(const S& format_string, Args&&... args) {
  nonstdstring s;
  fmt::format_to(std::back_inserter(s), format_string,
                 std::forward<Args>(args)...);
  return s;
}

template <typename... Args>
nonstdstring sprintf(fmt::string_view format_string, Args&&... args) {
  using context =
      fmt::basic_printf_context<std::back_insert_iterator<nonstdstring>, char>;
  nonstdstring s;
  context(std::back_inserter(s), format_string,
          fmt::make_format_args<context>(std::forward<Args>(args)...))
      .format();
  return s;
}
}  // namespace usefmt

#endif