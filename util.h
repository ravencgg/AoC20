#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cstdint>
#include <cassert>

using int64 = int64_t;
using int32 = int32_t;
using int16 = int16_t;
using int8  = int8_t;
using uint64 = uint64_t;
using uint32 = uint32_t;
using uint16 = uint16_t;
using uint8  = uint8_t;

template <typename Container, typename Function>
size_t erase_if(Container& container, Function predicate)
{
    size_t cur = container.size();
    container.erase(std::remove_if(container.begin(), container.end(), predicate), container.end());
    return cur - container.size();
}

#define arrsize(_arr) (sizeof(_arr) / sizeof(_arr[0]))

using StringList = std::vector<std::string>;
using IntList = std::vector<int>;
using IntList64 = std::vector<int64>;

std::string ReadEntireFile(const char* filename);

// Removes empty tokens!
StringList TokenizeString(const std::string& input_, char token);
StringList TokenizeFile(const char* filename, char token);

IntList TokenizeFileToInt(const char* filename, char token);
IntList TokenizeStringToInt(const std::string& input_, char token);
IntList StringListToIntList(const StringList& strings);

IntList64 TokenizeFileToInt64(const char* filename, char token);
IntList64 TokenizeStringToInt64(const std::string& input_, char token);
IntList64 StringListToIntList64(const StringList& strings);

std::string SafeSubString(const std::string& input, size_t begin, size_t end);
std::string SafeSubStringFromEnd(const std::string& input, size_t begin, size_t end);



enum class ConsoleColor
{
    Normal,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Count,
};
void SetConsoleColor(ConsoleColor color);
void ClearConsoleColor();
void PrintF(ConsoleColor color, const char* format, ...);
