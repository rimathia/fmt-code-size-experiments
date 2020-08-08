#include <nonstdstring/nonstdstring.h>
#include <usefmt/usefmt.h>

#include <iostream>

int main() {
  std::cout << std::string(usefmt::format("{{}}\n"));
  std::cout << std::string(usefmt::format("{}", "fmt!\n"));
  std::cout << std::string(usefmt::format(FMT_STRING("{}\n"), 'A'));
  std::cout << std::string(usefmt::format(
      FMT_STRING("second argument: {1} and first argument: {0}\n"), "one",
      "two"));
  std::cout << std::string(usefmt::format(
      "a very long format string for a very short argument: {answer:4}\n",
      fmt::arg("answer", 42)));
}