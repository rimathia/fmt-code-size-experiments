#ifndef NONSTDSTRING_H
#define NONSTDSTRING_H

#include <fmt/format.h>
#include <fmt/printf.h>

#include <array>
#include <string>
#include <vector>

class nonstdstring : public std::vector<char> {
 public:
  nonstdstring() = default;
  nonstdstring(const char* first, const char* last)
      : std::vector<char>(first, last) {}

  explicit operator std::string() const;

  template <typename... Args>
  static nonstdstring fmt(fmt::string_view format_string, const Args&... args);

  template <typename S, typename... Args,
            typename = std::enable_if_t<
                std::is_base_of<fmt::compile_string, S>::value>>
  static nonstdstring fmt(const S& format_string, const Args&... args);

  template <typename... Args>
  static nonstdstring printf(fmt::string_view format_string,
                             const Args&... args);

  void reserve(std::size_t new_cap);
  void push_back(const char& value);

 private:
  using backit = std::back_insert_iterator<nonstdstring>;

  using cont = fmt::basic_format_context<backit, char>;
  using truncated_cont =
      fmt::basic_format_context<fmt::detail::truncating_iterator<char*>, char>;

  using printf_cont = fmt::basic_printf_context<backit, char>;
  using truncated_printf_cont =
      fmt::basic_printf_context<fmt::detail::truncating_iterator<char*>, char>;

  static fmt::format_to_n_result<char*> internal_vformat_to_n(
      char* first, std::size_t n, fmt::string_view format_string,
      fmt::basic_format_args<truncated_cont> format_args);

  static backit internal_vformat_to(backit it, fmt::string_view format_string,
                                    fmt::basic_format_args<cont> format_args);

  static fmt::format_to_n_result<char*> internal_vprintf_to_n(
      char* first, std::size_t n, fmt::string_view format_string,
      fmt::basic_format_args<truncated_printf_cont> format_args);

  static backit internal_vprintf_to(
      backit it, fmt::string_view format_string,
      fmt::basic_format_args<printf_cont> format_args);
};

template <typename... Args>
nonstdstring nonstdstring::fmt(fmt::string_view format_string,
                               const Args&... args) {
  std::array<char, 32> buffer;
  const auto it_size =
      internal_vformat_to_n(std::begin(buffer), buffer.size(), format_string,
                            fmt::make_format_args<truncated_cont>(args...));
  if (it_size.size <= buffer.size()) {
    return nonstdstring(std::begin(buffer), it_size.out);
  } else {
    nonstdstring s;
    s.reserve(it_size.size);
    internal_vformat_to(std::back_inserter(s), format_string,
                        fmt::make_format_args<cont>(args...));
    return s;
  }
}

template <typename S, typename... Args, typename>
nonstdstring nonstdstring::fmt(const S& format_string, const Args&... args) {
  fmt::internal::check_format_string<Args...>(format_string);
  return fmt(fmt::string_view(format_string), args...);
}

template <typename... Args>
nonstdstring nonstdstring::printf(fmt::string_view format_string,
                                  const Args&... args) {
  std::array<char, 32> buffer;
  const auto it_size = internal_vprintf_to_n(
      std::begin(buffer), buffer.size(), format_string,
      fmt::make_format_args<truncated_printf_cont>(args...));
  if (it_size.size <= buffer.size()) {
    return nonstdstring(std::begin(buffer), it_size.out);
  } else {
    nonstdstring s;
    s.reserve(it_size.size);
    internal_vprintf_to(std::back_inserter(s), format_string,
                        fmt::make_format_args<printf_cont>(args...));
    return s;
  }
}
#endif
