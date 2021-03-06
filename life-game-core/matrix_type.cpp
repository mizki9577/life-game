#include "matrix_type.hpp"

matrix_type::matrix_type()
{
    x_offset = 0;
    y_offset = 0;
}

bool operator==(matrix_type const& lhs, matrix_type const& rhs)
{
    return lhs._matrix == rhs._matrix && lhs.x_offset == rhs.x_offset && lhs.y_offset == rhs.y_offset;
}

matrix_type operator&(matrix_type lhs, matrix_type rhs)
{
    matrix_type::arrange_size(lhs, rhs);

    auto lhs_row = lhs._matrix.begin();
    auto rhs_row = rhs._matrix.begin();
    while (lhs_row != lhs._matrix.end()) {
        *lhs_row &= *rhs_row;
        std::advance(rhs_row, 1);
        std::advance(lhs_row, 1);
    }

    return lhs;
}

matrix_type operator|(matrix_type lhs, matrix_type rhs)
{
    matrix_type::arrange_size(lhs, rhs);

    auto lhs_row = lhs._matrix.begin();
    auto rhs_row = rhs._matrix.begin();
    while (lhs_row != lhs._matrix.end()) {
        *lhs_row |= *rhs_row;
        std::advance(rhs_row, 1);
        std::advance(lhs_row, 1);
    }

    return lhs;
}

matrix_type operator^(matrix_type lhs, matrix_type rhs)
{
    matrix_type::arrange_size(lhs, rhs);

    auto lhs_row = lhs._matrix.begin();
    auto rhs_row = rhs._matrix.begin();
    while (lhs_row != lhs._matrix.end()) {
        *lhs_row ^= *rhs_row;
        std::advance(rhs_row, 1);
        std::advance(lhs_row, 1);
    }

    return lhs;
}


matrix_type operator~(matrix_type const& rhs)
{
    auto result = rhs;

    for (auto && row : result._matrix) {
        row.flip();
    }

    return result;
}

void matrix_type::arrange_size(matrix_type& lhs, matrix_type& rhs)
{
    if (lhs.top() > rhs.top()) {
        // 左辺の上端が右辺の上端より下にある.
        // 左辺を下シフトし, オフセットを右辺と等しくする.
        lhs.shift(0, lhs.top() - rhs.top());
        lhs.y_offset = rhs.y_offset;
    } else if (lhs.top() < rhs.top()) {
        // 右辺の上端が左辺の上端より下にある.
        // 右辺を下シフトし, オフセットを左辺と等しくする.
        rhs.shift(0, rhs.top() - lhs.top());
        rhs.y_offset = lhs.y_offset;
    }

    if (lhs.left() > rhs.left()) {
        // 左辺の左端が右辺の左端より右にある.
        // 左辺を右シフトし, オフセットを右辺と等しくする.
        lhs.shift(lhs.left() - rhs.left(), 0);
        lhs.x_offset = rhs.x_offset;
    } else if (lhs.left() < rhs.left()) {
        // 右辺の左端が左辺の左端より右にある.
        // 右辺を右シフトし, オフセットを左辺と等しくする.
        rhs.shift(rhs.left() - lhs.left(), 0);
        rhs.x_offset = lhs.x_offset;
    }

    if (lhs.bottom() > rhs.bottom()) {
        // 右辺の下端が左辺の下端より上にある.
        // 右辺を上シフトし, オフセットを左辺と等しくする.
        rhs.shift(0, rhs.bottom() - lhs.bottom());
        rhs.y_offset = lhs.y_offset;
    } else if (lhs.bottom() < rhs.bottom()) {
        // 左辺の下端が右辺の下端より上にある.
        // 左辺を上シフトし, オフセットを右辺と等しくする.
        lhs.shift(0, lhs.bottom() - rhs.bottom());
        lhs.y_offset = rhs.y_offset;
    }

    if (lhs.right() > rhs.right()) {
        // 右辺の右端が左辺の右端より左にある.
        // 右辺を左シフトし, オフセットを左辺と等しくする.
        rhs.shift(rhs.right() - lhs.right(), 0);
        rhs.x_offset = lhs.x_offset;
    } else if (lhs.right() < rhs.right()) {
        // 左辺の右端が右辺の右端より左にある.
        // 左辺を左シフトし, オフセットを右辺と等しくする.
        lhs.shift(lhs.right() - rhs.right(), 0);
        lhs.x_offset = rhs.x_offset;
    }
}

