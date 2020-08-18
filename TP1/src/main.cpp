#include <queue>
#include <iostream>
#include <string>
#include "game.hpp"
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "not enough arguments" << std::endl
                  << "usage: " << argv[0] << " [-b | --benchmark] (file)";
    }
#if defined(BENCHMARK)
    clock_t t;

    t = clock();

#endif // BENCHMARK

    auto game = new Game(argv[1]);
    auto result = game->Play();

    if (result.second == -1)
    {
        std::cout << "SEM VENCEDORES\n";
    }
    else
    {
        std::cout << result.first << std::endl
                  << result.second << std::endl;
    }
#if defined(BENCHMARK)

    t = clock() - t;
    std::cout << "\nnumber of clock cycles: " << t << std::endl;

#endif // BENCHMARK
}
