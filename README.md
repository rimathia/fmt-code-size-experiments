# fmt-code-size-experiments
Experiments for using fmt with a custom string library with the goal of minimal code size overhead for the consumers of the custom string library and reasonable performance.

There are different versions of usefmt trying out different ways of wrapping. The summary is: `usefmt_erasedbuffer` is the way to go. Although this always results in a copy from the internal buffer to the custom string using a fixed-size buffer on the stack (as in `usefmt_singlealloc`) apparently isn't worth it.

The Dockerfile serves to determine code sizes on linux using gcc 9, it can be run right from the root directory: ```docker build .```. It omits the microbenchmarks.
