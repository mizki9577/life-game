#include "matrix_type.hpp"

matrix_type::matrix_type()
{
    boost::dynamic_bitset<> unit(1, 0);
    quadrant_br = { unit };
    quadrant_bl = { unit };
    quadrant_ul = { unit };
    quadrant_ur = { unit };
}

std::tuple<matrix_type::quadrant_type const&, std::size_t, std::size_t> matrix_type::convert_coordinate(int const& x, int const& y) const noexcept
{
    auto quadrant = std::ref(quadrant_br);
    std::size_t x2, y2;

    if (x >= 0) {
        x2 = x;
        if (y >= 0) {
            quadrant = std::ref(quadrant_br);
            y2 = y;
        } else {
            quadrant = std::ref(quadrant_ur);
            y2 = -y - 1;
        }
    } else {
        x2 = -x - 1;
        if (y >= 0) {
            quadrant = std::ref(quadrant_bl);
            y2 = y;
        } else {
            quadrant = std::ref(quadrant_ul);
            y2 = -y - 1;
        }
    }

    return std::make_tuple(quadrant, x2, y2);
}

bool matrix_type::get(int const& x, int const& y) const noexcept
{
    auto const&& params = convert_coordinate(x, y);
    auto const& quadrant = std::get<0>(params);
    auto const& x2 = std::get<1>(params);
    auto const& y2 = std::get<2>(params);

    if (quadrant.front().size() > x2 && quadrant.size() > y2) {
        return quadrant.at(y2)[x2];
    } else {
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
            quadrant.resize(y2 + 2, boost::dynamic_bitset<>(quadrant.front().size()));
        }
        if (x2 >= quadrant.front().size() - 1) {
            for (auto&& row : quadrant) {
                row.resize(x2 + 2, false);
            }
        }
        quadrant.at(y2)[x2] = value;
    } else if (x2 < quadrant.front().size() - 1 && y2 < quadrant.size() - 1) {
        quadrant.at(y2)[x2] = value;
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

// vim: set ts=4 sw=4 et:
