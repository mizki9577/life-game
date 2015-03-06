#include "matrix_type.hpp"

matrix_type::matrix_type()
{
    clear();
}

matrix_type::coordinate_type matrix_type::convert_coordinate(int const& x, int const& y) noexcept
{
    auto quadrant = std::ref(quadrant_br);
    std::size_t nx, ny;

    if (x >= 0) {
        nx = x;
        if (y >= 0) {
            quadrant = std::ref(quadrant_br);
            ny = y;
        } else {
            quadrant = std::ref(quadrant_ur);
            ny = -y - 1;
        }
    } else {
        nx = -x - 1;
        if (y >= 0) {
            quadrant = std::ref(quadrant_bl);
            ny = y;
        } else {
            quadrant = std::ref(quadrant_ul);
            ny = -y - 1;
        }
    }

    return coordinate_type{quadrant, nx, ny};
}

bool matrix_type::get(int const& x, int const& y) noexcept
{
    auto && coordinate = convert_coordinate(x, y);

    if (coordinate.quadrant.front().size() > coordinate.x && coordinate.quadrant.size() > coordinate.y) {
        return coordinate.quadrant[coordinate.y][coordinate.x];
    } else {
        return false;
    }
}

void matrix_type::set(int const& x, int const& y, bool const& value) noexcept
{
    auto && coordinate = convert_coordinate(x, y);

    if (value == true) {
        if (coordinate.y >= coordinate.quadrant.size() - 1) {
            coordinate.quadrant.resize(coordinate.y + 2, boost::dynamic_bitset<>(coordinate.quadrant.front().size()));
        }
        if (coordinate.x >= coordinate.quadrant.front().size() - 1) {
            for (auto&& row : coordinate.quadrant) {
                row.resize(coordinate.x + 2, false);
            }
        }
        coordinate.quadrant[coordinate.y][coordinate.x] = value;
    } else if (coordinate.x < coordinate.quadrant.front().size() - 1 && coordinate.y < coordinate.quadrant.size() - 1) {
        coordinate.quadrant[coordinate.y][coordinate.x] = value;
    }
}

void matrix_type::clear() noexcept
{
    boost::dynamic_bitset<> unit(1, 0);
    quadrant_br = { unit };
    quadrant_bl = { unit };
    quadrant_ul = { unit };
    quadrant_ur = { unit };
}

std::size_t matrix_type::width() const noexcept
{
    return std::max(quadrant_br.front().size(), quadrant_ur.front().size()) + std::max(quadrant_bl.front().size(), quadrant_ul.front().size()) - 2;
}

std::size_t matrix_type::height() const noexcept
{
    return std::max(quadrant_br.size(), quadrant_bl.size()) + std::max(quadrant_ul.size(), quadrant_ur.size()) - 2;
}

int matrix_type::top() const noexcept
{
    return -std::max(quadrant_ul.size(), quadrant_ur.size());
}

int matrix_type::bottom() const noexcept
{
    return std::max(quadrant_br.size(), quadrant_bl.size());
}

int matrix_type::left() const noexcept
{
    return -std::max(quadrant_bl.front().size(), quadrant_ul.front().size());
}

int matrix_type::right() const noexcept
{
    return std::max(quadrant_br.front().size(), quadrant_ur.front().size());
}

matrix_type matrix_type::shift(std::size_t const& x, std::size_t y) noexcept
{
    matrix_type result = *this;
    if (x > 0) {
        // shift to right

        // shift right quadrants to right.
        // for right quadrants, the direction "right" is backward (MSB side).
        // so shift operator is <<=.
        for (auto && row : result.quadrant_ur) {
            row <<= x;
        }
        for (auto && row : result.quadrant_br) {
            row <<= x;
        }

        // copy rightmost x bits of left quadrants to leftmost x bits of right quadrants.
        // for left quadrants, the direction "right" is frontward (LSB side).
        // and for right quadrants, the direction "left" is frontward (LSB side).
        // in addion, left quadrants is flipped horizontally.
        // so do following procedure for each row:
        //     1. select front x bits of left quadrant's row,
        //     2. flip horizontally it,
        //     3. and copy it to front of right quadrant's row.
        for (std::size_t i = 0; i < result.quadrant_ur.size(); ++i) {
            std::reverse_copy(result.quadrant_ul[i].begin(),
                              result.quadrant_ul[i].begin() + x,
                              result.quadrant_ur[i].begin());
        }
        for (std::size_t i = 0; i < result.quadrant_br.size(); ++i) {
            std::reverse_copy(result.quadrant_bl[i].begin(),
                              result.quadrant_bl[i].begin() + x,
                              result.quadrant_br[i].begin());
        }

        // shift left quadrants to right.
        // for left quadrants, the direction "right" is frontward (LSB side).
        // so shift operator is >>=.
        for (auto && row : result.quadrant_ul) {
            row >>= x;
        }
        for (auto && row : result.quadrant_bl) {
            row >>= x;
        }
    } else if (x < 0) {
    }

    if (y > 0) {
    } else if (y < 0) {
    }

    return result;
}

// vim: set ts=4 sw=4 et:
