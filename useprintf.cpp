#include <nonstdstring/nonstdstring.h>

#include <iostream>

int main() {
  std::cout << std::string(nonstdstring::printf("%s", "printf!\n"));
  std::cout << std::string(nonstdstring::printf("%c\n", 'A'));
  std::cout << std::string(
      nonstdstring::printf("%s %d\n", "the answer is", 42));
  std::cout << std::string(nonstdstring::printf("%d, %.2f\n", 42, 1.234));
  std::cout << std::string(nonstdstring::printf(
      "format with increasing precision: %.2f, %.3f, %.4f\n", 1.23456, 1.23456,
      1.23456));
}