#include <nonstdstring/nonstdstring.h>

std::vector<nonstdstring> examples()
{
    return {
        nonstdstring::fmt(FMT_STRING("{}\n"), int(3)),
        nonstdstring::fmt(FMT_STRING("{}, {:.2f}\n"), int(3), double(1.234)),
        nonstdstring::fmt(FMT_STRING("{}, {:.2f}, {}\n"), 2, 1.8, "hi"),
        nonstdstring::fmt(FMT_STRING("{}, {:.2f}, {}\n"), 2, 1.8, "hi again"),
        nonstdstring::fmt(FMT_STRING("{}, {}, {}, {}, {}\n"), 1, 2, 3, "and", 4),
    };
}
