import argparse
import json
import glob
import os
import subprocess
import matplotlib.pyplot as plt
import shutil

BENCHMARK_GROUPS = {"default": ["erasedpushback", "erasedbuffer", "singlealloc", "originalfmt"], "bufsizes": [
    "buf32grow2", "buf512grow2", "buf1024grow2", "originalfmt"]}


def removeprefix(s: str, prefix: str) -> str:
    if s.startswith(prefix):
        return s[len(prefix):]
    else:
        return s[:]


def removesuffix(s: str, suffix: str) -> str:
    # suffix='' should not call self[:-0].
    if suffix and s.endswith(suffix):
        return s[:-len(suffix)]
    else:
        return s[:]


def plot_series(data, prefix, title, suffix):
    fig, ax = plt.subplots()
    ax.set(xlabel="n", ylabel="ns")
    plt.title(title)
    plt.yscale('log')
    plt.xscale('log')
    for (key, results) in data.items():
        x = []
        y = []
        for benchmark in results["benchmarks"]:
            if benchmark["name"].startswith(prefix):
                x.append(int(benchmark["name"].split("/")[-1]))
                y.append(benchmark["real_time"])
        if (len(x) > 0):
            ax.plot(x, y, label=key, marker='x', linestyle=":")
    fig.legend(loc="upper left", bbox_to_anchor=(0.15, 0.85))
    fig.savefig(prefix + "_{}.png".format(suffix))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='run microbenchmarks for formatting strings of various lengths.')
    parser.add_argument('--compiler', default="clang++",
                        help="CMAKE_CXX_COMPILER={compiler}")
    parser.add_argument(
        "--reconfigure", help="recreate build directory, start by running cmake", action="store_true")
    args = parser.parse_args()

    compiler = args.compiler
    builddir = "build_microbenchmarks_{}".format(compiler.split("/")[-1])
    if args.reconfigure or not os.path.exists(builddir):
        try:
            shutil.rmtree(builddir)
        except FileNotFoundError:
            None
        os.mkdir(builddir)
    os.chdir(builddir)
    subprocess.check_call(
        "cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_CXX_COMPILER={} ..".format(compiler), shell=True)
    subprocess.check_call("make -j", shell=True)

    for (benchmarkgroup, benchmarks) in BENCHMARK_GROUPS.items():

        slbenchmarks = ["microbenchmarks/stringlengthbenchmark_{}".format(
            benchmark) for benchmark in benchmarks]
        for slbenchmark in slbenchmarks:
            output = "{}.json".format(slbenchmark)
            try:
                if os.path.getmtime(output) > os.path.getmtime(slbenchmark):
                    print("not running {} because output {} is up to date".format(
                        slbenchmark, output))
                    continue
            except:
                None
            subprocess.check_call(
                [slbenchmark, "--benchmark_out={}".format(output)])

        results = dict()
        for slbenchmark in slbenchmarks:
            filename = "{}.json".format(slbenchmark)
            key = removeprefix(os.path.split(slbenchmark)
                               [-1], "stringlengthbenchmark_")
            results[key] = json.load(open(filename))
        compilerversion = subprocess.check_output(
            [compiler, "--version"]).splitlines()[0]
        plot_series(results, "fmt_longstring",
                    title="{}".format(compilerversion), suffix=benchmarkgroup)
        plot_series(results, "printf_longstring",
                    title="{}".format(compilerversion), suffix=benchmarkgroup)