bool matrix_type::get(int const& x, int const& y) const
{
    std::size_t rx = x + x_offset,
                ry = y + y_offset;

    if (rx < width() && ry < height()) {
        return _matrix.at(ry).test(rx);
    } else {
        return false;
    }
}

void matrix_type::set(int const& x, int const& y, bool const& value)
{
    int rx = x + x_offset;
    int ry = y + y_offset;

    if (ry < 0) {
        // 上に拡張する
        std::fill_n(std::front_inserter(_matrix),
                    -ry,
                    boost::dynamic_bitset<>(width()));
        y_offset = -y;
        ry = 0;
    } else if (ry >= static_cast<int>(height())) {
        // 下に拡張する
        _matrix.resize(ry + 1, boost::dynamic_bitset<>(width()));
    }

    if (rx < 0) {
        // 左に拡張する
        for (auto && row : _matrix) {
            row.resize(row.size() + -rx);
            row <<= -rx;
        }
        x_offset = -x;
        rx = 0;
    } else if (rx >= static_cast<int>(width())) {
        // 右に拡張する
        for (auto && row : _matrix) {
            row.resize(rx + 1);
        }
    }

    if (rx < static_cast<int>(width()) &&
        ry < static_cast<int>(height()) &&
        rx >= 0 && ry >= 0) {
        _matrix.at(ry).set(rx, value);
    }
}

void matrix_type::clear()
{
    _matrix.clear();
}

std::size_t matrix_type::width() const
{
    return height() == 0 ? 0 : _matrix.front().size();
}

std::size_t matrix_type::height() const
{
    return _matrix.size();
}

int matrix_type::top() const
{
    return -y_offset;
}

int matrix_type::bottom() const
{
    return height() - y_offset - 1;
}

int matrix_type::left() const
{
    return -x_offset;
}

int matrix_type::right() const
{
    return width() - x_offset - 1;
}

matrix_type& matrix_type::shift(int x, int y)
{
    if (x < 0) {
        // 左にシフトする
        x = -x;
        for (auto && row : _matrix) {
            row.resize(row.size() + x);
        }
        x_offset += x;
    } else if (x > 0) {
        // 右にシフトする
        for (auto && row : _matrix) {
            row.resize(row.size() + x);
            row <<= x;
        }
    }

    if (y < 0) {
        // 上にシフトする
        y = -y;
        std::fill_n(std::back_inserter(_matrix),
                    y,
                    boost::dynamic_bitset<>(width()));
        y_offset += y;
    } else if (y > 0) {
        // 下にシフトする
        std::fill_n(std::front_inserter(_matrix),
                    y,
                    boost::dynamic_bitset<>(width()));
    }

    return *this;
}

matrix_type matrix_type::shifted(int x, int y)
{
    auto result = *this;
    result.shift(x, y);
    return result;
}

void matrix_type::optimize()
{
    // top
    auto const erase_end = std::prev(std::find_if(_matrix.begin(), _matrix.end(),
                                                  [](auto const & row) { return row.any(); }));
    auto const distance = std::distance(_matrix.begin(), erase_end);

    if (_matrix.front().none()) {
        _matrix.erase(_matrix.begin(), erase_end);
    }
    y_offset -= distance;

    // bottom
    if (_matrix.back().none()) {
        _matrix.erase(std::prev(std::find_if(_matrix.rbegin(), _matrix.rend(),
                                             [](auto const & row) { return row.any(); })
                                ).base(),
                      _matrix.end());
    }

    // left
    unsigned left_min_empty = width();
    for (auto const & row : _matrix) {
        unsigned x;
        for (x = 0; x < width(); ++x) {
            if (row.test(x)) {
                break;
            }
        }
        if (x < left_min_empty) {
            left_min_empty = x;
        }
    }
    --left_min_empty;
    for (auto && row : _matrix) {
        row >>= left_min_empty;
    }
    x_offset -= left_min_empty;

    // right
    unsigned right_max_alive = 0;
    for (auto const & row : _matrix) {
        unsigned x;
        for (x = width() - 1; x > 0; --x) {
            if (row.test(x)) {
                break;
            }
        }
        if (x > right_max_alive) {
            right_max_alive = x;
        }
    }
    for (auto && row : _matrix) {
        row.resize(right_max_alive + 2);
    }
}

// vim: set ts=4 sw=4 et:
