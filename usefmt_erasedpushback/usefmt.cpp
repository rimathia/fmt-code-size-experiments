#include <usefmt/usefmt.h>

#include <vector>

using backit = std::back_insert_iterator<std::vector<char>>;

template backit fmt::vformat_to<backit>(backit, fmt::string_view,
                                        fmt::format_args);
