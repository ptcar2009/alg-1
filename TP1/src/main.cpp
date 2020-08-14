#include <queue>
#include <iostream>
#include "game.h"
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        throw "not enought arguments";
    }

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
}
