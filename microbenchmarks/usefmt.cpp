#include <benchmark/benchmark.h>
#include <nonstdstring/nonstdstring.h>
#include <usefmt/usefmt.h>

static void fmt_double(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::format("double: {:.6f}", 1.23456789);
  }
}

BENCHMARK(fmt_double);

static void fmt_longstring(benchmark::State& state) {
  std::string format_string = "{}" + std::string(state.range(0), ' ');
  for (auto _ : state) {
    usefmt::format(format_string, "Hi");
  }
}

BENCHMARK(fmt_longstring)->RangeMultiplier(10)->Range(10, 10'000'000);

BENCHMARK_MAIN();