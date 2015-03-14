#include "life_game.hpp"

void life_game::next()
{
    auto next_matrix = *this;
    for (int y = top() - 1; y <= bottom() + 1; ++y) {
        for (int x = left() - 1; x <= right() + 1; ++x) {
            auto alives = count_around(x, y);
            if (get(x, y) == true) {
                if (alives != 2 && alives != 3) {
                    next_matrix.set(x, y, false);
                }
            } else {
                if (alives == 3) {
                    next_matrix.set(x, y, true);
                }
            }
        }
    }
    *this = std::move(next_matrix);
}

std::size_t life_game::count_around(int const& x, int const& y)
{
    std::size_t result = 0;
    if (get(x - 1, y - 1)) ++result;
    if (get(x - 1, y    )) ++result;
    if (get(x - 1, y + 1)) ++result;
    if (get(x    , y - 1)) ++result;
    if (get(x    , y + 1)) ++result;
    if (get(x + 1, y - 1)) ++result;
    if (get(x + 1, y    )) ++result;
    if (get(x + 1, y + 1)) ++result;
    return result;
}

// vim: set ts=4 sw=4 et:
