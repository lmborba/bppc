#include <iostream>
#include "bppc.h"

int main(int argc, char **argv) {
  srand(0);
  ifstream istanzes_file;
  istanzes_file.open(argv[1]);
  string file_name;
  double gap_first = 0;
  double gap_second = 0;
  int n = 0;
  while (istanzes_file >> file_name) {
    cout << file_name << endl;
    BPPC * problem = new BPPC(file_name);
    int upper,lower;
    unordered_set<pair<int,list<int> > > feasible_bins;
    list<vector<pair<int,list<int> > > > pool;
    time_t init = time(NULL);
    problem->first_phase(lower,upper,pool,feasible_bins);
    time_t final = time(NULL);
    cout << "First phase (" << final-init << "): " << endl;
    cout << "   ";
    if (lower == upper) {
      cout << "Solved";
    } else {
      cout << "Unsolv";
    };
    cout << endl;
    cout << "Upper bound: " << upper << endl;
    cout << "Lower bound: " << lower << endl;
    double percent = (((double) (100*(upper-lower)))/((double) lower));
    gap_first += percent;
    cout << "Percentage gap: " << percent << endl;

    init = time(NULL);
    problem->second_phase(lower,upper,pool,feasible_bins);
    final = time(NULL);
    cout << "Second phase (" << final-init << "): " << endl;
    cout << "   ";
    if (lower == upper) {
      cout << "Solved";
    } else {
      cout << "Unsolv";
    };
    cout << endl;
    cout << "Upper bound: " << upper << endl;
    cout << "Lower bound: " << lower << endl;
    percent = (((double) (100*(upper-lower)))/((double) lower));
    gap_second += percent;
    cout << "Percentage gap: " << percent << endl;

    string feas = file_name+".fea";

    ofstream o_file;
    o_file.open(feas.c_str());

    o_file << feasible_bins.size() << endl;
    for (unordered_set<pair<int,list<int> > >::iterator it = feasible_bins.begin(); it != feasible_bins.end(); it++) {
      o_file << it->first << " " << it->second.size() << endl;
      for(list<int>::const_iterator it2 = it->second.begin(); it2 != it->second.end() ;it2++) {
        o_file << *it2 << " ";
      };
      o_file << endl;
    };

    o_file.close();

    n++;
    delete problem;
  };

  cout << "First Phase Gap: " << ((double) gap_first) / ((double) n) << endl;
  cout << "Second Phase Gap: " << ((double) gap_second) / ((double) n) << endl;
  return 0;
}
