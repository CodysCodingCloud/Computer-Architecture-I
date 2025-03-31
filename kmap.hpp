// #ifndef KMAP_PROBLEM
// #define KMAP_PROBLEM
#pragma once

#include <set>
#include <string>
#include <vector>
int ABSORBED = 2;
class KmapProblem {
    private:
        std::vector<std::vector<int>> _problem;
        std::string _answer;
        int _num_vars;
        int _display_type;
        int _max_terms;
        char _var_set[3] = {'x', 'y', 'z'};
        std::vector<std::vector<std::vector<int>>> _ans;

    public:
        KmapProblem();
        KmapProblem(int& num_vars);
        bool set_num_vars(int& num_vars);
        int gen_memo_elem(std::vector<int> term1);
        void display_kmap() const;
        bool is_gray(std::vector<int> term1, std::vector<int> term2) const;
        std::vector<int> simplify_gray(const std::vector<int> term1, const std::vector<int> term2) const;
        std::vector<int> simplify_term(const std::vector<int> term1, const std::vector<int> term2);
        bool simplify_problem(std::vector<std::vector<int>>& problem, std::vector<std::vector<int>> simp_terms = {}, std::set<int> memo = {}, int i_ = 0, int j_ = 1);
        void gen_problem(int custom_terms = 0);
        bool set_problem(std::vector<std::vector<int>>& newproblem);
        void print(const std::vector<std::vector<int>>& standard_form) const;
        void display_term(const std::vector<int>& term) const;
        void gen_ans();
        void display_ans();
};
#include "kmap.cpp"
// #endif