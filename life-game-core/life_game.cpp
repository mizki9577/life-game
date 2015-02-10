#include "life_game.hpp"

void life_game::next() noexcept
{
    auto next_matrix = matrix;
    for (int y = matrix.top(); y < matrix.bottom(); ++y) {
        for (int x = matrix.left(); x < matrix.right(); ++x) {
            auto alives = count_around(x, y);
            if (matrix.get(x, y) == true) {
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
    matrix = std::move(next_matrix);
}

std::size_t life_game::count_around(int const& x, int const& y) const
{
    std::size_t result = 0;
    if (matrix.get(x - 1, y - 1)) ++result;
    if (matrix.get(x - 1, y    )) ++result;
    if (matrix.get(x - 1, y + 1)) ++result;
    if (matrix.get(x    , y - 1)) ++result;
    if (matrix.get(x    , y + 1)) ++result;
    if (matrix.get(x + 1, y - 1)) ++result;
    if (matrix.get(x + 1, y    )) ++result;
    if (matrix.get(x + 1, y + 1)) ++result;
    return result;
}

// vim: set ts=4 sw=4 et:
