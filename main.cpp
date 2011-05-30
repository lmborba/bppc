#include <iostream>
#include "bppc.h"

int main(int argc, char **argv) {
  ifstream istanzes_file;
  istanzes_file.open(argv[1]);
  string file_name;
  int bf = 0;
  int ff = 0;
  int wf = 0;
  int all = 0;
  int n = 0;
  while (istanzes_file >> file_name) {
    cout << file_name << endl;
    int res;
    istanzes_file >> res;
    BPPC * problem = new BPPC(file_name);
    int cp = problem->lower_bound_cp();
    int cp_imp = problem->lower_bound_cp_imp();
    int lower = max(cp,cp_imp);
    int upper_ff = problem->upper_bound_ff();
    int upper_bf = problem->upper_bound_bf();
    int upper_wf = problem->upper_bound_wf();
    int upper = min(upper_ff,upper_bf);
    upper = min(upper,upper_wf);
    cout << upper_ff - lower << endl;
    cout << upper_bf - lower << endl;
    cout << upper_wf - lower << endl;
    cout << upper - lower << endl;
    bf += upper_bf - lower;
    ff += upper_ff - lower;
    wf += upper_wf - lower;
    all += upper - lower;
    n++;
    delete problem;
  };

  cout << "Upper Bound FF: " << ((double) ff) / ((double) n) << endl;
  cout << "Upper Bound BF: " << ((double) bf) / ((double) n) << endl;
  cout << "Upper Bound WF: " << ((double) wf) / ((double) n) << endl;
  cout << "Better Upper Bound: " << all << endl;
  return 0;
}
