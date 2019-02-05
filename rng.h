#ifndef RNG
#define RNG


#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>

namespace {

    struct rng 
    {
        static int get_seed()
        {
            int hour = std::atoi(__TIME__);
            int min = std::atoi(__TIME__ + 3);
            int sec = std::atoi(__TIME__ + 6);
            return 10000 * hour + 100 * min + sec;
        }

        get_rn()
        {
            // get_seed() returns an int based on __TIME__ (a string literal
            // set by the preprocessor), which is known at compile time.
            //
            // Also, w/r/t the engines in <random>: not setting a seed explicitly
            // will use a default seed, which is known at compile time.  So if
            // you're OK getting the same sequence of numbers for any compilation,
            // then "std::mt19937_64 rng;" may be all you need.
            std::mt19937_64 rng(get_seed());
            std::uniform_int_distribution<int16_t> plusminus(-1, 1);
            const int COUNT = 1000;
            std::generate_n(std::ostream_iterator<int16_t>(std::cout, "\n"), COUNT,
                [&rng, &plusminus]() { return plusminus(rng); });
            return 0;
        }
    };
}

#endif // RNG