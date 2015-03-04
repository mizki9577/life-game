#ifndef LIFE_GAME_HPP
#define LIFE_GAME_HPP

#include "life-game-core_global.hpp"
#include "matrix_type.hpp"

class LIFEGAMECORESHARED_EXPORT life_game : matrix_type
{
    public:
        life_game() = default;
        ~life_game() = default;

        void next() noexcept;

        matrix_type matrix;

    private:
        std::size_t count_around(int const& x, int const& y);
};

#endif // LIFE_GAME_HPP
// vim: set ts=4 sw=4 et:
