#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

struct Rule {
    char nonterminal;
    std::string right_part;

    bool operator==(const Rule& other) const;
    bool operator<(const Rule& other) const;
};

class Grammar {
    Rule ParseRule(const std::string& rule);
    static void CheckRuleFormat(const std::string& rule);
    static void CheckLeftOperand(char left_operand);

    std::vector<char> non_terminals_;
    std::vector<char> alphabet_;
    std::vector<Rule> rules;

public:
    Grammar() = default;
    explicit Grammar(const std::vector<std::string>& rules);

    const std::vector<Rule>& GetRules() const;
    friend std::istream& operator>>(std::istream& in, Grammar& grammar);
};