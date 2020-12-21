#include "Earley.h"
#include <vector>
#include <string>
#include <gtest/gtest.h>



std::string GenerateBrackets(size_t test_size) {
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

std::string GenerateNotBrackets(const size_t test_size) {
    std::string test;
    for (int i = 0; i < test_size; ++i) {
        test += ((i * i * i % (test_size) % (i + 5) == 0) ? "(" : ")");
    }
    return test;
}

std::vector<std::string> GenerateBracketsGrammar() {
    std::vector<std::string> rules;
    rules.emplace_back("S->(S)S");
    rules.emplace_back("S->");
    return rules;
}


TEST(BRACKETS, SMALL_CORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenerateBrackets(10)));
}

TEST(BRACKETS, MEDIUM_CORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenerateBrackets(100)));
}

TEST(BRACKETS, BIG_CORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenerateBrackets(1000)));
}

TEST(BRACKETS, HUGE_CORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_TRUE(Early(grammar).Check(GenerateBrackets(10000)));
}

TEST(BRACKETS, SMALL_INCORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotBrackets(10)));
}

TEST(BRACKETS, MEDIUM_INCORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotBrackets(100)));
}

TEST(BRACKETS, BIG_INCORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotBrackets(1000)));
}

TEST(BRACKETS, HUGE_INCORRECT) {
    Grammar grammar(GenerateBracketsGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotBrackets(10000)));
}



std::string GeneratePalindrome(size_t test_size) {
    std::string test;
    test.resize(test_size);
    for (size_t i = 0; i < test_size / 2; ++i) {
        test[i] = test[test_size - i - 1] = 'a' + test_size * i * i % 26;
    }
    return test;
}

std::string GenerateNotPalindrome(size_t test_size) {
    std::string test;
    test.resize(test_size * 2 + 1);
    for (size_t i = 0; i < test.size(); ++i) {
        char letter = 'a' + (test.size() * i * i) % 26;
        test[i] = letter;
    }
    return test;
}

std::vector<std::string> GeneratePalindromeGrammar() {
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


TEST(PALINDROMES, SMALL_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GeneratePalindrome(10)));
}

TEST(PALINDROMES, MEDIUM_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GeneratePalindrome(100)));
}

TEST(PALINDROMES, BIG_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GeneratePalindrome(1000)));
}

TEST(PALINDROMES, HUGE_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_TRUE(Early(grammar).Check(GeneratePalindrome(3000)));
}

TEST(PALINDROMES, SMALL_NOT_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotPalindrome(10)));
}

TEST(PALINDROMES, MEDIUM_NOT_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotPalindrome(100)));
}

TEST(PALINDROMES, BIG_NOT_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotPalindrome(1000)));
}

TEST(PALINDROMES, HUGE_NOT_PALINDROME) {
    Grammar grammar(GeneratePalindromeGrammar());
    EXPECT_FALSE(Early(grammar).Check(GenerateNotPalindrome(3000)));
}



TEST(INCORRECT_GRAMMAR, LEFT_IS_NOT_TERMINAL) {
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