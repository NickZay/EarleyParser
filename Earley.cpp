#include "Earley.h"

bool Situation::operator<(const Situation& another) const {
    if (rule == another.rule) {
        if (point == another.point) {
            return i < another.i;
        }
        return point < another.point;
    }
    return rule < another.rule;
}

bool Early::Check(const std::string& s) {
    string_to_check = s;

    states.clear();
    states.resize(string_to_check.size() + 1);
    states[0].insert(Situation(grammar.GetRules()[0], 0, 0));

    size_t previous_size;
    do {
        previous_size = states[0].size();
        Predict(0);
        Complete(0);
    } while (states[0].size() != previous_size);

    for (size_t i = 1; i <= string_to_check.size(); ++i) {
        Scan(i - 1, string_to_check[i - 1]);
        do {
            previous_size = states[i].size();
            Predict(i);
            Complete(i);
        } while (states[i].size() != previous_size);
    }
    Situation end(grammar.GetRules()[0], 1, 0);
    return states[string_to_check.size()].find(end) !=
           states[string_to_check.size()].end();
}

void Early::Predict(size_t j) {
    std::vector<Situation> new_situations;
    for (const auto& situation : states[j]) {
        for (const auto& rule : grammar.GetRules()) {
            if (rule.nonterminal == situation.rule.right_part[situation.point]) {
                new_situations.emplace_back(rule, 0, j);
            }
        }
    }
    for (const auto& situation : new_situations) {
        states[j].insert(situation);
    }
}

void Early::Scan(size_t j, char x) {
    for (const auto& situation : states[j]) {
        if (situation.rule.right_part[situation.point] == x) {
            states[j + 1].emplace(situation.rule, situation.point + 1, situation.i);
        }
    }
}

void Early::Complete(size_t j) {
    std::vector<Situation> new_situations;
    for (const auto& inner_situation : states[j]) {
        if (inner_situation.point != inner_situation.rule.right_part.size()) {
            continue;
        }
        for (const auto& situation : states[inner_situation.i]) {
            if (situation.rule.right_part[situation.point] == inner_situation.rule.nonterminal) {
                new_situations.emplace_back(situation.rule, situation.point + 1, situation.i);
            }
        }
    }
    for (const auto& situation : new_situations) {
        states[j].insert(situation);
    }
}