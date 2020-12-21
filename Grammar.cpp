#include "Grammar.h"

const std::vector<Rule>& Grammar::GetRules() const {
    return rules;
}

void Grammar::CheckRuleFormat(const std::string& rule) {
    if (rule.find("->") != 1 || rule.size() < 3 || rule.find("->") == std::string::npos) {
        throw std::logic_error("Bad Rule");
    }
}

void Grammar::CheckLeftOperand(char left_operand) {
    if (!isalpha(left_operand) || !(isupper(left_operand))) {
        throw std::logic_error("Left operand is bad");
    }
}

Rule Grammar::ParseRule(const std::string& rule) {
    Rule new_rule;
    CheckRuleFormat(rule);
    CheckLeftOperand(rule[0]);

    new_rule.nonterminal = rule[0];
    new_rule.right_part = rule.substr(3, rule.size());

    for (const auto& symbol : new_rule.right_part) {
        if (isupper(symbol)) {
            non_terminals_.push_back(symbol);
        } else if (islower(symbol)) {
            alphabet_.push_back(symbol);
        }
    }
    return new_rule;
}

std::istream& operator>>(std::istream& in, Grammar& grammar) {
    int rules_number;
    in >> rules_number;

    grammar.rules.push_back({'$', std::string("S")});

    std::string rule;
    for (int i = 0; i < rules_number; ++i) {
        in >> rule;
        grammar.rules.push_back(grammar.ParseRule(rule));
    }
    return in;
}

bool Rule::operator<(const Rule &other) const {
    if (nonterminal < other.nonterminal) {
        return true;
    } else if (nonterminal > other.nonterminal) {
        return false;
    } else {
        return right_part < other.right_part;
    }
}

bool Rule::operator==(const Rule &other) const {
    return nonterminal == other.nonterminal && right_part == other.right_part;
}

Grammar::Grammar(const std::vector<std::string>& mrules) {
    rules.push_back({'$', "S"});
    for (const auto& rule : mrules) {
        rules.push_back(ParseRule(rule));
    }
}
