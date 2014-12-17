#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

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
    BOOST_CHECK_EQUAL(matrix.width(), 10);
    BOOST_CHECK_EQUAL(matrix.height(), 10);
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
    matrix_type.clear();
    BOOST_CHECK_EQUAL(matrix_type.width(), 0);
    BOOST_CHECK_EQUAL(matrix_type.height(), 0);
}

// vim: set ts=4 sw=4 et:
