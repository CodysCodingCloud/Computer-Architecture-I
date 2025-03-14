
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
  int diffs = 0;
  for (int i = 0; i < _num_vars; i++) {
    if (term1[i] != term2[i] && term1[i] != ABSORBED && term2[i] != ABSORBED)
      diffs++;
  }
  std::cout << "is_gray: ";
  display_term(term1);
  std::cout << " == ";
  display_term(term2);
  std::cout << " diffs: " << diffs << std::endl;

  return diffs == 1;
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
  std::cout << "simplified term:  ";
  display_term(simp_term);
  std::cout << std::endl;
  return simp_term;
};
bool KmapProblem::simplify_problem(std::vector<std::vector<int>> &problem, std::vector<std::vector<int>> simp_terms, std::set<int> memo, int i_, int j_) {
  try {
    //   std::vector<std::vector<int>> simp_terms;
    //   std::set<int> memo;
    //   did any in the outter loop get simplified
    bool simped = false;
    std::cout << "problem size: " << problem.size() << std::endl;
    bool used_j = false;
    for (int i = i_; i < problem.size(); i++) {
      // int i = i_;
      // do {
      // check if it is the last element and if it was used to group or not
      if (i == (problem.size() - 1)) {
        if (memo.find(9) == memo.end()) {
          std::cout << "9 not found" << std::endl;
          simp_terms.push_back(problem[i]);
        } else
          std::cout << "9 found" << std::endl;
        break;
      }
      bool grouped_prev = false;
      //   int index_simp_prev = -1;
      std::vector<int> term_simp;
      for (int j = used_j ? i + 1 : j_; j < problem.size(); j++) {
        used_j = true;
        std::cout << "index: " << i << " , " << j << std::endl;
        if (is_gray(problem[i], problem[j])) {
          term_simp = simplify_gray(problem[i], problem[j]);
          int temp_dupe = 0;
          for (int k = 0; k < term_simp.size(); k++) {
            // std::cout << "temp_dupe3: " << term_simp[k] << std::endl;
            temp_dupe += (pow(10, k) * (term_simp[k] == 1 ? 1 : 0));
            // std::cout << "temp_dupe4: " << temp_dupe << std::endl;
          }
          if (memo.find(temp_dupe) == memo.end()) {
            // std::cout << "temp_dupe5: " << temp_dupe << std::endl;
            if (simped) {
              std::set<int> memo_copy = memo;
              std::vector<std::vector<int>> simp_terms_copy = simp_terms;
              simp_terms_copy.pop_back();
              // memo_copy.
              simplify_problem(problem, simp_terms_copy, memo_copy, i, j);
            }
            memo.insert(temp_dupe);
            grouped_prev = true;
            simped = true;
            // check if this is the last elem
            if (j == (problem.size() - 1)) {
              std::cout << "add 9" << std::endl;
              // add 9 to indicate that last elem was used to group
              memo.insert(9);
            }
            std::cout << "memo added: " << temp_dupe << std::endl;
          }
        }
      }
      if (grouped_prev) {
        std::cout << "term adding simped: ";
        display_term(term_simp);
        std::cout << std::endl;
        simp_terms.push_back(term_simp);
      } else {
        std::cout << "term adding unsimp: ";
        display_term(problem[i]);
        std::cout << std::endl;
        simp_terms.push_back(problem[i]);
      }
      std::cout << "term added: ";
      display_term(simp_terms[simp_terms.size() - 1]);
      std::cout << std::endl;
      //   i++;
    }
    // while (i < problem.size() - 1);
    std::cout << "simp so far: ";
    print(simp_terms);
    if (simped) {
      // may be further simplified
      simplify_problem(simp_terms);
    } else {
      // no more simplification possible
      _ans.push_back(simp_terms);
    }
    return true;
  } catch (const std::exception &e) {
    std::cerr << "Standard exception: " << e.what() << std::endl;
    return false;
  }
};
void KmapProblem::gen_ans() {
  simplify_problem(_problem);
};
void KmapProblem::display_ans() {
  gen_ans();
  std::cout << "generating [" << _ans.size() << "] answers for :";
  print(_problem);
  std::cout << std::endl;
  for (std::vector<std::vector<int>> ans : _ans) {
    print(ans);
  }
  std::cout << "all answers displayed" << std::endl;
};