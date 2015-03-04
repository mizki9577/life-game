#ifndef MATRIX_TYPE_HPP
#define MATRIX_TYPE_HPP

#include <functional>
#include <tuple>
#include <vector>
#include <array>
#include <boost/dynamic_bitset.hpp>

class matrix_type
{
    public:
        using quadrant_type = std::vector<boost::dynamic_bitset<>>;
        using reference_type = boost::dynamic_bitset<>::reference;

        class coordinate_type
        {
            public:
                coordinate_type() = default;
                ~coordinate_type() = default;

                quadrant_type& quadrant;
                std::size_t x;
                std::size_t y;
        };

        matrix_type();
        ~matrix_type() = default;

        bool get(int const& x, int const& y) noexcept;
        void set(int const& x, int const& y, bool const& value) noexcept;
        void clear() noexcept;

        std::size_t width() const noexcept;
        std::size_t height() const noexcept;
        int top() const noexcept;
        int bottom() const noexcept;
        int left() const noexcept;
        int right() const noexcept;

        quadrant_type quadrant_br;
        quadrant_type quadrant_bl;
        quadrant_type quadrant_ul;
        quadrant_type quadrant_ur;

    private:
        coordinate_type convert_coordinate(int const& x, int const& y) noexcept;
};

#endif // MATRIX_TYPE_HPP
// vim: set ts=4 sw=4 et:
