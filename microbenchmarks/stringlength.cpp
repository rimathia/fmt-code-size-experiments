#include <benchmark/benchmark.h>
//#include <nonstdstring/nonstdstring.h>
#include <usefmt/usefmt.h>

static void fmt_longstring(benchmark::State& state) {
  std::string format_string = "{}" + std::string(state.range(0), ' ');
  for (auto _ : state) {
    usefmt::format(format_string, "Hi");
  }
}

BENCHMARK(fmt_longstring)->RangeMultiplier(10)->Range(10, 10'000'000);

static void printf_longstring(benchmark::State& state) {
  std::string format_string = "%s" + std::string(state.range(0), ' ');
  for (auto _ : state) {
    usefmt::sprintf(format_string, "Hi");
  }
}

BENCHMARK(printf_longstring)->RangeMultiplier(10)->Range(10, 10'000'000);

BENCHMARK_MAIN();