add_library(usefmt_erasedbuffer usefmt.cpp include/usefmt/usefmt.h)
target_include_directories(usefmt_erasedbuffer PUBLIC include)
target_link_libraries(usefmt_erasedbuffer PUBLIC fmt)
target_link_libraries(usefmt_erasedbuffer PUBLIC nonstdstring)