
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
  std::set<int>
      memo;
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
void KmapProblem::print() const {
  std::cout << _num_vars << "ss" << std::endl;
}
void KmapProblem::display_kmap() const {
  for (std::vector<int> n : _problem) {
    for (int m : n) {
      std::cout << m;
    }
    std::cout << " ";
  }
  std::cout << '\n';
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
void KmapProblem::simplify_problem(std::vector<std::vector<int>> &problem, std::set<int> memo, int i, int j) {
  std::vector<std::vector<int>> simp_terms;
  std::set<int> memo;
  bool simped = false;
  for (int i; i < problem.size() - 1; i++) {
    bool grouped_prev = false;
    for (int j; i < problem.size(); i++) {
      if (is_gray(problem[i], problem[j])) {
        std::vector<int> term_simp = simplify_gray(problem[i], problem[j]);
        int temp_dupe = 0;
        for (int n : term_simp) {
          temp_dupe += pow(10, i) * n;
        }
        if (memo.find(temp_dupe) == memo.end()) {
          if (simped) {

            std::set<int> memo_copy = memo;
            memo_copy.
          }
          memo.insert(temp_dupe);
          simp_terms.push_back(term_simp);
          std::cout << "temp_dupe: " << temp_dupe << std::endl;
          grouped_prev = true;
          simped = true;
        }
      }
    }
  }
  int arr[5];
  if (simped) {
    simplify_problem(simp_terms, memo);
  } else {
    _ans.push_back(simp_terms);
  }
};

// void insert(node &new_node, int &pos) {
//   // get the the ptr to the first node
//   node cur_node = _head;
//   int curr_pos = 0;
//   // traverse to the the node of the specified position -1
//   while (curpos < pos - 1) {
//     curr_node = curr_node.next();
//   }
//   // set the prev node of the next node (at the specified pos) to the new_node
//   curr_node.next().set_prev(curr_node());
//   // set the next node of the new_node as the node at pos
//   new_node.set_next(curr_node.next());
//   // set the node at pos-1 to the new_node
//   curr_node.set_next(new_node);
//   // set the prev node of the new_node as the node at pos-1
//   new_node.set_prev(curr_node);
//   return true;
// }