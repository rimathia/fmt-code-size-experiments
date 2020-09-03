#include <benchmark/benchmark.h>
//#include <nonstdstring/nonstdstring.h>
#include <usefmt/usefmt.h>

static void fmt_longstring_front(benchmark::State& state) {
  std::string format_string = "{}" + std::string(state.range(0), ' ');
  for (auto _ : state) {
    usefmt::format(format_string, "Hi");
  }
}

BENCHMARK(fmt_longstring_front)
    ->Arg(10)
    ->Arg(33)
    ->Arg(100)
    ->Arg(333)
    ->Arg(1000)
    ->Arg(3333)
    ->Arg(10000);

static void fmt_longstring_back(benchmark::State& state) {
  std::string format_string = std::string(state.range(0), ' ') + "{}";
  for (auto _ : state) {
    usefmt::format(format_string, "Hi");
  }
}

BENCHMARK(fmt_longstring_back)
    ->Arg(10)
    ->Arg(33)
    ->Arg(100)
    ->Arg(333)
    ->Arg(1000)
    ->Arg(3333)
    ->Arg(10000);

static void printf_longstring_front(benchmark::State& state) {
  std::string format_string = "%s" + std::string(state.range(0), ' ');
  for (auto _ : state) {
    usefmt::sprintf(format_string, "Hi");
  }
}

BENCHMARK(printf_longstring_front)
    ->Arg(10)
    ->Arg(33)
    ->Arg(100)
    ->Arg(333)
    ->Arg(1000)
    ->Arg(3333)
    ->Arg(10000);

static void printf_longstring_back(benchmark::State& state) {
  std::string format_string = std::string(state.range(0), ' ') + "%s";
  for (auto _ : state) {
    usefmt::sprintf(format_string, "Hi");
  }
}

BENCHMARK(printf_longstring_back)
    ->Arg(10)
    ->Arg(33)
    ->Arg(100)
    ->Arg(333)
    ->Arg(1000)
    ->Arg(3333)
    ->Arg(10000);

BENCHMARK_MAIN();