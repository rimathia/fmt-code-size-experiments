#include <nonstdstring/nonstdstring.h>

// #include <iostream>

nonstdstring::operator std::string() const {
  return std::string(begin(), end());
}

void nonstdstring::reserve(std::size_t new_cap) {
  // std::cout << "reserve " << new_cap << "\n";
  std::vector<char>::reserve(new_cap);
}

void nonstdstring::push_back(const char& c) {
  // if (capacity() == size()) {
  //  std::cout << "push_back called at exhausted capacity " << capacity()
  //            << "\n";
  //}
  std::vector<char>::push_back(c);
}

fmt::format_to_n_result<char*> nonstdstring::internal_vformat_to_n(
    char* first, std::size_t n, fmt::string_view format_string,
    fmt::basic_format_args<nonstdstring::truncated_cont> format_args) {
  return fmt::vformat_to_n(first, n, format_string, format_args);
}

nonstdstring::backit nonstdstring::internal_vformat_to(
    nonstdstring::backit it, fmt::string_view format_string,
    fmt::basic_format_args<nonstdstring::cont> format_args) {
  return fmt::vformat_to(it, format_string, format_args);
}

fmt::format_to_n_result<char*> nonstdstring::internal_vprintf_to_n(
    char* first, std::size_t n, fmt::string_view format_string,
    fmt::basic_format_args<nonstdstring::truncated_printf_cont> format_args) {
  const auto truncit =
      truncated_printf_cont(fmt::detail::truncating_iterator<char*>(first, n),
                            format_string, format_args)
          .format();
  auto ret = fmt::format_to_n_result<char*>();
  ret.out = truncit.base();
  ret.size = truncit.count();
  return ret;
}

nonstdstring::backit nonstdstring::internal_vprintf_to(
    nonstdstring::backit it, fmt::string_view format_string,
    fmt::basic_format_args<nonstdstring::printf_cont> format_args) {
  return printf_cont(it, format_string, format_args).format();
}