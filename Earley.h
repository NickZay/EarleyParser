#pragma once

#include "Grammar.h"
#include <utility>
#include <vector>
#include <iostream>
#include <set>

struct Situation {
    Rule rule;
    size_t point;
    size_t i;

    Situation(Rule rule, size_t point, size_t i) :
            rule(std::move(rule)), point(point), i(i) {};

    bool operator<(const Situation& another) const;
};

class Early {
    std::string string_to_check;
    std::vector<std::set<Situation>> states;
    Grammar grammar;

    void Predict(size_t j);
    void Scan(size_t j, char x);
    void Complete(size_t j);

public:
    explicit Early(Grammar g) : grammar(std::move(g)) {}
    bool Check(const std::string& s);
};