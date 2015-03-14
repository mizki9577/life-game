#include "life_game.hpp"

void life_game::next()
{
    // 8 方向にシフトする
    matrix_type Z3, Z2, Z1, Z0,
                I1 = shifted(-1, -1),
                I2 = shifted( 0, -1),
                I3 = shifted( 1, -1),
                I4 = shifted(-1,  0),
                I5 = shifted( 1,  0),
                I6 = shifted(-1,  1),
                I7 = shifted( 0,  1),
                I8 = shifted( 1,  1);

    Z0 = ~(I1 | I2);
    Z1 = I1 ^ I2;
    Z2 = I1 & I2;

    Z3 = Z2 & I3;
    Z2 = (Z1 & I3) | (Z2 & ~I3);
    Z1 = (Z0 & I3) | (Z1 & ~I3);
    Z0 = Z0 & ~I3;

    Z3 = (Z2 & I4) | (Z3 & ~I4);
    Z2 = (Z1 & I4) | (Z2 & ~I4);
    Z1 = (Z0 & I4) | (Z1 & ~I4);
    Z0 = Z0 & ~I4;

    Z3 = (Z2 & I5) | (Z3 & ~I5);
    Z2 = (Z1 & I5) | (Z2 & ~I5);
    Z1 = (Z0 & I5) | (Z1 & ~I5);
    Z0 = Z0 & ~I5;

    Z3 = (Z2 & I6) | (Z3 & ~I6);
    Z2 = (Z1 & I6) | (Z2 & ~I6);
    Z1 = (Z0 & I6) | (Z1 & ~I6);
    Z0 = Z0 & ~I6;

    Z3 = (Z2 & I7) | (Z3 & ~I7);
    Z2 = (Z1 & I7) | (Z2 & ~I7);
    Z1 = (Z0 & I7) | (Z1 & ~I7);
    Z0 = Z0 & ~I7;

    Z3 = (Z2 & I8) | (Z3 & ~I8);
    Z2 = (Z1 & I8) | (Z2 & ~I8);

    *this = static_cast<life_game&&>(Z3 | (*this & Z2));
}

// vim: set ts=4 sw=4 et:
