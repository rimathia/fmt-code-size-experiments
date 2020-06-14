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