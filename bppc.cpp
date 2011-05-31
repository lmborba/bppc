/*
  Binary Packing Problem with Conflicts
  Copyright (C) 2011  Leonardo de Miranda Borba <lmborba@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bppc.h"

void BPPC::read_line(int line, ifstream & file)
{
  int c;
  file >> c;
  int weight;
  file >> weight;
  bin_packing->add_item(weight);
  string cur_line;
  getline(file,cur_line);
  stringstream ss(cur_line);
  int conflict;
  while (ss >> conflict) {
    conflict--;
    conflicts->add_bidirectional_edge(line,conflict,1);
  };
};

void BPPC::generate_conflicts_big()
{
  conflicts_big = new Graph(*conflicts);
  bin_packing->add_size_conflicts(*conflicts_big);
};

BPPC::BPPC(string file_name)
{
  ifstream bppc_file;
  bppc_file.open(file_name.c_str());
  int n_items;
  int capacity;
  bppc_file >> n_items;
  bppc_file >> capacity;
  conflicts = new Graph(n_items);
  bin_packing = new BPP(capacity);
  for (int i=0;i<n_items;i++) {
    read_line(i,bppc_file);
  };
  bppc_file.close();

  generate_conflicts_big();

  conflicts_big->unique();
  conflicts->unique();

};

int BPPC::lower_bound_0_bpp()
{
  bin_packing->lower_bound_0();
};

int BPPC::lower_bound_cp()
{
  list<int> clique = conflicts_big->johnsons_maximal_clique();

  int ret = bin_packing->transportation(clique,*conflicts_big);
  return ret;
};

int BPPC::lower_bound_cp_imp()
{

  list<int> clique = conflicts->johnsons_maximal_clique();
  list<int> subclique = conflicts_big->johnsons_maximal_clique(clique);

  int ret = bin_packing->transportation(subclique,*conflicts_big);
  return ret;

};

int BPPC::upper_bound_ff(list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  bin_packing->upper_bound_ffd(*conflicts,pool,feasible_bins);

};

int BPPC::upper_bound_bf(list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  bin_packing->upper_bound_bf(*conflicts,pool,feasible_bins);

};

int BPPC::upper_bound_wf(list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  bin_packing->upper_bound_wf(*conflicts,pool,feasible_bins);

};

vector<double> BPPC::get_surrogate_bpp(double alpha)
{

  return vector<double>(0);

};

void BPPC::get_surrogate_fits(int &upper_ff, int &upper_bf, int &upper_wf,list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  upper_ff = INF;
  upper_bf = INF;
  upper_wf = INF;
  for (int i=0;i<=10;i++) {
    vector<int> swc = bin_packing->get_surrogate_bpp(((double) i)/((double) 10), *conflicts_big);
    upper_ff = min(upper_ff,bin_packing->upper_bound_ffd(*conflicts_big,swc,pool,feasible_bins));
    upper_bf = min(upper_bf,bin_packing->upper_bound_bf(*conflicts_big,swc,pool,feasible_bins));
    upper_wf = min(upper_wf,bin_packing->upper_bound_wf(*conflicts_big,swc,pool,feasible_bins));
  };

};

bool sol_compare(vector<pair<int,list<int> > > & a, vector<pair<int,list<int> > > & b)
{
  return a.size() > b.size();
};

void BPPC::first_phase(int &lower, int &upper, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  int cp = lower_bound_cp();
  int cp_imp = lower_bound_cp_imp();

  lower = max(cp,cp_imp);

  int upper_ff = upper_bound_ff(pool,feasible_bins);
  int upper_bf = upper_bound_bf(pool,feasible_bins);
  int upper_wf = upper_bound_wf(pool,feasible_bins);

  int upper_ff_a;
  int upper_bf_a;
  int upper_wf_a;
  get_surrogate_fits(upper_ff_a,upper_bf_a,upper_wf_a,pool,feasible_bins);

  upper = min(upper_ff,upper_bf);
  upper = min(upper,upper_wf);
  upper = min(upper,upper_ff_a);
  upper = min(upper,upper_bf_a);
  upper = min(upper,upper_wf_a);

  pool.sort(sol_compare);

  while (pool.size() > 20) {
    pool.erase(pool.begin());
  };

};

double BPPC::surrogate(list<int> & data, double avg_degree, double avg_weight, double alpha)
{
  double sum = 0;
  for (list<int>::iterator it=data.begin();it != data.end();it++) {
    double val;
    if (avg_degree != 0.0) {
      val = ((alpha*((double) bin_packing->item_weight(*it)))/avg_weight) + (((((double) 1)-alpha)*((double) conflicts_big->degree(*it)))/avg_degree);
    } else {
      val = ((alpha*((double) bin_packing->item_weight(*it)))/avg_weight) + (((double) 1)-alpha);
    };
    val = max(val,0.000001);
    sum += val;
  };
  return sum;
};

bool BPPC::tabu_search(int & k,vector<pair<int,list<int> > > & bins)
{

  double avg_degree = conflicts_big->average_degree();
  double avg_weight = bin_packing->average_weight();
  double alpha = 1;

  int iter=0;

  vector<vector<int> > total_bins(bin_packing->get_items_size(),vector<int>(bins.size(),-41));
  while ((bins[k].second.size() != 0) && (iter < 500)) {

    int item = rand() % bins[k].second.size();

    list<int>::iterator it123;
    for (it123 = bins[k].second.begin(); it123 != bins[k].second.end();it123++) {
      if (item == 0) {
        break;
      };
      item--;
    };

    int current_item = *it123;

    bins[k].second.erase(it123);
    bins[k].first -= bin_packing->item_weight(current_item);

    double cur_sum = surrogate(bins[k].second,avg_degree,avg_weight,alpha);
    double min_sum = (double) INF;
    list<int> r_maintain;
    list<int> r_remove;
    int r_bin=-1;

    for (int i=0;i<k;i++) {



      list<int> maintain;
      int sum_maintain=0;
      list<int> remove;
      for (list<int>::iterator it = bins[i].second.begin(); it != bins[i].second.end(); it++) {
        if (conflicts_big->has_edge(*it,current_item)) {
          remove.push_back(*it);
        } else {
          maintain.push_back(*it);
          sum_maintain += bin_packing->item_weight(*it);
        };
      };

      bin_packing->order(maintain);

      while (sum_maintain + bin_packing->item_weight(current_item) > bin_packing->get_capacity()) {
        int cur = maintain.front();
        maintain.pop_front();
        remove.push_back(cur);
        sum_maintain -= bin_packing->item_weight(cur);
      };

      double new_sum = surrogate(remove,avg_degree,avg_weight,alpha);
      if (new_sum < min_sum) {
        if ((iter - total_bins[current_item][i] >= 40)) {
          min_sum = new_sum;
          r_maintain = maintain;
          r_remove = remove;
          r_bin = i;
        };
      };

    };

    total_bins[current_item][r_bin] = iter;
    bins[r_bin].second = r_maintain;
    bins[r_bin].second.push_back(current_item);

    bins[r_bin].first = 0;
    for (list<int>::iterator it = bins[r_bin].second.begin(); it != bins[r_bin].second.end(); it++) {
      bins[r_bin].first += bin_packing->item_weight(*it);
    };

    bins[k].second.insert(bins[k].second.end(),r_remove.begin(),r_remove.end());
    bins[k].first = 0;
    for (list<int>::iterator it = bins[k].second.begin(); it != bins[k].second.end(); it++) {
      bins[k].first += bin_packing->item_weight(*it);
    };

    iter++;

  };

  return bins[k].second.size() == 0;

};

bool BPPC::population_heuristic(int k, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  double avg_degree = conflicts_big->average_degree();
  double avg_weight = bin_packing->average_weight();
  double alpha = 1;

  time_t initial;
  initial = time(NULL);
  bool t = false;
  for (list<vector<pair<int,list<int> > > >::iterator it = pool.begin(); it != pool.end(); it++) {
    for (int i=it->size()-1;i>k;i--) {
      (*it)[k].second.insert((*it)[k].second.end(),(*it)[i].second.begin(),(*it)[i].second.end());
      (*it)[k].first += (*it)[i].first;
      it->pop_back();
    };
    if (tabu_search(k,(*it))) {
      for (int i=0;i<k;i++) {
        feasible_bins.insert((*it)[i]);
      };
      return true;
    };
    for (int i=0;i<k;i++) {
      feasible_bins.insert((*it)[i]);
    };
  };

  time_t final;
  final = time(NULL);
  while ((final-initial) <= ((double) 120)) {

    int a = rand() % pool.size();
    list<vector<pair<int,list<int> > > >::iterator it = pool.begin();
    while (a) {
      a--;
      it++;
    };

    vector<pair<int,list<int> > > first = *it;
    pool.erase(it);

    a = rand() % pool.size();
    it = pool.begin();
    while (a) {
      a--;
      it++;
    };
    vector<pair<int,list<int> > > second = *it;
    pool.erase(it);

    double x = surrogate(first[k].second,avg_degree,avg_weight,alpha);
    double y = surrogate(second[k].second,avg_degree,avg_weight,alpha);
    if (x < y) {
      pool.push_back(first);
    } else {
      pool.push_back(second);
    };

    vector<pair<int,list<int> > > result(first.size());

    for (int i=0;i<k;i++) {

      if (i%2) {
        double max = -1;
        int el = 0;
        for (int j=0;j<k;j++) {
          double b = surrogate(second[j].second,avg_degree,avg_weight,alpha);
          if (b > max) {
            max = b;
            el = j;
          };
        };
        result[i] = second[el];
      } else {
        double max = -1;
        int el = 0;
        for (int j=0;j<k;j++) {
          double b = surrogate(first[j].second,avg_degree,avg_weight,alpha);
          if (b > max) {
            max = b;
            el = j;
          };
        };
        result[i] = first[el];
      };

      set<int> arr;
      for (list<int>::iterator it = result[i].second.begin(); it != result[i].second.end(); it++) {
        arr.insert(*it);
      };

      for (int j=0;j<first.size();j++) {
        list<int> new_list;
        int sum = 0;
        for (list<int>::iterator it = first[j].second.begin(); it != first[j].second.end(); it++) {
          if (arr.find(*it) == arr.end()) {
            new_list.push_back(*it);
            sum += bin_packing->item_weight(*it);
          };
        };
        first[j].second = new_list;
        first[j].first = sum;
      };

      for (int j=0;j<second.size();j++) {
        list<int> new_list;
        int sum = 0;
        for (list<int>::iterator it = second[j].second.begin(); it != second[j].second.end(); it++) {
          if (arr.find(*it) == arr.end()) {
            new_list.push_back(*it);
            sum += bin_packing->item_weight(*it);
          };
        };
        second[j].second = new_list;
        second[j].first = sum;
      };
    };

    list<int> new_list;
    int sum = 0;
    for (int j=0;j<second.size();j++) {
      for (list<int>::iterator it = second[j].second.begin(); it != second[j].second.end(); it++) {
        new_list.push_back(*it);
        sum += bin_packing->item_weight(*it);
      };
    };

    result[k].first = sum;
    result[k].second = new_list;

    tabu_search(k,result);

    for (int i=0;i<k;i++) {
      feasible_bins.insert(result[i]);
    };
    pool.push_back(result);

    if (result[k].second.size() == 0) {
      return true;
    };

    final = time(NULL);
  };

  return false;

};

void BPPC::second_phase(int &lower, int &upper, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  while ((lower < upper) && (population_heuristic(upper-1,pool,feasible_bins))) {
    upper--;
  };

};

void BPPC::third_phase(int &lower, int &upper, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{



};

BPPC::~BPPC()
{
  delete conflicts_big;
  delete conflicts;
  delete bin_packing;
}
