
#include "util.h"

void day1_part_two()
{
    auto ints = TokenizeFileToInt("input/day1.txt", '\n');

    size_t count = ints.size();

    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    bool found = false;
    for (i = 0; i < count - 1; ++i)
    {
        for (j = i; j < count; ++j)
        {
            for (k = j; k < count; ++k)
            {
                if (ints[i] + ints[j] + ints[k] == 2020)
                {
                    found = true;
                    goto done;
                }
            }
        }
    }
    done:

    assert(found);
    if (found)
        PrintF(ConsoleColor::Green, "Day 1 part 2: %lld\n", int64_t(ints[i]) * ints[j] * ints[k]);
    else
        PrintF(ConsoleColor::Red, "Day 1 part 2: Result not found\n");
}

void day1_part_one()
{
    auto ints = TokenizeFileToInt("input/day1.txt", '\n');

    size_t count = ints.size();

    size_t i = 0;
    size_t j = 0;
    bool found = false;
    for (i = 0; i < count - 1; ++i)
    {
        for (j = i; j < count; ++j)
        {
            if (ints[i] + ints[j] == 2020)
            {
                found = true;
                goto done;
            }
        }
    }
    done:

    assert(found);
    if (found)
        PrintF(ConsoleColor::Green, "Day 1 part 1: %d\n", ints[i] * ints[j]);
    else
        PrintF(ConsoleColor::Red, "Day 1: Result not found\n");

}

void day1_run()
{
    day1_part_one();
    day1_part_two();
}
