#include "zip/zip.hpp"
#include <iostream>

int main()
{
    cov::zip file("./covscript.zip");
    auto buff = file.entry_open("covscript/README.md");
    std::cout.write((char*)buff.data, buff.size);
    return 0;
}