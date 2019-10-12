#include <gtest/gtest.h>

#include "Matrix.hpp"

TEST(MatrixTests, SimpleTest)
{
    Matrix<double> matrix{{1, 2, 4}, {3, 7, 0}};

    ASSERT_EQ(matrix.countOfRows(), 2);
    ASSERT_EQ(matrix.countOfColumns(), 3);
    ASSERT_EQ(matrix.isEmpty(), false);
    ASSERT_EQ(matrix.isSquare(), false);

    EXPECT_DOUBLE_EQ(matrix[0][0], 1);
    EXPECT_DOUBLE_EQ(matrix[0][1], 2);
    EXPECT_DOUBLE_EQ(matrix[0][2], 4);
    EXPECT_DOUBLE_EQ(matrix[1][0], 3);
    EXPECT_DOUBLE_EQ(matrix[1][1], 7);
    EXPECT_DOUBLE_EQ(matrix[1][2], 0);
}

TEST(MatrixTests, SumTest)
{
    Matrix<int> mat1 = {{1, 2, 1}, {7, -3, 8}, {2, 5, -1}}, mat2 = {{2, -6, 7}, {1, 3, 9}, {4, 7, 8}},
                mat3 = {{3, -4, 8}, {8, 0, 17}, {6, 12, 7}};

    ASSERT_EQ(mat1 + mat2, mat3);
}

TEST(MatrixTests, FunctionAtTest)
{
    Matrix<short> mat(4, 5);
    Matrix<char> empty_mat;

    ASSERT_THROW(mat.at(4, 5), std::out_of_range);
    ASSERT_THROW(mat.at(4, 3), std::out_of_range);
    ASSERT_THROW(mat.at(1, 5), std::out_of_range);
    ASSERT_THROW(mat.at(2, 8), std::out_of_range);
    ASSERT_THROW(mat.at(10, 3), std::out_of_range);
    ASSERT_THROW(empty_mat.at(0, 0), std::out_of_range);
    ASSERT_THROW(empty_mat.at(0, 2), std::out_of_range);
    ASSERT_THROW(empty_mat.at(23, 0), std::out_of_range);
    ASSERT_THROW(empty_mat.at(4, 6), std::out_of_range);

    ASSERT_NO_THROW(mat.at(3, 2));
    ASSERT_NO_THROW(mat.at(0, 0));
    ASSERT_NO_THROW(mat.at(3, 4));
}