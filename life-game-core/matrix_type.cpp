#include "matrix_type.hpp"

matrix_type::matrix_type()
{
    x_offset = 0;
    y_offset = 0;
}

bool operator==(matrix_type const& lhs, matrix_type const& rhs)
{
    return lhs._matrix == rhs._matrix;
}

matrix_type operator&(matrix_type const& lhs, matrix_type const& rhs)
{
    assert(lhs.width() == rhs.width());
    assert(lhs.height() == rhs.height());

    auto result = lhs;

    auto rhs_row = rhs._matrix.begin();
    auto result_row = result._matrix.begin();
    while (result_row != result._matrix.end()) {
        *result_row &= *rhs_row;
        std::advance(rhs_row, 1);
        std::advance(result_row, 1);
    }

    return result;
}

matrix_type operator|(matrix_type const& lhs, matrix_type const& rhs)
{
    assert(lhs.width() == rhs.width());
    assert(lhs.height() == rhs.height());

    auto result = lhs;

    auto rhs_row = rhs._matrix.begin();
    auto result_row = result._matrix.begin();
    while (result_row != result._matrix.end()) {
        *result_row |= *rhs_row;
        std::advance(rhs_row, 1);
        std::advance(result_row, 1);
    }

    return result;
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
            row >>= x;
        }
    } else if (x > 0) {
        // 右にシフトする
        for (auto && row : _matrix) {
            row <<= x;
        }
    }

    if (y < 0) {
        // 上にシフトする
        y = -y;

        // コピーする方法
        std::copy(std::next(_matrix.begin(), y),
                  _matrix.end(),
                  _matrix.begin());
        std::fill(std::prev(_matrix.end(), y),
                  _matrix.end(),
                  my_dynamic_bitset<>(width()));

        // 追加削除する方法
        /*
        _matrix.erase(_matrix.begin(),
                      std::next(_matrix.begin(), y + 1));
        _matrix.emplace_back(width());
        */
    } else if (y > 0) {
        // 下にシフトする

        // コピーする方法
        std::copy_backward(_matrix.begin(),
                           std::prev(_matrix.end(), y),
                           _matrix.end());
        std::fill(_matrix.begin(),
                  std::next(_matrix.begin(), y),
                  my_dynamic_bitset<>(width()));

        /*
        // 追加削除する方法
        _matrix.erase(std::prev(_matrix.end(), y + 1),
                      _matrix.end());
        _matrix.emplace_front(width());
        */
    }

    return *this;
}

// vim: set ts=4 sw=4 et:
