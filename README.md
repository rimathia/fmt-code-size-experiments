# fmt-code-size-experiments
Experiments for using fmt with a custom string library with the goal of minimal code size overhead for the consumers of the custom string library and reasonable performance. The underlying assumption is that there are many executables running which use the custom string library, therefore having some code in the shared custom string library instead of in every executable saves quite a bit of code size.

The Dockerfile serves to determine code sizes on linux using gcc 9, it can be run right from the root directory: ```docker build . --tag=fmt-code-size-experiments```. It omits the microbenchmarks.

The baseline for using `fmt` with a custom string class is the library `usefmt_directpushback` which is only a header. The other `usefmt_` libraries all try to get the code into a shared library. For the `fmt` family of functions the code size overhead when using `fmt_directpushback` is about 1.6K, but for the `printf`-style functions it is about 45K.

There are different versions of usefmt trying out different ways of wrapping. The summary is: `usefmt_erasedbuffer` is the way to go. Although this always results in a copy from the internal buffer to the custom string using a fixed-size buffer on the stack (as in `usefmt_singlealloc`) apparently isn't worth it.
