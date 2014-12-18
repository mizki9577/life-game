#include "matrix_type.hpp"

matrix_type::matrix_type()
{
    quadrant_1 = { { false } };
    quadrant_2 = { { false } };
    quadrant_3 = { { false } };
    quadrant_4 = { { false } };
}

std::tuple<matrix_type::quadrant_type const&, std::size_t, std::size_t> matrix_type::convert_coordinate(int const& x, int const& y) const noexcept
{
    quadrant_type const* quadrant;
    std::size_t x2, y2;

    if (x >= 0) {
        x2 = x;
        if (y >= 0) {
            quadrant = &quadrant_1;
            y2 = y;
        } else {
            quadrant = &quadrant_4;
            y2 = -y - 1;
        }
    } else {
        x2 = -x - 1;
        if (y >= 0) {
            quadrant = &quadrant_2;
            y2 = y;
        } else {
            quadrant = &quadrant_3;
            y2 = -y - 1;
        }
    }

    return std::make_tuple(std::ref(*quadrant), x2, y2);
}

bool matrix_type::get(int const& x, int const& y) const noexcept
{
    auto const&& params = convert_coordinate(x, y);
    auto const& quadrant = std::get<0>(params);
    auto const& x2 = std::get<1>(params);
    auto const& y2 = std::get<2>(params);

    try {
        return quadrant.at(y2).at(x2);
    } catch (std::out_of_range e) {
        return false;
    }
}

void matrix_type::set(int const& x, int const& y, bool const& value)
{
    auto const&& params = convert_coordinate(x, y);
    auto& quadrant = const_cast<quadrant_type&>(std::get<0>(params));
    auto const& x2 = std::get<1>(params);
    auto const& y2 = std::get<2>(params);

    if (value == true) {
        if (y2 >= quadrant.size() - 1) {
            for (std::size_t i = 0, size = quadrant.size(); i < y2 - size + 2; ++i) {
                quadrant.emplace_back(quadrant.front().size(), false);
            }
        }
        if (x2 >= quadrant.front().size() - 1) {
            for (auto&& row : quadrant) {
                row.resize(x2 + 2, false);
            }
        }
        quadrant.at(y2).at(x2) = value;
    } else if (x2 < quadrant.front().size() - 1 && y2 < quadrant.size() - 1) {
        quadrant.at(y2).at(x2) = value;
    }
}

void matrix_type::clear() noexcept
{
    quadrant_1 = { { false } };
    quadrant_2 = { { false } };
    quadrant_3 = { { false } };
    quadrant_4 = { { false } };
}

std::size_t matrix_type::width() const noexcept
{
    return std::max(quadrant_1.front().size(), quadrant_4.front().size()) + std::max(quadrant_2.front().size(), quadrant_3.front().size()) - 2;
}

std::size_t matrix_type::height() const noexcept
{
    return std::max(quadrant_1.size(), quadrant_2.size()) + std::max(quadrant_3.size(), quadrant_4.size()) - 2;
}

int matrix_type::top() const noexcept
{
    return -std::max(quadrant_3.size(), quadrant_4.size());
}

int matrix_type::bottom() const noexcept
{
    return std::max(quadrant_1.size(), quadrant_2.size());
}

int matrix_type::left() const noexcept
{
    return -std::max(quadrant_2.front().size(), quadrant_3.front().size());
}

int matrix_type::right() const noexcept
{
    return std::max(quadrant_1.front().size(), quadrant_4.front().size());
}

// vim: set ts=4 sw=4 et:
