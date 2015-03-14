#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include "life_game.hpp"

BOOST_AUTO_TEST_CASE(matrix_type_dynamic_allocate)
{
    matrix_type matrix;

    // 未確保領域を取得するだけだったら確保しない (false を返す)
    BOOST_CHECK_EQUAL(matrix.get(10, 10), false);
    BOOST_CHECK_EQUAL(matrix.width(), 0);
    BOOST_CHECK_EQUAL(matrix.height(), 0);

    // 未確保領域を true にセットしたときは確保する
    matrix.set(10, 10, true);
    BOOST_CHECK_EQUAL(matrix.width(), 11);
    BOOST_CHECK_EQUAL(matrix.height(), 11);
}

BOOST_AUTO_TEST_CASE(matrix_type_negative_coordinate)
{
    matrix_type matrix;

    // 正負の座標値を扱える
    matrix.set( 10,  10, true);
    matrix.set(-10,  10, true);
    matrix.set(-10, -10, true);
    matrix.set( 10, -10, true);
    BOOST_CHECK_EQUAL(matrix.get( 10,  10), true);
    BOOST_CHECK_EQUAL(matrix.get(-10,  10), true);
    BOOST_CHECK_EQUAL(matrix.get(-10, -10), true);
    BOOST_CHECK_EQUAL(matrix.get( 10, -10), true);
}

BOOST_AUTO_TEST_CASE(matrix_type_clear)
{
    matrix_type matrix;

    for (int y = -50; y < 50; ++y) for (int x = -50; x < 50; ++x) {
        matrix.set(x, y, true);
    }
    matrix.clear();
    BOOST_CHECK_EQUAL(matrix.width(), 0);
    BOOST_CHECK_EQUAL(matrix.height(), 0);
}

BOOST_AUTO_TEST_CASE(matrix_type_coordinate_max_and_min)
{
    matrix_type matrix;

    matrix.set(-10, 5, true);
    matrix.set(10, -5, true);
    BOOST_CHECK_EQUAL(matrix.top(), -5);
    BOOST_CHECK_EQUAL(matrix.right(), 10);
    BOOST_CHECK_EQUAL(matrix.bottom(), 5);
    BOOST_CHECK_EQUAL(matrix.left(), -10);
}

BOOST_AUTO_TEST_CASE(life_game_rpentomino)
{
    life_game game;
    game.set(0, 1, true);
    game.set(1, 0, true);
    game.set(1, 1, true);
    game.set(1, 2, true);
    game.set(2, 0, true);
    game.next();
    BOOST_CHECK_EQUAL(game.get(0, 0),  true);
    BOOST_CHECK_EQUAL(game.get(0, 1),  true);
    BOOST_CHECK_EQUAL(game.get(0, 2),  true);
    BOOST_CHECK_EQUAL(game.get(1, 0),  true);
    BOOST_CHECK_EQUAL(game.get(1, 1), false);
    BOOST_CHECK_EQUAL(game.get(1, 2),  true);
    BOOST_CHECK_EQUAL(game.get(2, 0),  true);
    BOOST_CHECK_EQUAL(game.get(2, 1), false);
    BOOST_CHECK_EQUAL(game.get(2, 2), false);
    game.next();
    BOOST_CHECK_EQUAL(game.get(-1, -1), false);
    BOOST_CHECK_EQUAL(game.get(-1,  0), false);
    BOOST_CHECK_EQUAL(game.get(-1,  1),  true);
    BOOST_CHECK_EQUAL(game.get(-1,  2), false);
    BOOST_CHECK_EQUAL(game.get( 0, -1), false);
    BOOST_CHECK_EQUAL(game.get( 0,  0),  true);
    BOOST_CHECK_EQUAL(game.get( 0,  1), false);
    BOOST_CHECK_EQUAL(game.get( 0,  2),  true);
    BOOST_CHECK_EQUAL(game.get( 1, -1),  true);
    BOOST_CHECK_EQUAL(game.get( 1,  0),  true);
    BOOST_CHECK_EQUAL(game.get( 1,  1), false);
    BOOST_CHECK_EQUAL(game.get( 1,  2),  true);
    BOOST_CHECK_EQUAL(game.get( 2, -1), false);
    BOOST_CHECK_EQUAL(game.get( 2,  0), false);
    BOOST_CHECK_EQUAL(game.get( 2,  1),  true);
    BOOST_CHECK_EQUAL(game.get( 2,  2), false);
}

BOOST_AUTO_TEST_CASE(my_dynamic_bitset_crop)
{
    my_dynamic_bitset<> a(10, 0b1010110010);
    a.crop(2, 7);
    my_dynamic_bitset<> b(5, 0b01100);
    BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(my_dynamic_bitset_reverse)
{
    my_dynamic_bitset<> a(10, 0b1010110010);
    a.reverse();
    my_dynamic_bitset<> b(10, 0b0100110101);
    BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_CASE(my_dynamic_bitset_copy_to)
{
    my_dynamic_bitset<> source(10, 0b0001111100);
    my_dynamic_bitset<> destination(10, 0b0000000000);
    my_dynamic_bitset<> expected(10, 0b0111110000);
    source.copy_to(2, 7, destination, 4);
    BOOST_CHECK_EQUAL(destination, expected);
}

BOOST_AUTO_TEST_CASE(matrix_type_up_shift)
{
    matrix_type matrix, shifted;

    matrix.set(-2, -2,  true); matrix.set(-1, -2, false); matrix.set( 0, -2, false); matrix.set( 1, -2, false); matrix.set( 2, -2,  true);
    matrix.set(-2, -1, false); matrix.set(-1, -1,  true); matrix.set( 0, -1, false); matrix.set( 1, -1,  true); matrix.set( 2, -1, false);
    matrix.set(-2,  0, false); matrix.set(-1,  0, false); matrix.set( 0,  0,  true); matrix.set( 1,  0, false); matrix.set( 2,  0, false);
    matrix.set(-2,  1, false); matrix.set(-1,  1,  true); matrix.set( 0,  1, false); matrix.set( 1,  1,  true); matrix.set( 2,  1, false);
    matrix.set(-2,  2,  true); matrix.set(-1,  2, false); matrix.set( 0,  2, false); matrix.set( 1,  2, false); matrix.set( 2,  2,  true);

    shifted.set(-2, -2, false); shifted.set(-1, -2, false); shifted.set( 0, -2,  true); shifted.set( 1, -2, false); shifted.set( 2, -2, false);
    shifted.set(-2, -1, false); shifted.set(-1, -1,  true); shifted.set( 0, -1, false); shifted.set( 1, -1,  true); shifted.set( 2, -1, false);
    shifted.set(-2,  0,  true); shifted.set(-1,  0, false); shifted.set( 0,  0, false); shifted.set( 1,  0, false); shifted.set( 2,  0,  true);
    shifted.set(-2,  1, false); shifted.set(-1,  1, false); shifted.set( 0,  1, false); shifted.set( 1,  1, false); shifted.set( 2,  1, false);
    shifted.set(-2,  2, false); shifted.set(-1,  2, false); shifted.set( 0,  2, false); shifted.set( 1,  2, false); shifted.set( 2,  2, false);

    BOOST_CHECK_EQUAL(shifted, matrix.shift(0, -2));
}

BOOST_AUTO_TEST_CASE(matrix_type_right_shift)
{
    matrix_type matrix, shifted;

    matrix.set(-2, -2,  true); matrix.set(-1, -2, false); matrix.set( 0, -2, false); matrix.set( 1, -2, false); matrix.set( 2, -2,  true);
    matrix.set(-2, -1, false); matrix.set(-1, -1,  true); matrix.set( 0, -1, false); matrix.set( 1, -1,  true); matrix.set( 2, -1, false);
    matrix.set(-2,  0, false); matrix.set(-1,  0, false); matrix.set( 0,  0,  true); matrix.set( 1,  0, false); matrix.set( 2,  0, false);
    matrix.set(-2,  1, false); matrix.set(-1,  1,  true); matrix.set( 0,  1, false); matrix.set( 1,  1,  true); matrix.set( 2,  1, false);
    matrix.set(-2,  2,  true); matrix.set(-1,  2, false); matrix.set( 0,  2, false); matrix.set( 1,  2, false); matrix.set( 2,  2,  true);

    shifted.set(-2, -2, false); shifted.set(-1, -2, false); shifted.set( 0, -2,  true); shifted.set( 1, -2, false); shifted.set( 2, -2, false);
    shifted.set(-2, -1, false); shifted.set(-1, -1, false); shifted.set( 0, -1, false); shifted.set( 1, -1,  true); shifted.set( 2, -1, false);
    shifted.set(-2,  0, false); shifted.set(-1,  0, false); shifted.set( 0,  0, false); shifted.set( 1,  0, false); shifted.set( 2,  0,  true);
    shifted.set(-2,  1, false); shifted.set(-1,  1, false); shifted.set( 0,  1, false); shifted.set( 1,  1,  true); shifted.set( 2,  1, false);
    shifted.set(-2,  2, false); shifted.set(-1,  2, false); shifted.set( 0,  2,  true); shifted.set( 1,  2, false); shifted.set( 2,  2, false);

    BOOST_CHECK_EQUAL(shifted, matrix.shift(2, 0));
}

BOOST_AUTO_TEST_CASE(matrix_type_down_shift)
{
    matrix_type matrix, shifted;

    matrix.set(-2, -2,  true); matrix.set(-1, -2, false); matrix.set( 0, -2, false); matrix.set( 1, -2, false); matrix.set( 2, -2,  true);
    matrix.set(-2, -1, false); matrix.set(-1, -1,  true); matrix.set( 0, -1, false); matrix.set( 1, -1,  true); matrix.set( 2, -1, false);
    matrix.set(-2,  0, false); matrix.set(-1,  0, false); matrix.set( 0,  0,  true); matrix.set( 1,  0, false); matrix.set( 2,  0, false);
    matrix.set(-2,  1, false); matrix.set(-1,  1,  true); matrix.set( 0,  1, false); matrix.set( 1,  1,  true); matrix.set( 2,  1, false);
    matrix.set(-2,  2,  true); matrix.set(-1,  2, false); matrix.set( 0,  2, false); matrix.set( 1,  2, false); matrix.set( 2,  2,  true);

    shifted.set(-2, -2, false); shifted.set(-1, -2, false); shifted.set( 0, -2, false); shifted.set( 1, -2, false); shifted.set( 2, -2, false);
    shifted.set(-2, -1, false); shifted.set(-1, -1, false); shifted.set( 0, -1, false); shifted.set( 1, -1, false); shifted.set( 2, -1, false);
    shifted.set(-2,  0,  true); shifted.set(-1,  0, false); shifted.set( 0,  0, false); shifted.set( 1,  0, false); shifted.set( 2,  0,  true);
    shifted.set(-2,  1, false); shifted.set(-1,  1,  true); shifted.set( 0,  1, false); shifted.set( 1,  1,  true); shifted.set( 2,  1, false);
    shifted.set(-2,  2, false); shifted.set(-1,  2, false); shifted.set( 0,  2,  true); shifted.set( 1,  2, false); shifted.set( 2,  2, false);

    BOOST_CHECK_EQUAL(shifted, matrix.shift(0, 2));
}

BOOST_AUTO_TEST_CASE(matrix_type_left_shift)
{
    matrix_type matrix, shifted;

    matrix.set(-2, -2,  true); matrix.set(-1, -2, false); matrix.set( 0, -2, false); matrix.set( 1, -2, false); matrix.set( 2, -2,  true);
    matrix.set(-2, -1, false); matrix.set(-1, -1,  true); matrix.set( 0, -1, false); matrix.set( 1, -1,  true); matrix.set( 2, -1, false);
    matrix.set(-2,  0, false); matrix.set(-1,  0, false); matrix.set( 0,  0,  true); matrix.set( 1,  0, false); matrix.set( 2,  0, false);
    matrix.set(-2,  1, false); matrix.set(-1,  1,  true); matrix.set( 0,  1, false); matrix.set( 1,  1,  true); matrix.set( 2,  1, false);
    matrix.set(-2,  2,  true); matrix.set(-1,  2, false); matrix.set( 0,  2, false); matrix.set( 1,  2, false); matrix.set( 2,  2,  true);

    shifted.set(-2, -2, false); shifted.set(-1, -2, false); shifted.set( 0, -2,  true); shifted.set( 1, -2, false); shifted.set( 2, -2, false);
    shifted.set(-2, -1, false); shifted.set(-1, -1,  true); shifted.set( 0, -1, false); shifted.set( 1, -1, false); shifted.set( 2, -1, false);
    shifted.set(-2,  0,  true); shifted.set(-1,  0, false); shifted.set( 0,  0, false); shifted.set( 1,  0, false); shifted.set( 2,  0, false);
    shifted.set(-2,  1, false); shifted.set(-1,  1,  true); shifted.set( 0,  1, false); shifted.set( 1,  1, false); shifted.set( 2,  1, false);
    shifted.set(-2,  2, false); shifted.set(-1,  2, false); shifted.set( 0,  2,  true); shifted.set( 1,  2, false); shifted.set( 2,  2, false);

    BOOST_CHECK_EQUAL(shifted, matrix.shift(-2, 0));
}

BOOST_AUTO_TEST_CASE(matrix_type_operator_and)
{
    matrix_type lhs, rhs, expected;

    lhs.set(-2, -2,  true); lhs.set(-1, -2, false); lhs.set( 0, -2, false); lhs.set( 1, -2, false); lhs.set( 2, -2,  true);
    lhs.set(-2, -1, false); lhs.set(-1, -1,  true); lhs.set( 0, -1, false); lhs.set( 1, -1,  true); lhs.set( 2, -1, false);
    lhs.set(-2,  0, false); lhs.set(-1,  0, false); lhs.set( 0,  0,  true); lhs.set( 1,  0, false); lhs.set( 2,  0, false);
    lhs.set(-2,  1, false); lhs.set(-1,  1,  true); lhs.set( 0,  1, false); lhs.set( 1,  1,  true); lhs.set( 2,  1, false);
    lhs.set(-2,  2,  true); lhs.set(-1,  2, false); lhs.set( 0,  2, false); lhs.set( 1,  2, false); lhs.set( 2,  2,  true);

    rhs.set(-2, -2,  true); rhs.set(-1, -2, false); rhs.set( 0, -2,  true); rhs.set( 1, -2, false); rhs.set( 2, -2,  true);
    rhs.set(-2, -1,  true); rhs.set(-1, -1, false); rhs.set( 0, -1,  true); rhs.set( 1, -1, false); rhs.set( 2, -1,  true);
    rhs.set(-2,  0,  true); rhs.set(-1,  0, false); rhs.set( 0,  0,  true); rhs.set( 1,  0, false); rhs.set( 2,  0,  true);
    rhs.set(-2,  1,  true); rhs.set(-1,  1, false); rhs.set( 0,  1,  true); rhs.set( 1,  1, false); rhs.set( 2,  1,  true);
    rhs.set(-2,  2,  true); rhs.set(-1,  2, false); rhs.set( 0,  2,  true); rhs.set( 1,  2, false); rhs.set( 2,  2,  true);

    expected.set(-2, -2,  true); expected.set(-1, -2, false); expected.set( 0, -2, false); expected.set( 1, -2, false); expected.set( 2, -2,  true);
    expected.set(-2, -1, false); expected.set(-1, -1, false); expected.set( 0, -1, false); expected.set( 1, -1, false); expected.set( 2, -1, false);
    expected.set(-2,  0, false); expected.set(-1,  0, false); expected.set( 0,  0,  true); expected.set( 1,  0, false); expected.set( 2,  0, false);
    expected.set(-2,  1, false); expected.set(-1,  1, false); expected.set( 0,  1, false); expected.set( 1,  1, false); expected.set( 2,  1, false);
    expected.set(-2,  2,  true); expected.set(-1,  2, false); expected.set( 0,  2, false); expected.set( 1,  2, false); expected.set( 2,  2,  true);

    BOOST_CHECK_EQUAL(lhs & rhs, expected);
}

// vim: set ts=4 sw=4 et:
