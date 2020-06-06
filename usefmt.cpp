#include <nonstdstring/nonstdstring.h>

#include <iostream>

int main() {
  std::cout << std::string(nonstdstring::fmt("{}", "fmt!\n"));
  std::cout << std::string(nonstdstring::fmt(FMT_STRING("{}\n"), 'A'));
  std::cout << std::string(nonstdstring::fmt(
      FMT_STRING("second argument: {1} and first argument: {0}\n"), "one",
      "two"));
  std::cout << std::string(nonstdstring::fmt(
      "a very long format string for a very short argument: {answer:4}\n",
      fmt::arg("answer", 42)));
}