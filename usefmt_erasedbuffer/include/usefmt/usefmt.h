#ifndef USEFMT_H
#define USEFMT_H

#include <fmt/format.h>
#include <fmt/printf.h>
#include <nonstdstring/nonstdstring.h>

namespace usefmt {
template <typename... Args>
nonstdstring fmt(fmt::string_view format_string, const Args&... args);

template <
    typename S, typename... Args,
    typename = std::enable_if_t<std::is_base_of<fmt::compile_string, S>::value>>
nonstdstring fmt(const S& format_string, const Args&... args);

template <typename... Args>
nonstdstring printf(fmt::string_view format_string, const Args&... args);

using cont =
    fmt::basic_format_context<std::back_insert_iterator<fmt::memory_buffer>,
                              char>;

using printf_cont =
    fmt::basic_printf_context<std::back_insert_iterator<fmt::memory_buffer>,
                              char>;

nonstdstring internal_vformat(fmt::string_view format_string,
                              fmt::basic_format_args<cont> format_args);

nonstdstring internal_vprintf(fmt::string_view format_string,
                              fmt::basic_format_args<printf_cont> format_args);
};  // namespace usefmt

template <typename... Args>
nonstdstring usefmt::fmt(fmt::string_view format_string, const Args&... args) {
  return internal_vformat(format_string, fmt::make_format_args<cont>(args...));
}

template <typename S, typename... Args, typename>
nonstdstring usefmt::fmt(const S& format_string, const Args&... args) {
  fmt::detail::check_format_string<Args...>(format_string);
  return usefmt::fmt(fmt::string_view(format_string), args...);
}

template <typename... Args>
nonstdstring usefmt::printf(fmt::string_view format_string,
                            const Args&... args) {
  return internal_vprintf(format_string,
                          fmt::make_format_args<printf_cont>(args...));
}
#endif
