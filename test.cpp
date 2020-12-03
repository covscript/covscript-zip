#include "zip.hpp"
#include <iostream>
#include <fstream>

int main()
{
    cov::zip file("./covscript.zip", cov::zip::openmode::append);
    std::ifstream ifs("./cs.exe", std::ios::binary);
    if (!ifs)
        std::cout << "BAD!" << std::endl;
    else
        file.write_entry_stream("fxxk/a.exe", ifs);
    return 0;
}