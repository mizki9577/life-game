#ifndef MATRIX_TYPE_HPP
#define MATRIX_TYPE_HPP

#include <cassert>
#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <utility>
#include "my_dynamic_bitset.hpp"

class matrix_type
{

    public:
        matrix_type();
        ~matrix_type() = default;

        friend bool operator==(matrix_type const& lhs, matrix_type const& rhs);
        friend matrix_type operator&(matrix_type const& lhs, matrix_type const& rhs);
        friend matrix_type operator|(matrix_type const& lhs, matrix_type const& rhs);

        bool get(int const& x, int const& y) const;
        void set(int const& x, int const& y, bool const& value);
        void clear();

        matrix_type& shift(int x, int y);

        std::size_t width() const;
        std::size_t height() const;
        int top() const;
        int bottom() const;
        int left() const;
        int right() const;

    private:
        std::deque<my_dynamic_bitset<>> _matrix;
        std::size_t x_offset;
        std::size_t y_offset;

};

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<< (std::basic_ostream<CharT, Traits>& os, matrix_type const& matrix)
{
    os << std::endl << "   ";
    for (int x = matrix.left(); x <= matrix.right(); ++x) {
        os << std::setw(3) << x;
    }
    os << std::endl;
    for (int y = matrix.top(); y <= matrix.bottom(); ++y) {
        os << std::setw(3) << y;
        for (int x = matrix.left(); x <= matrix.right(); ++x) {
            os << std::setw(3) << matrix.get(x, y);
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}

template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<< (std::basic_ostream<CharT, Traits>& os, matrix_type const&& matrix)
{
    os << matrix;
    return os;
}

#endif // MATRIX_TYPE_HPP
// vim: set ts=4 sw=4 et:
