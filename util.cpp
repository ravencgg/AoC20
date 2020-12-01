#include "util.h"

#include <stdarg.h>

std::string ReadEntireFile(const char* filename)
{
    FILE* file = nullptr;
    if (fopen_s(&file, filename, "rb") != 0 || file == nullptr)
    {
        printf("ERROR opening input file");
        return {};
    }

    std::string result;
    fseek(file, 0, SEEK_END);
    auto filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    result.resize(filesize);
    fread(&result[0], filesize, 1, file);
    fclose(file);
    return result;
}

StringList TokenizeString(const std::string& input_, char token)
{
    std::string input = input_;
    if (token == '\n')
        erase_if(input, [](const char& c) { return c == '\r'; });

    StringList result;
    size_t pos = 0;
    while (pos != std::string::npos)
    {
        size_t end = input.find(token, pos);
        size_t next_pos = std::string::npos;
        if (end == std::string::npos)
            end = input.size();
        else
            next_pos = end + 1;

        if (end != std::string::npos && end != pos)
        {
            result.push_back(input.substr(pos, end - pos));
            ++end;
        }
        pos = next_pos;
    }

    return result;
}

StringList TokenizeFile(const char* filename, char token)
{
    return TokenizeString(ReadEntireFile(filename), token);
}

IntList TokenizeFileToInt(const char* filename, char token)
{
    return TokenizeStringToInt(ReadEntireFile(filename), token);
}

IntList TokenizeStringToInt(const std::string& input_, char token)
{
    StringList temp = TokenizeString(input_, token);
    return StringListToIntList(temp);
}

IntList StringListToIntList(const StringList& strings)
{
    IntList result;
    result.reserve(strings.size());
    for (auto& str : strings)
        result.push_back(atoi(str.c_str()));
    return result;
}

IntList64 TokenizeFileToInt64(const char* filename, char token)
{
    return TokenizeStringToInt64(ReadEntireFile(filename), token);
}

IntList64 StringListToIntList64(const StringList& strings)
{
    IntList64 result;
    result.reserve(strings.size());
    for (auto& str : strings)
        result.push_back(strtoll(str.c_str(), nullptr, 0));
    return result;
}

IntList64 TokenizeStringToInt64(const std::string& input_, char token)
{
    StringList temp = TokenizeString(input_, token);
    return StringListToIntList64(temp);
}

std::string SafeSubString(const std::string& input, size_t begin, size_t end)
{
    begin = std::min(begin, input.size());
    end = std::min(end, input.size());
    auto result = input.substr(begin, end - begin);
    return result;
}

std::string SafeSubStringFromEnd(const std::string& input, size_t begin, size_t end)
{
    int64_t size = input.size();
    int64_t s = size - begin;
    int64_t e = size - end;
    e = std::clamp(e, 0ll, size);
    s = std::clamp(s, 0ll, e);
    return SafeSubString(input, s, e);
}


void SetConsoleColor(ConsoleColor color)
{
    const char* colors[] = {
        "\x1B[0m",
        "\x1B[1;31m",
        "\x1B[1;32m",
        "\x1B[1;33m",
        "\x1B[1;34m",
        "\x1B[1;35m",
        "\x1B[1;36m",
        "\x1B[1;37m",
    };
    static_assert((int)ConsoleColor::Count == arrsize(colors));

    printf("%s", colors[(int)color]);
}

void ClearConsoleColor()
{
    SetConsoleColor(ConsoleColor::Normal);
}

void PrintF(ConsoleColor color, const char* format, ...)
{
    SetConsoleColor(color);
    va_list list;
    va_start(list, format);
    vprintf(format, list);
    va_end(list);
    ClearConsoleColor();
}
