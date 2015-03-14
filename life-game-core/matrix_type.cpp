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
    if (lhs.x_offset > rhs.x_offset) {
        rhs.shift(lhs.x_offset - rhs.x_offset, 0);
        rhs.x_offset = lhs.x_offset;
    } else if (lhs.x_offset < rhs.x_offset) {
        lhs.shift(lhs.x_offset - rhs.x_offset, 0);
    }

    if (lhs.y_offset > rhs.y_offset) {
        rhs.shift(0, lhs.y_offset - rhs.y_offset);
        rhs.y_offset = lhs.y_offset;
    } else if (lhs.y_offset < rhs.y_offset) {
        lhs.shift(0, lhs.y_offset - rhs.y_offset);
    }

    if (lhs.height() > rhs.height()) {
        std::fill_n(std::back_inserter(rhs._matrix),
                    lhs.height() - rhs.height(),
                    my_dynamic_bitset<>(rhs.width()));
    } else if (lhs.height() < rhs.height()) {
        std::fill_n(std::back_inserter(lhs._matrix),
                    rhs.height() - lhs.height(),
                    my_dynamic_bitset<>(lhs.width()));
    }

    if (lhs.width() > rhs.width()) {
        for (auto && row : rhs._matrix) {
            row.resize(lhs.width());
        }
    } else if (lhs.width() < rhs.width()) {
        for (auto && row : lhs._matrix) {
            row.resize(rhs.width());
        }
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
                    my_dynamic_bitset<>(width()));
        y_offset = -y;
        ry = 0;
    } else if (ry >= static_cast<int>(height())) {
        // 下に拡張する
        _matrix.resize(ry + 1, my_dynamic_bitset<>(width()));
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
                    my_dynamic_bitset<>(width()));
        y_offset += y;
    } else if (y > 0) {
        // 下にシフトする
        std::fill_n(std::front_inserter(_matrix),
                    y,
                    my_dynamic_bitset<>(width()));
    }

    return *this;
}

matrix_type matrix_type::shifted(int x, int y)
{
    auto result = *this;
    result.shift(x, y);
    return result;
}

// vim: set ts=4 sw=4 et:
