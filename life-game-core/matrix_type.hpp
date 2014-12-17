#ifndef MATRIX_TYPE_HPP
#define MATRIX_TYPE_HPP

#include <functional>
#include <tuple>
#include <vector>

class matrix_type
{
    public:
        matrix_type();
        ~matrix_type() = default;

        bool get(int const& x, int const& y) const noexcept;
        void set(int const& x, int const& y, bool const& value);
        void clear() noexcept;

        std::size_t width() const noexcept;
        std::size_t height() const noexcept;

    private:
        using quadrant_type = std::vector<std::vector<bool>>;

        std::tuple<quadrant_type const&, std::size_t, std::size_t> convert_coordinate(int const& x, int const& y) const noexcept;

        quadrant_type quadrant_1;
        quadrant_type quadrant_2;
        quadrant_type quadrant_3;
        quadrant_type quadrant_4;
};

#endif // MATRIX_TYPE_HPP
// vim: set ts=4 sw=4 et:
