#include "FileReader.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define STRING(x) #x"/"
#define XSTRING(x) STRING(x)

std::string FileReader::GetShaderData(std::string dataName)
{
    std::string fullPath = XSTRING(RENDER_ROOT);
    fullPath += + "Shaders/" + dataName + ".hlsl";

    HANDLE fileHandle;

    DWORD countByte;

    fileHandle = CreateFileA(fullPath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_ALWAYS,
                             FILE_ATTRIBUTE_READONLY, nullptr);

    const DWORD fileSize = GetFileSize(fileHandle, nullptr);

    char* stringFile = new char[fileSize + 1];
    stringFile[fileSize] = {'\0'};

    try {
        if(ReadFile(fileHandle, stringFile, fileSize, &countByte, nullptr)) {
            return std::string(stringFile);
        } else {
            throw "Unexpected file or path.";
        }
    }
    catch(const std::string exception) {
        printf("Error: %s", (char*) &exception);
        return nullptr;
    }
}

std::string FileReader::GetFullPath(std::string pathName)
{
    std::string fullPath = XSTRING(RENDER_ROOT);
    fullPath += pathName;

    return fullPath;
}
