#ifndef MATRIX_TYPE_HPP
#define MATRIX_TYPE_HPP

#include <algorithm>
#include <functional>
#include <vector>
#include "my_dynamic_bitset.hpp"

class matrix_type
{
    public:
        using quadrant_type = std::vector<my_dynamic_bitset<>>;
        using reference_type = my_dynamic_bitset<>::reference;

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

        friend bool operator==(matrix_type const& lhs, matrix_type const& rhs);

        bool get(int const& x, int const& y);
        void set(int const& x, int const& y, bool const& value);
        void clear();

        matrix_type shift(int const& x, int const& y);

        std::size_t width() const;
        std::size_t height() const;
        int top() const;
        int bottom() const;
        int left() const;
        int right() const;

        quadrant_type quadrant_br;
        quadrant_type quadrant_bl;
        quadrant_type quadrant_ul;
        quadrant_type quadrant_ur;

    private:
        coordinate_type convert_coordinate(int const& x, int const& y);
};

#endif // MATRIX_TYPE_HPP
// vim: set ts=4 sw=4 et:
