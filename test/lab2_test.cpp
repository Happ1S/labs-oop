#include <gtest/gtest.h>
#include "Octal.h"

TEST(test_01, DefaultConstructor) {
    Octal octal;
    ASSERT_EQ(octal.getSize(), 0);
}

TEST(test_02, SizeConstructor) {
    Octal octal(5, 3);
    ASSERT_EQ(octal.getSize(), 5);
}

TEST(test_03, InitializerListConstructor) {
    Octal octal({1, 2, 3, 4});
    ASSERT_EQ(octal.getSize(), 4);
}

TEST(test_04, StringConstructor) {
    Octal octal("1234");
    ASSERT_EQ(octal.getSize(), 4);
}

TEST(test_05, CopyConstructor) {
    Octal octal1({1, 2, 3, 4});
    Octal octal2(octal1);
    ASSERT_EQ(octal2.getSize(), 4);
}

TEST(test_06, MoveConstructor) {
    Octal octal1({1, 2, 3, 4});
    Octal octal2(std::move(octal1));
    ASSERT_EQ(octal2.getSize(), 4);
}

TEST(test_07, Addition) {
    Octal octal1("123");
    Octal octal2("456");
    Octal result = octal1.add(octal2);
    Octal right_result("601");
    ASSERT_TRUE(result.equal(right_result));
}

TEST(test_08, Subtraction) {
    Octal octal1("456");
    Octal octal2("123");
    Octal result = octal1.subtract(octal2);
    Octal right_result("333");
    ASSERT_TRUE(result.equal(right_result));
}

TEST(test_09, GreaterThan) {
    Octal octal1("456");
    Octal octal2("123");
    ASSERT_TRUE(octal1.greater(octal2));
}

TEST(test_10, LessThan) {
    Octal octal1("123");
    Octal octal2("456");
    ASSERT_TRUE(octal1.less(octal2));
}

TEST(test_11, Equal) {
    Octal octal1("123");
    Octal octal2("123");
    ASSERT_TRUE(octal1.equal(octal2));
}