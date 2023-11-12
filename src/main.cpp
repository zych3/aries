#include <iostream>
#include <fmt/core.h>
#include "Game.h"

int main()
{
    try
    {
        aries::Game game;
        game.run();
    }
    catch (std::exception& e)
    {
        fmt::println("EXCEPTION: {}",
					 e.what());
    }
}