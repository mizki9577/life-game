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

    // 未確保領域を false にセットしても確保しない
    matrix.set(10, 10, false);
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
    BOOST_CHECK_NO_THROW(matrix.set( 10,  10, true));
    BOOST_CHECK_NO_THROW(matrix.set(-10,  10, true));
    BOOST_CHECK_NO_THROW(matrix.set(-10, -10, true));
    BOOST_CHECK_NO_THROW(matrix.set( 10, -10, true));
    BOOST_CHECK_EQUAL(matrix.get( 10,  10), true);
    BOOST_CHECK_EQUAL(matrix.get(-10,  10), true);
    BOOST_CHECK_EQUAL(matrix.get(-10, -10), true);
    BOOST_CHECK_EQUAL(matrix.get( 10, -10), true);
    BOOST_CHECK_NO_THROW(matrix.set( 10,  10, false));
    BOOST_CHECK_NO_THROW(matrix.set(-10,  10, false));
    BOOST_CHECK_NO_THROW(matrix.set(-10, -10, false));
    BOOST_CHECK_NO_THROW(matrix.set( 10, -10, false));
    BOOST_CHECK_EQUAL(matrix.get( 10,  10), false);
    BOOST_CHECK_EQUAL(matrix.get(-10,  10), false);
    BOOST_CHECK_EQUAL(matrix.get(-10, -10), false);
    BOOST_CHECK_EQUAL(matrix.get( 10, -10), false);
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
    BOOST_CHECK_EQUAL(matrix.top(), -6);
    BOOST_CHECK_EQUAL(matrix.right(), 12);
    BOOST_CHECK_EQUAL(matrix.bottom(), 7);
    BOOST_CHECK_EQUAL(matrix.left(), -11);
}

BOOST_AUTO_TEST_CASE(life_game_rpentomino)
{
    life_game game;
    game.matrix.set(0, 1, true);
    game.matrix.set(1, 0, true);
    game.matrix.set(1, 1, true);
    game.matrix.set(1, 2, true);
    game.matrix.set(2, 0, true);
    game.next();
    BOOST_CHECK_EQUAL(game.matrix.get(0, 0), true);
    BOOST_CHECK_EQUAL(game.matrix.get(0, 1), true);
    BOOST_CHECK_EQUAL(game.matrix.get(0, 2), true);
    BOOST_CHECK_EQUAL(game.matrix.get(1, 0), true);
    BOOST_CHECK_EQUAL(game.matrix.get(1, 2), true);
    BOOST_CHECK_EQUAL(game.matrix.get(2, 0), true);
    game.next();
    BOOST_CHECK_EQUAL(game.matrix.get(-1, 1), true);
    BOOST_CHECK_EQUAL(game.matrix.get(0, 0), true);
    BOOST_CHECK_EQUAL(game.matrix.get(0, 2), true);
    BOOST_CHECK_EQUAL(game.matrix.get(1, -1), true);
    BOOST_CHECK_EQUAL(game.matrix.get(1, 0), true);
    BOOST_CHECK_EQUAL(game.matrix.get(1, 2), true);
    BOOST_CHECK_EQUAL(game.matrix.get(2, 1), true);
}

// vim: set ts=4 sw=4 et:
