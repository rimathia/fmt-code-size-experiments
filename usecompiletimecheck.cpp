#include <nonstdstring/nonstdstring.h>

#include <iostream>

std::vector<nonstdstring> examples();

int main()
{
        const auto ex = examples();
        for (const auto& e : ex)
        {
                std::cout << std::string(e);
        }
}
