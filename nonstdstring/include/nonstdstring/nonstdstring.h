#ifndef NONSTDSTRING_H
#define NONSTDSTRING_H

#include <string>
#include <vector>

class nonstdstring : public std::vector<char> {
 public:
  nonstdstring() = default;
  nonstdstring(const char* first, const char* last)
      : std::vector<char>(first, last) {}
  nonstdstring(const char* first, std::size_t n)
      : std::vector<char>(first, first + n) {}

  explicit operator std::string() const;

  void reserve(std::size_t new_cap);
  void push_back(const char& value);
};

#endif