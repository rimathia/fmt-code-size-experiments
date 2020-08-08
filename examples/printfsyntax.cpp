#include <nonstdstring/nonstdstring.h>
#include <usefmt/usefmt.h>

#include <iostream>

int main() {
  std::cout << std::string(usefmt::sprintf("%%\n"));
  std::cout << std::string(usefmt::sprintf("%s", "printf!\n"));
  std::cout << std::string(usefmt::sprintf("%c\n", 'A'));
  std::cout << std::string(usefmt::sprintf("%s %d\n", "the answer is", 42));
  std::cout << std::string(usefmt::sprintf("%d, %.2f\n", 42, 1.234));
  std::cout << std::string(
      usefmt::sprintf("format with increasing precision: %.2f, %.3f, %.4f\n",
                     1.23456, 1.23456, 1.23456));
}