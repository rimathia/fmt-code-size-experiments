# fmt-code-size-experiments
Experiments for using fmt with a custom string library with the goal of minimal code size overhead for the consumers of the custom string library and reasonable performance.

There are different versions of usefmt trying out different ways of wrapping. The summary is: `usefmt_erasedbuffer` is the way to go. If almost all of your formatted custom strings fit into a buffer of a few 100 bytes `usefmt_singleallocation` may be worth trying, but for longer strings you pay about almost a factor of 2.

The Dockerfile serves to determine code sizes on linux using gcc 9, it can be run right from the root directory: ```docker build --tag fmt-code-size-experiments```. It omits the microbenchmarks.
