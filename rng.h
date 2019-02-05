#ifndef RNG
#define RNG


#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <random>

#include "sprite_animation.h"

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

        int get_rn(void)
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
            const int COUNT = 100;
            std::array<int16_t, COUNT> arr;

            /*
            std::generate_n(std::back_inserter(arr), COUNT,
                            [&rng, &plusminus]() {
                                return plusminus(rng);
                            });
            */
            /* std::generate_n(std::ostream_iterator<int16_t>(std::cout, "\n"), COUNT, 
                            [&rng, &plusminus]() {
                                return plusminus(rng);
                            }); */
            return 0;
        }
    };
}

#endif // RNG