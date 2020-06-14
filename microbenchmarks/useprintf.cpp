#include <benchmark/benchmark.h>
#include <nonstdstring/nonstdstring.h>
#include <usefmt/usefmt.h>

static void printf_double(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::printf("double: %.6f", 1.23456789);
  }
}

BENCHMARK(printf_double);

static void printf_longstring(benchmark::State& state) {
  std::string format_string = "%s" + std::string(state.range(0), ' ');
  for (auto _ : state) {
    usefmt::printf(format_string, "Hi");
  }
}

BENCHMARK(printf_longstring)->RangeMultiplier(10)->Range(10, 10'000'000);

BENCHMARK_MAIN();