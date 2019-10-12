#include <gtest/gtest.h>
#include <cmath>

#include "Function.hpp"

TEST(FunctionTest, SumTest)
{
    Function func1([](double x) -> double { return x + 1; });
    Function func2([](double x) -> double { return x + 2; });
    Function func3(sin);

    auto func_res1 = func1 + func2;
    auto func_res2 = func3 + func1;

    EXPECT_DOUBLE_EQ(func_res1(1), 5.0);
    EXPECT_DOUBLE_EQ(func_res1(-2), -1.0);
    EXPECT_DOUBLE_EQ(func_res2(3), 4.0 + sin(3.0));
    EXPECT_DOUBLE_EQ(func_res2(0), 1.0);
}

TEST(FunctionTest, SubTest)
{
    Function func1(exp);
    Function func2([](double x) -> double { return x * x + 2 * x + 1; });
    Function func3(log);

    auto func_res1 = func1 - func2;
    auto func_res2 = func3 - func1;
    auto func_res3 = func2 - func_res1;

    EXPECT_DOUBLE_EQ(func_res1(0), 0.0);
    EXPECT_DOUBLE_EQ(func_res1(-2), exp(-2) - 1);
    EXPECT_DOUBLE_EQ(func_res2(3), log(3) - exp(3));
    EXPECT_DOUBLE_EQ(func_res3(2.8), 2 * 3.8 * 3.8 - exp(2.8));
}
