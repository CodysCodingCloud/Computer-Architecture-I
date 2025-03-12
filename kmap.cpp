
#include "kmap.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <set>

KmapProblem::KmapProblem() {
  std::srand(std::time(0));
  _num_vars = (std::rand() % 2) + 2;
  std::cout << "_num_vars: " << _num_vars << std::endl;
  gen_problem();
};
KmapProblem::KmapProblem(int &num_vars) : _num_vars(num_vars) {
  gen_problem(0);
};
void KmapProblem::gen_problem(int custom_terms) {
  std::srand(std::time(0));
  _max_terms = std::pow(2, _num_vars);
  std::cout << "_max_terms: " << _max_terms << std::endl;
  //   int set[_max_terms];
  std::set<int> memo;
  int terms;
  if (custom_terms == 0 || custom_terms > _max_terms) {
    //   ran num terms should be atleast 2 and not maximum
    int rt = (std::rand() % (_max_terms - 2));
    std::cout << "rt: " << rt << std::endl;
    terms = 2 + rt;
  } else {
    terms = custom_terms;
  }
  std::cout << "terms: " << terms << std::endl;
  while (terms-- > 0) {
    std::vector<int> term(_num_vars);
    int temp_dupe = 0;
    for (int i = 0; i < _num_vars; i++) {
      term[i] = std::rand() % 2;
      temp_dupe += pow(10, i) * term[i];
    }
    if (memo.find(temp_dupe) == memo.end()) {
      memo.insert(temp_dupe);
      _problem.push_back(term);
      std::cout << "temp_dupe: " << temp_dupe << std::endl;
    }
  };
};
void KmapProblem::print(const std::vector<std::vector<int>> &standard_form) const {
  int size = standard_form.size();
  for (int i = 0; i < size; i++) {
    display_term(standard_form[i]);
    if (i != size - 1) {
      std::cout << " + ";
    }
  }
  std::cout << std::endl;
  //   std::cout << _num_vars << "ss" << std::endl;
}

void KmapProblem::display_term(const std::vector<int> &term) const {
  for (int i = 0; i < _num_vars; i++) {
    switch (term[i]) {
      case 0:
        std::cout << _var_set[i] << '\'';
        break;
      case 1:
        std::cout << _var_set[i];
        break;
      default:
        break;
    }
  }
};
void KmapProblem::display_kmap() const {
  std::cout << "practice problem: ";
  print(_problem);
  //   for (std::vector<int> n : _problem) {
  //     for (int m : n) {
  //       std::cout << m;
  //     }
  //     std::cout << " ";
  //   }
  //   std::cout << '\n';
}
bool KmapProblem::is_gray(std::vector<int> term1, std::vector<int> term2) const {
  int matches = 0;
  for (int i = 0; i < _num_vars; i++) {
    if (term1[i] == term2[i] && term1[i] != ABSORBED)
      matches++;
  }
  return matches == 1;
};
std::vector<int> KmapProblem::simplify_gray(const std::vector<int> term1, const std::vector<int> term2) const {
  std::vector<int> simp_term(3);
  for (int i = 0; i < _num_vars; i++) {
    if (term1[i] == term2[i] && term1[i] != ABSORBED) {
      simp_term[i] = term1[i];
    } else {
      simp_term[i] = ABSORBED;
    }
  }
  return simp_term;
};
void KmapProblem::simplify_problem(std::vector<std::vector<int>> &problem, std::set<int> memo, int i_, int j_) {
  std::vector<std::vector<int>> simp_terms;
  //   std::set<int> memo;
  //   did any in the outter loop get simplified
  bool simped = false;
  for (int i = i_; i < problem.size() - 1; i++) {
    bool grouped_prev = false;
    std::vector<int> term_simp;
    for (int j = j_; i < problem.size(); i++) {
      if (is_gray(problem[i], problem[j])) {
        term_simp = simplify_gray(problem[i], problem[j]);
        int temp_dupe = 0;
        for (int n : term_simp) {
          temp_dupe += pow(10, i) * n;
        }
        if (memo.find(temp_dupe) == memo.end()) {
          if (simped) {

            std::set<int> memo_copy = memo;
            // memo_copy.
            simplify_problem(simp_terms, memo_copy, i, j);
          }
          memo.insert(temp_dupe);
          std::cout << "temp_dupe: " << temp_dupe << std::endl;
          grouped_prev = true;
          simped = true;
        }
      }
    }
    if (grouped_prev) {
      simp_terms.push_back(term_simp);
    }
  }
  if (simped) {
    // may be further simplified
    simplify_problem(simp_terms, memo);
  } else {
    // no more simplification possible
    _ans.push_back(simp_terms);
  }
};
