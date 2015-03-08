#include "matrix_type.hpp"

matrix_type::matrix_type()
{
    clear();
}

bool operator==(matrix_type const& lhs, matrix_type const& rhs)
{
    std::set<std::pair<int, int>> lhs_trues, rhs_trues;
    for (int x = lhs.left(); x <= lhs.right(); ++x) {
        for (int y = lhs.top(); y <= lhs.bottom(); ++y) {
            if (lhs.get(x, y) == true) {
                lhs_trues.insert({x, y});
            }
        }
    }
    for (int x = rhs.left(); x <= rhs.right(); ++x) {
        for (int y = rhs.top(); y <= rhs.bottom(); ++y) {
            if (rhs.get(x, y) == true) {
                rhs_trues.insert({x, y});
            }
        }
    }
    return lhs_trues == rhs_trues;
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

matrix_type& matrix_type::shift(int x, int y)
{
    if (x != 0) {
        // 水平方向にシフトする

        /*
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

        quadrant_type *top_front_ptr,
                      *top_back_ptr,
                      *bottom_front_ptr,
                      *bottom_back_ptr;

        if (x > 0) {
            top_front_ptr    = &quadrant_ur;
            top_back_ptr     = &quadrant_ul;
            bottom_front_ptr = &quadrant_br;
            bottom_back_ptr  = &quadrant_bl;
        } else {
            x = -x;
            top_front_ptr    = &quadrant_ul;
            top_back_ptr     = &quadrant_ur;
            bottom_front_ptr = &quadrant_bl;
            bottom_back_ptr  = &quadrant_br;
        }

        quadrant_type &top_front    = *top_front_ptr,
                      &top_back     = *top_back_ptr,
                      &bottom_front = *bottom_front_ptr,
                      &bottom_back  = *bottom_back_ptr;

        // 1. シフト方向側の象限をシフト方向にxビットシフトする
        // 2. シフト方向側の端の番人ビットを0にする
        for (auto && row : top_front) {
            row <<= x;
            row[row.size() - 1] = false;
        }
        for (auto && row : bottom_front) {
            row <<= x;
            row[row.size() - 1] = false;
        }

        // 3. シフト方向に対して反対側の象限の, シフト方向側のxビットを,
        //    シフト方向側の象限の, シフト方向に対して反対側のxビットにコピーする
        for (std::size_t i = 0; i < top_back.size() && i < top_front.size(); ++i) {
            auto part = top_back[i];
            part.crop(0, x).reverse().copy_to(top_front[i]);
        }
        for (std::size_t i = 0; i < bottom_back.size() && i < bottom_front.size(); ++i) {
            auto part = bottom_back[i];
            part.crop(0, x).reverse().copy_to(bottom_front[i]);
        }

        // 4. シフト方向に対して反対側の象限をシフト方向にxビットシフトする
        for (auto && row : top_back) {
            row >>= x;
        }
        for (auto && row : bottom_back) {
            row >>= x;
        }
    }

    if (y != 0) {
        // 垂直方向へシフトする

        /*
        * 下方向へのnビットシフトは次の手順で行われる:
        *  1. 下側の象限の, 上端から, 下端からn行目までを, 下端にコピーする
        *  2. 上側の象限の下側n行を下側の象限の上端にコピーする
        *  3. 上側の象限の下側n行を削除する
        * 上方向へのシフトは各手順の上下を反転させる.
        *
        * 実際には, 上側の象限の上端は配列の末尾側, 下端は配列の先頭側,
        *           下側の象限の上端は配列の先頭側, 下端は配列の末尾側である.
        * x軸をまたいだコピーは反転をともなう.
        */

        quadrant_type *front_left_ptr,
                      *front_right_ptr,
                      *back_left_ptr,
                      *back_right_ptr;

        if (y > 0) {
            front_left_ptr  = &quadrant_bl;
            front_right_ptr = &quadrant_br;
            back_left_ptr   = &quadrant_ul;
            back_right_ptr  = &quadrant_ur;
        } else {
            y = -y;
            front_left_ptr  = &quadrant_ul;
            front_right_ptr = &quadrant_ur;
            back_left_ptr   = &quadrant_bl;
            back_right_ptr  = &quadrant_br;
        }

        quadrant_type &front_left  = *front_left_ptr,
                      &front_right = *front_right_ptr,
                      &back_left   = *back_left_ptr,
                      &back_right  = *back_right_ptr;

        // 1. シフト方向側の象限の, シフト方向に対して反対側の端からy行目を, シフト方向側の端にコピーする
        std::copy_backward(front_left.begin(),
                           std::prev(front_left.end(), y + 1),
                           std::prev(front_left.end()));
        std::copy_backward(front_right.begin(),
                           std::prev(front_right.end(), y + 1),
                           std::prev(front_right.end()));

        // 2. シフト方向に対して反対側の象限の, シフト方向側のy行を,
        //    シフト方向側の象限の, シフト方向に対して反対側の端にコピーする
        std::reverse_copy(back_left.begin(),
                          std::next(back_left.begin(), y),
                          front_left.begin());
        std::reverse_copy(back_right.begin(),
                          std::next(back_right.begin(), y),
                          front_right.begin());

        // 3. シフト方向に対して反対側の象限の, シフト方向側のn行を削除する
        back_left.erase(back_left.begin(),
                          std::next(back_left.begin(), y));
        back_right.erase(back_right.begin(),
                          std::next(back_right.begin(), y));
    }

    return *this;
}

// vim: set ts=4 sw=4 et:
