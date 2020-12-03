#include "zip.hpp"
#include <iostream>

int main()
{
    cov::zip file("./a.zip", cov::zip::openmode::append);
    auto opt = file.get_entries();
    if (!opt)
        std::cout << "OK" << std::endl;
    else {
        for (auto &it : *opt)
            std::cout << it.name << std::endl;
    }
    return 0;
}