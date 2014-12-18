#include <iostream>
#include "life_game.hpp"

int main()
{
    life_game game;
    game.matrix.set(0, 1, true);
    game.matrix.set(1, 0, true);
    game.matrix.set(1, 1, true);
    game.matrix.set(1, 2, true);
    game.matrix.set(2, 0, true);

    int bottom, right;
    while (true) {
        bottom = game.matrix.bottom();
        right = game.matrix.right();
        for (int y = game.matrix.top(); y < bottom; ++y) {
            for (int x = game.matrix.left(); x < right; ++x) {
                std::cout << (game.matrix.get(x, y) ? "*" : " ");
            }
            std::cout << std::endl;
        }
        std::cout << "----------------" << std::endl;
        game.next();
    }
    return 0;
}
