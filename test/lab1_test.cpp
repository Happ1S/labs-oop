#include <gtest/gtest.h>
#include "lib.h"

TEST(test_01, EmptyString) {
    std::string s = "";
    bool result = correct_parentheses_sequence(s);
    ASSERT_TRUE(result);
}

TEST(test_02, ValidSequence) {
    std::string s = "()";
    bool result = correct_parentheses_sequence(s);
    ASSERT_TRUE(result);
}

TEST(test_03, InvalidSequence) {
    std::string s = ")(";
    bool result = correct_parentheses_sequence(s);
    ASSERT_FALSE(result);
}

TEST(test_04, ValidNestedSequence) {
    std::string s = "(())";
    bool result = correct_parentheses_sequence(s);
    ASSERT_TRUE(result);
}

TEST(test_05, ValidMultipleNestedSequence) {
    std::string s = "((()))";
    bool result = correct_parentheses_sequence(s);
    ASSERT_TRUE(result);
}

TEST(test_06, InvalidSequenceExtraOpening) {
    std::string s = "(()";
    bool result = correct_parentheses_sequence(s);
    ASSERT_FALSE(result);
}

TEST(test_07, InvalidSequenceExtraClosing) {
    std::string s = "())";
    bool result = correct_parentheses_sequence(s);
    ASSERT_FALSE(result);
}

TEST(test_08, ValidLargeSequence) {
    std::string s = "((((((((((()))))))))))";
    bool result = correct_parentheses_sequence(s);
    ASSERT_TRUE(result);
}

TEST(test_09, InvalidLargeSequence) {
    std::string s = "((((((((((())))))))))";
    bool result = correct_parentheses_sequence(s);
    ASSERT_FALSE(result);
}