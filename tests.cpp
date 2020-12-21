#include "Earley.h"
#include <vector>
#include <string>
#include <gtest/gtest.h>

std::string GenPalindrome(const size_t test_size) {
    std::string test;
    test.resize(test_size);
    for (size_t i = 0; i < test_size / 2; ++i) {
        char letter = 'a' + test_size * i * i % 26;
        test[i] = test[test_size - i - 1] = letter;
    }
    return test;
}

std::string GenNotPalindrome(const size_t test_size) {
    std::string test;
    test.resize(test_size * 2 + 1);
    for (size_t i = 0; i < test.size(); ++i) {
        char letter = 'a' + (test.size() * i * i) % 26;
        test[i] = letter;
    }
    return test;
}

std::vector<std::string> GenPalindromeGrammar() {
    std::vector<std::string> rules;
    char start_letter = 'a';
    for (int i = 0; i < 26; ++i) {
        std::string start_string(1, start_letter);
        rules.push_back("S->" + start_string + "S" + start_string);
        rules.push_back("S->" + start_string);
        ++start_letter;
    }
    rules.emplace_back("S->");
    return rules;
}

std::string GenBrackets(const size_t test_size) {
    std::string test;
    for (int i = 0; i < test_size / 2; ++i) {
        if ((i * i * i % test_size) % 3 == 0) {
            test += "()";
        } else if ((i * i * i % test_size) % 3 == 1) {
            test = "()" + test;
        } else {
            test = "(" + test + ")";
        }
    }
    return test;
}

std::string GenNotBrackets(const size_t test_size) {
    std::string test;
    for (int i = 0; i < test_size; ++i) {
        test += ((i * i * i % (test_size) % (i + 5) == 0) ? "(" : ")");
    }
    return test;
}

std::vector<std::string> GenBracketsGrammar() {
    std::vector<std::string> rules;
    rules.push_back("S->(S)S");
    rules.push_back("S->S(S)");
    rules.push_back("S->");
    return rules;
}


TEST(PALINDROME, IS_PALINDROME_SMALL) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenPalindrome(10)));
}

TEST(PALINDROME, IS_PALINDROME_MEDIUM) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenPalindrome(100)));
}

TEST(PALINDROME, IS_PALINDROME_BIG) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenPalindrome(1000)));
}

TEST(PALINDROME, IS_PALINDROME_HUGE) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenPalindrome(3000)));
}

TEST(PALINDROME, NOT_PALINDROME_SMALL) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotPalindrome(10)));
}

TEST(PALINDROME, NOT_PALINDROME_MEDIUM) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotPalindrome(100)));
}

TEST(PALINDROME, NOT_PALINDROME_BIG) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotPalindrome(1000)));
}

TEST(PALINDROME, NOT_PALINDROME_HUGE) {
    Grammar grammar(GenPalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotPalindrome(3000)));
}


TEST(BRACKETS, IS_CORRECT_SMALL) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenBrackets(10)));
}

TEST(BRACKETS, IS_CORRECT_MEDIUM) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenBrackets(100)));
}

TEST(BRACKETS, IS_CORRECT_BIG) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenBrackets(1000)));
}

TEST(BRACKETS, IS_CORRECT_HUGE) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenBrackets(10000)));
}

TEST(BRACKETS, NOT_CORRECT_SMALL) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotBrackets(10)));
}

TEST(BRACKETS, NOT_CORRECT_MEDIUM) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotBrackets(100)));
}

TEST(BRACKETS, NOT_CORRECT_BIG) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotBrackets(1000)));
}

TEST(BRACKETS, NOT_CORRECT_HUGE) {
    Grammar grammar(GenBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenNotBrackets(10000)));
}


TEST(INCORRECT_GRAMMAR, LEFT_NOT_TERMINAL) {
    std::vector<std::string> rules;
    rules.emplace_back("a->A");
    Grammar grammar;
    EXPECT_ANY_THROW(grammar = Grammar(rules));
}

TEST(INCORRECT_GRAMMAR, RULE_BAD_FORMAT) {
    std::vector<std::string> rules;
    rules.emplace_back("A -> AAA");
    Grammar grammar;
    EXPECT_ANY_THROW(grammar = Grammar(rules));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}