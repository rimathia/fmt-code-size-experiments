#include <nonstdstring/nonstdstring.h>

std::vector<nonstdstring> examples()
{
    return {
        nonstdstring::fmt("{}\n", int(3)),
        nonstdstring::fmt("{}, {:.2f}\n", int(3), double(1.234)),
        nonstdstring::fmt("{}, {:.2f}, {}\n", 2, 1.8, "hi"),
        nonstdstring::fmt("{}, {:.2f}, {}\n", 2, 1.8, "hi again"),
        nonstdstring::fmt("{}, {}, {}, {}, {}\n", 1, 2, 3, "and", 4)
    };
}
