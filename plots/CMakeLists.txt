add_custom_command(OUTPUT stringlengthbenchmark_buf32grow2.json
DEPENDS stringlengthbenchmark_buf32grow2
COMMAND ../microbenchmarks/stringlengthbenchmark_buf32grow2 
ARGS --benchmark_out=stringlengthbenchmark_buf32grow2.json)

add_custom_command(OUTPUT stringlengthbenchmark_buf512grow2.json
DEPENDS stringlengthbenchmark_buf512grow2
COMMAND ../microbenchmarks/stringlengthbenchmark_buf512grow2 
ARGS --benchmark_out=stringlengthbenchmark_buf512grow2.json)

add_custom_command(OUTPUT stringlengthbenchmark_buf1024grow2.json
DEPENDS stringlengthbenchmark_buf1024grow2
COMMAND ../microbenchmarks/stringlengthbenchmark_buf1024grow2 
ARGS --benchmark_out=stringlengthbenchmark_buf1024grow2.json)

add_custom_command(OUTPUT stringlengthbenchmark_erasedbuffer.json
DEPENDS stringlengthbenchmark_erasedbuffer
COMMAND ../microbenchmarks/stringlengthbenchmark_erasedbuffer 
ARGS --benchmark_out=stringlengthbenchmark_erasedbuffer.json)

#add_custom_command(
#        OUTPUT stringlengthplots.py
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_CURRENT_SOURCE_DIR}/stringlengthplotsxyz.py
#                ${CMAKE_CURRENT_BINARY_DIR}/stringlengthplots.py)
#
add_custom_target(stringlengthplots
DEPENDS stringlengthbenchmark_buf32grow2.json stringlengthbenchmark_buf512grow2.json stringlengthbenchmark_buf1024grow2.json stringlengthbenchmark_erasedbuffer.json stringlengthplots.py
COMMAND python3 ARGS stringlengthplots.py)
