#include "matrix_type.hpp"

matrix_type::matrix_type()
{
    clear();
}

bool operator==(matrix_type const& lhs, matrix_type const& rhs)
{
    return    lhs.quadrant_br == rhs.quadrant_br
           && lhs.quadrant_bl == rhs.quadrant_bl
           && lhs.quadrant_ul == rhs.quadrant_ul
           && lhs.quadrant_ur == rhs.quadrant_ur;
}

matrix_type::coordinate_type matrix_type::convert_coordinate(int const& x, int const& y) const
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

bool matrix_type::get(int const& x, int const& y) const
{
    auto && coordinate = convert_coordinate(x, y);

    if (coordinate.quadrant.front().size() > coordinate.x && coordinate.quadrant.size() > coordinate.y) {
        return coordinate.quadrant[coordinate.y][coordinate.x];
    } else {
        return false;
    }
}

void matrix_type::set(int const& x, int const& y, bool const& value)
{
    auto && coordinate = convert_coordinate(x, y);
    auto & quadrant = const_cast<quadrant_type&>(coordinate.quadrant);

    if (value == true) {
        if (coordinate.y >= quadrant.size() - 1) {
            quadrant.resize(coordinate.y + 2, my_dynamic_bitset<>(quadrant.front().size()));
        }
        if (coordinate.x >= quadrant.front().size() - 1) {
            for (auto&& row : quadrant) {
                row.resize(coordinate.x + 2, false);
            }
        }
        quadrant[coordinate.y][coordinate.x] = value;
    } else if (coordinate.x < quadrant.front().size() - 1 && coordinate.y < quadrant.size() - 1) {
        quadrant[coordinate.y][coordinate.x] = value;
    }
}

void matrix_type::clear()
{
    my_dynamic_bitset<> unit(1, 0);
    quadrant_br = { unit };
    quadrant_bl = { unit };
    quadrant_ul = { unit };
    quadrant_ur = { unit };
}

std::size_t matrix_type::width() const
{
    return std::max(quadrant_br.front().size(), quadrant_ur.front().size()) + std::max(quadrant_bl.front().size(), quadrant_ul.front().size()) - 2;
}

std::size_t matrix_type::height() const
{
    return std::max(quadrant_br.size(), quadrant_bl.size()) + std::max(quadrant_ul.size(), quadrant_ur.size()) - 2;
}

int matrix_type::top() const
{
    return -std::max(quadrant_ul.size(), quadrant_ur.size());
}

int matrix_type::bottom() const
{
    return std::max(quadrant_br.size(), quadrant_bl.size());
}

int matrix_type::left() const
{
    return -std::max(quadrant_bl.front().size(), quadrant_ul.front().size());
}

int matrix_type::right() const
{
    return std::max(quadrant_br.front().size(), quadrant_ur.front().size());
}

matrix_type matrix_type::shift(int const& x, int const& y)
{
    /* 非常に混乱するメモ
     *
     * nビット右シフトは次の手順で行われる:
     *  1. 右側の象限をnビット右シフトする
     *  2. 右側の右端の番人ビットを0にする
     *  3. 左側の象限の右側nビットを右側の象限の左側nビットにコピーする
     *  4. 左側の象限をnビット右シフトする
     * 左シフトは上記の手順を左右に反転すれば同じである.
     *
     * 実際には, 右側の象限の右端はMSB, 左端はLSB,
     *           左側の象限の右端はLSB, 左端はMSBになる.
     * すなわち, 右側の象限の右シフトはMSB側へのシフトになるので左シフトに,
     *           左側の象限の右シフトはLSB側へのシフトになるので右シフトになる.
     * また, 右側の象限から左側の象限,
     * あるいは左側の象限から右側の象限へビット列をコピーするとき,
     * そのビット列は左右反転させた状態でコピーされねばならない.
     */

    matrix_type result = *this;
    if (x > 0) {
        // 右にシフトする

        // 1. 右側の象限をxビット右シフトする
        // 2. 右側の右端の番人ビットを0にする
        for (auto && row : result.quadrant_ur) {
            row <<= x;
            row[row.size() - 1] = false;
        }
        for (auto && row : result.quadrant_br) {
            row <<= x;
            row[row.size() - 1] = false;
        }

        // 3. 左側の象限の右側xビットを右側の象限の左側xビットにコピーする
        for (std::size_t i = 0; i < result.quadrant_ul.size() && i < result.quadrant_ur.size(); ++i) {
            auto part = result.quadrant_ul[i];
            part.crop(0, x).reverse().copy_to(result.quadrant_ur[i]);
        }
        for (std::size_t i = 0; i < result.quadrant_bl.size() && i < result.quadrant_br.size(); ++i) {
            auto part = result.quadrant_bl[i];
            part.crop(0, x).reverse().copy_to(result.quadrant_br[i]);
        }

        // 4. 左側の象限をnビット右シフトする
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
