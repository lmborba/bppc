#include <iostream>
#include "bppc.h"

int main(int argc, char **argv) {
  ifstream istanzes_file;
  istanzes_file.open(argv[1]);
  string file_name;
  int correct = 0;
  int incorrect = 0;
  while (istanzes_file >> file_name) {
    cout << file_name << endl;
    int res;
    istanzes_file >> res;
    BPPC * problem = new BPPC(file_name);
    int cp = problem->lower_bound_cp();
    int cp_imp = problem->lower_bound_cp_imp();
    int real = max(cp,cp_imp);
    cout << res - cp << endl;
    cout << res - cp_imp << endl;
    cout << res - real << endl;
    if (res-real == 0) {
      correct++;
    } else {
      incorrect++;
    };
    delete problem;
  };

  cout << "Number of correct results: " << correct << endl;
  cout << "Number of incorrect results: " << incorrect << endl;
  return 0;
}
