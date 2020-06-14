#include <benchmark/benchmark.h>

static void copy(benchmark::State& state) {
  std::vector<char> source(state.range(0), 'X');
  std::vector<char> dest(state.range(0), 'Y');
  for (auto _ : state) {
    std::copy(std::begin(source), std::end(source), std::begin(dest));
  }
  assert(std::equal(std::begin(source), std::end(source), std::begin(dest)));
}

BENCHMARK(copy)->RangeMultiplier(10)->Range(10, 10'000'000);

BENCHMARK_MAIN();