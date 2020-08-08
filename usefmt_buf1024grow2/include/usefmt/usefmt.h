#ifndef USEFMT_H
#define USEFMT_H

#include <fmt/format.h>
#include <fmt/printf.h>
#include <memory_buffer/memory_buffer.h>
#include <nonstdstring/nonstdstring.h>

namespace usefmt {
template <typename... Args>
nonstdstring format(fmt::string_view format_string, const Args&... args);

template <
    typename S, typename... Args,
    typename = std::enable_if_t<std::is_base_of<fmt::compile_string, S>::value>>
nonstdstring format(const S& format_string, const Args&... args);

template <typename... Args>
nonstdstring sprintf(fmt::string_view format_string, const Args&... args);

using buffer = membuf::memory_buffer<membuf::FactorTwo, 1024>;

using cont = fmt::basic_format_context<std::back_insert_iterator<buffer>, char>;

using printf_cont =
    fmt::basic_printf_context<std::back_insert_iterator<buffer>, char>;

nonstdstring internal_vformat(fmt::string_view format_string,
                              fmt::basic_format_args<cont> format_args);

nonstdstring internal_vprintf(fmt::string_view format_string,
                              fmt::basic_format_args<printf_cont> format_args);
};  // namespace usefmt

template <typename... Args>
nonstdstring usefmt::format(fmt::string_view format_string,
                            const Args&... args) {
  return internal_vformat(format_string, fmt::make_format_args<cont>(args...));
}

template <typename S, typename... Args, typename>
nonstdstring usefmt::format(const S& format_string, const Args&... args) {
  fmt::detail::check_format_string<Args...>(format_string);
  return usefmt::format(fmt::string_view(format_string), args...);
}

template <typename... Args>
nonstdstring usefmt::sprintf(fmt::string_view format_string,
                             const Args&... args) {
  return internal_vprintf(format_string,
                          fmt::make_format_args<printf_cont>(args...));
}
#endif
