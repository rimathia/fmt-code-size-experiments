#include <benchmark/benchmark.h>
#include <nonstdstring/nonstdstring.h>
#include <usefmt/usefmt.h>

#include <cmath>

constexpr double pi = M_PI;

static void fmt_double(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::format("double: {:.6f}", pi);
  }
}
BENCHMARK(fmt_double);

static void fmt_longdouble(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::format("double: {:.16f}", pi);
  }
}
BENCHMARK(fmt_longdouble);

static void fmt_fivedoubles(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::format("five doubles: {:.16f}, {:.16f}, {:.16f}, {:.16f}, {:.16f}",
                   pi, pi / 2, pi / 3, pi / 4, pi / 5);
  }
}
BENCHMARK(fmt_fivedoubles);

static void fmt_tendoubles(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::format(
        "ten doubles: {:.16f}, {:.16f}, {:.16f}, {:.16f}, {:.16f}, {:.16f}, "
        "{:.16f}, {:.16f}, {:.16f}, {:.16f}",
        pi, pi / 2, pi / 3, pi / 4, pi / 5, pi / 6, pi / 7, pi / 8, pi / 9,
        pi / 10);
  }
}
BENCHMARK(fmt_tendoubles);

static void printf_double(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::sprintf("double: %.6f", pi);
  }
}
BENCHMARK(printf_double);

static void printf_longdouble(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::sprintf("double: %.16f", pi);
  }
}
BENCHMARK(printf_longdouble);

static void printf_fivedoubles(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::sprintf("five doubles: %.16f, %.16f, %.16f, %.16f, %.16f", pi,
                    pi / 2, pi / 3, pi / 4, pi / 5);
  }
}
BENCHMARK(printf_fivedoubles);

static void printf_tendoubles(benchmark::State& state) {
  for (auto _ : state) {
    usefmt::sprintf(
        "ten doubles: %.16f, %.16f, %.16f, %.16f, %.16f, %.16f, %.16f, %.16f, "
        "%.16f, %.16f",
        pi, pi / 2, pi / 3, pi / 4, pi / 5, pi / 6, pi / 7, pi / 8, pi / 9,
        pi / 10);
  }
}
BENCHMARK(printf_tendoubles);

BENCHMARK_MAIN();