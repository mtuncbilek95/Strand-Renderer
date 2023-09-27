#pragma once

#include <iostream>

struct FileReader{
    static std::string GetShaderData(std::string dataName);

    static std::string GetFullPath(std::string pathName);
};
