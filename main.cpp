#include "kmap.hpp"
#include <iostream>
using namespace std;
int main() {
    //   int choice;
    KmapProblem k;
    //   k.print();
    k.display_kmap();

    std::vector<std::vector<int>> p = vector{vector{0, 1, 0}, vector{0, 1, 1}, vector{1, 0, 0}};
    int i = 3;
    k.set_num_vars(i);
    k.set_problem(p);
    cout << "update here" << endl
         << endl;
    k.gen_ans();
    k.display_ans();
    //   while (true) {
    //     cout << "menu" << endl;
    //     cout << "1) Option 1" << endl;
    //     cout << "1) Option 1" << endl;
    //     cout << "1) Option 1" << endl;
    //     cout << "1) Option 1" << endl;
    //     cout << "Input Choice: " << endl;
    //     cin >> choice;
    //     switch (choice) {
    //       case 1:
    //         break;
    //       case 2:
    //         break;
    //       case 3:
    //         break;
    //       default:
    //         cout << "invalid choice, input a number" << endl;
    //     }
    //   }
    return 0;
}