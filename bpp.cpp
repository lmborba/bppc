/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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


#include "bpp.h"

BPP::BPP(int _capacity)
{
  capacity = _capacity;
}

BPP::BPP(const BPP& other)
{
  set_parameters(other);
}

BPP::~BPP()
{

}

BPP& BPP::operator=(const BPP& other)
{
  set_parameters(other);
  return *this;
}

vector<int> BPP::get_items()
{
  return items;
};

int BPP::get_items_size()
{
  return items.size();
};

int BPP::get_capacity()
{
  return capacity;
};

void BPP::add_item(int weight)
{
  items.push_back(weight);
};

void BPP::set_parameters(const BPP& other) {
  capacity = other.capacity;
  items = other.items;
};

int BPP::lower_bound_0()
{
  int sum = 0;
  for (int i = 0; i<items.size(); i++) {
    sum += items[i];
  };
  int lower_bound = sum/capacity;
  lower_bound += sum%capacity ? 1 : 0;
  return lower_bound;
};

void BPP::add_size_conflicts(Graph & conflicts)
{
  for (int i=0;i<items.size();i++) {
    for (int j=0;j<items.size();j++) {
      if (i != j) {
        if (items[i] + items[j] > capacity) {
          conflicts.add_edge(i,j,1);
        };
      };
    };
  };
};

int BPP::transport_problem(vector<int> & a, vector<int> & b, vector<vector<int> > & c, vector<vector<int> > & x)
{

  long long int ko;

  long long int steps = 0;
  long long int m = a.size();
  long long int n = b.size();

  vector<long long int> u(m,0);
  vector<long long int> v(n,0);

  for (long long int j=0; j < n; j++) {
    long long int r = INF;
    for (long long int i=0; i < m; i++) {
      x[i][j] = 0;
      long long int sf = c[i][j];
      if (sf < r) {
        r = sf;
      };
    };
    v[j] = r;
  }

  bool lab1 = false;

  bool lab,lab2;
  long long int ra, sf,r;

  long long int i,j;

  do {

    vector<long long int> w(m,-1);
    vector<long long int> eps(m);
    for (long long int i=0; i < m; i++) {
      eps[i] = a[i];
    }
    vector<long long int> k(n,-1);
    vector<long long int> del(n,0);

    do {
      lab  = true;
      lab2 = true;
      i = 0;
      do {
        sf = eps[i];
        eps[i] = eps[i];
        if (sf > 0) {
          ra = u[i];
          j = 0;
          do {
            if ((del[j] == 0) && (v[j]-ra == c[i][j])) {
              k[j] = i;
              del[j] = sf;
              lab = false;
              if (b[j] > 0) {
                lab = true;
                lab2= false;
                sf = (del[j] < 0) ? -del[j] : del[j];
                r = b[j];
                if (r < sf) {
                  sf = r;
                };
                b[j] = r - sf;
                do {
                  i = k[j];
                  x[i][j] += sf;
                  j = w[i];
                  if (j != -1) {
                    x[i][j] -= sf;
                  };
                } while (j != -1);
                a[i] -= sf;

                // if b[j] <= 0 for all j, OPTIMAL
                j = 0;
                do {
                  lab1 = (b[j] <= 0);
                  j++;
                } while ((j < n) && (lab1));
                if (lab1) {
                  ko = 0;
                  for (i = 0; i < m; i++)
                    for (j = 0; j < n; j++)
                      ko += x[i][j] * c[i][j];
                }
              } // if ($b[$j])
            } // if (($del[$j] ...
            j++;
          } while ((j < n) && (lab2));
        } // if ($sf >5 0) ...
        i++;
      } while ((i < m) && (lab2));
      if (!lab) {
        lab = true;
        for (j = 0; j < n; j++) {
          sf = del[j];
          if (sf > 0) {
            for (i = 0; i < m; i++) {
              if (eps[i] == 0) {
                r = x[i][j];
                if (r > 0) {
                  w[i] = j;
                  if (r <= sf) {
                    eps[i] = r;
                  } else {
                    eps[i] = sf;
                  };
                  lab = false;
                } // if ($r > 0)
              } // if ($eps[$i] == 0)
            } // for ($i ... )
            del[j] = -sf;
          } // if ($sf > 0)
        } // for ($j ... )
      } // if (!$lab)
    } while (!lab);

    if (lab2) {
      r = INF;
      for (i = 0; i < m; i++) {
        if (eps[i] != 0) {
          ra = u[i];
          for (j = 0; j < n; j++) {
            if (del[j] == 0) {
              sf = c[i][j] + ra - v[j];
              if (r > sf)
                r = sf;
            } // if ($del[$j])
          } // for ($j ... )
        } // if ($eps[$i] != 0)
      }
      for (i = 0; i < m; i++)
        if (eps[i] == 0)
          u[i] += r;
      for (j = 0; j < n; j++)
        if (del[j] == 0)
          v[j] += r;
    }
  } while (!lab1);

  return ko;

};

int BPP::calc_transportation(int l, vector<bool> &not_used_items, vector<int> & residuals, list<int> & prev_items, Graph & conflicts, int min_index, int min)
{



};

int BPP::transportation(list<int> & prev_items, Graph & conflicts)
{
  vector<pair<int,int> > bins(prev_items.size()+1);
  vector<int> not_used_items(items.size(),true);

  int i =1;
  bins[0].first = INF;
  bins[0].second = -1;
  int maxi = -1;
  for (list<int>::iterator it = prev_items.begin();it != prev_items.end();it++) {
    not_used_items[*it] = false;
    bins[i].first = capacity - items[*it];
    if (bins[i].first > maxi) {
      maxi = bins[i].first;
    };
    bins[i].second = *it;
    i++;
  };

  int l = INF;
  for (int i = 0; i < not_used_items.size();i++) {
    if (not_used_items[i]) {
      if (items[i] <= maxi) {
        if (items[i] < l) {
          l = items[i];
        };
      };
    };
  };

  vector<int> Ill;
  vector<int> Il;
  vector<int> Illl;
  for (i=0;i<not_used_items.size();i++) {
    if (not_used_items[i]) {
      if (items[i] < l) {
        Ill.push_back(i);
      } else if ((items[i] >= l) && (items[i] <= maxi)) {
        Il.push_back(i);
      } else {
        Illl.push_back(i);
      };
    };
  };

  vector<pair<int,int> > Kl;

  for (int i=0;i<bins.size();i++) {
    if (bins[i].first >= l) {
      Kl.push_back(bins[i]);
    };
  };

  vector<vector<int> > c(Kl.size(),vector<int>(Il.size()));
  vector<vector<int> > x(Kl.size(),vector<int>(Il.size()));

  for (int i=0;i<Kl.size();i++) {
    for (int j=0;j<Il.size();j++) {
      if (i >= 1) {
        if (conflicts.has_edge(Kl[i].second,Il[j])) {
          c[i][j] = INF;
        } else {
          c[i][j] = 1;
        };
      } else {
        c[i][j] = items.size();
      };
    };
  };

  vector<int> a(Kl.size());
  for (int i=0;i<Kl.size();i++) {
    a[i] = Kl[i].first;
  };
  vector<int> b(Il.size());
  for (int i=0;i<Il.size();i++) {
    b[i] = items[Il[i]];
  };

  transport_problem(a, b, c, x);

  int cima = 0;

  for (int i=0;i<Il.size();i++) {
    cima += x[0][i];
  };

  for (int i=0;i<Illl.size();i++) {
    cima += items[Illl[i]];
  };

  int zl = 0;

  for (int i=0;i<Ill.size();i++) {
    zl += items[Ill[i]];
  };

  int subzl = 0;

  for (int i=0;i<bins.size();i++) {
    if (bins[i].second != -1) {
      subzl += bins[i].first;
    };
  };

  for (int i=0;i<Il.size();i++) {
    for (int j=1;j<Kl.size();j++) {
      subzl -= x[j][i];
    };
  };

  zl -= subzl;
  zl = max(0,zl);
  cima += zl;

  //  cout << zl << endl;

  //  cout << prev_items.size() << "," << ((cima/capacity) + ((cima % capacity) ? 1 : 0)) << endl;

  return prev_items.size() + ((cima/capacity) + ((cima % capacity) ? 1 : 0));

};

class Decrease {
  vector<int> * items;
public:
  Decrease(vector<int> & _items) {
    items = &_items;
  };
  ~Decrease(){};
  bool operator() (int i, int j) {
    return (*items)[i] > (*items)[j];
  };
};


int BPP::upper_bound_ffd(Graph & conflicts, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{
  vector<int> sub_items(items.size());
  for (int i=0;i<items.size();i++) {
    sub_items[i] = i;
  };
  sort(sub_items.begin(),sub_items.end(),Decrease(items));
  vector<pair<int,list<int> > > bins;

  for (int i=0;i<sub_items.size();i++) {
    //    cout << items[sub_items[i]] << endl;
    int j;
    for (j=0;j<bins.size();j++) {
      if (bins[j].first + items[sub_items[i]] <= capacity) {
        bool t =false;
        for (list<int>::iterator it = bins[j].second.begin(); it != bins[j].second.end(); it++) {
          if (conflicts.has_edge(*it,sub_items[i])) {
            t = true;
            break;
          };
        };
        if (!t) {
          break;
        };
      };
    };

    if (j >= bins.size()) {
      bins.push_back(pair<int,list<int> >(0,list<int>(0)));
    };

    bins[j].first += items[sub_items[i]];
    bins[j].second.push_back(sub_items[i]);

  };

  for (int i=0;i<bins.size();i++) {
    feasible_bins.insert(bins[i]);
  };
  pool.push_back(bins);

  return bins.size();

};

int BPP::upper_bound_bf(Graph & conflicts, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{
  vector<int> sub_items(items.size());
  for (int i=0;i<items.size();i++) {
    sub_items[i] = i;
  };
  sort(sub_items.begin(),sub_items.end(),Decrease(items));
  vector<pair<int,list<int> > > bins;

  for (int i=0;i<sub_items.size();i++) {
    int res = -1;
    int val = -1;
    for (int j=0;j<bins.size();j++) {
      if (bins[j].first + items[sub_items[i]] <= capacity) {
        bool not_conflict = true;
        for (list<int>::iterator it = bins[j].second.begin();it != bins[j].second.end(); it++) {
          if (conflicts.has_edge(*it,sub_items[i])) {
            not_conflict = false;
          };
        };
        if (not_conflict) {
          if (bins[j].first + items[sub_items[i]] > res) {
            res = bins[j].first + items[sub_items[i]];
            val = j;
          };
        };
      };
    };

    if (val == -1) {
      bins.push_back(pair<int,list<int> >(0,list<int>(0)));
      val = bins.size()-1;
    };

    bins[val].first += items[sub_items[i]];
    bins[val].second.push_back(sub_items[i]);

  };

  for (int i=0;i<bins.size();i++) {
    feasible_bins.insert(bins[i]);
  };
  pool.push_back(bins);

  return bins.size();

};

int BPP::upper_bound_wf(Graph & conflicts, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  vector<int> sub_items(items.size());
  for (int i=0;i<items.size();i++) {
    sub_items[i] = i;
  };
  sort(sub_items.begin(),sub_items.end(),Decrease(items));
  vector<pair<int,list<int> > > bins;

  for (int i=0;i<sub_items.size();i++) {
    int res = INF;
    int val = -1;
    for (int j=0;j<bins.size();j++) {
      if (bins[j].first + items[sub_items[i]] <= capacity) {
        bool not_conflict = true;
        for (list<int>::iterator it = bins[j].second.begin();it != bins[j].second.end(); it++) {
          if (conflicts.has_edge(*it,sub_items[i])) {
            not_conflict = false;
          };
        };
        if (not_conflict) {
          if (bins[j].first + items[sub_items[i]] < res) {
            res = bins[j].first + items[sub_items[i]];
            val = j;
          };
        };
      };
    };

    if (val == -1) {
      bins.push_back(pair<int,list<int> >(0,list<int>(0)));
      val = bins.size()-1;
    };

    bins[val].first += items[sub_items[i]];
    bins[val].second.push_back(sub_items[i]);

  };

  for (int i=0;i<bins.size();i++) {
    feasible_bins.insert(bins[i]);
  };
  pool.push_back(bins);

  return bins.size();

};

class DecreaseSWC {
  vector<double> * items;
public:
  DecreaseSWC(vector<double> & _items) {
    items = &_items;
  };
  ~DecreaseSWC(){};
  bool operator() (int i, int j) {
    return (*items)[i] > (*items)[j];
  };
};

class Supa {
  vector<int> items;
public:
  Supa(int size)
    : items(size)
  {
    for (int i=0;i<items.size();i++) {
      items[i] = rand()%items.size();
    };
  };
  ~Supa(){};
  bool operator() (int i, int j) {
    return (items)[i] > (items)[j];
  };
};

void BPP::order(list<int> & a) {
  a.sort(Supa(items.size()));
};

double BPP::average_weight()
{

  double soma = 0;

  for (int i=0;i<items.size();i++) {
    soma += items[i];
  };

  return (soma / ((double) items.size()));

};

vector<int> BPP::get_surrogate_bpp(double alpha, Graph & conflicts)
{

  double avg_degree = conflicts.average_degree();
  double soma = 0;

  for (int i=0;i<items.size();i++) {
    soma += items[i];
  };

  double avg_weight = soma / ((double) items.size());

  vector<double> toret(items.size());

  for (int i=0;i<items.size();i++) {
    toret[i] = ((alpha*((double) items[i]))/avg_weight) + (((((double) 1)-alpha)*((double) conflicts.degree(i)))/avg_degree);
  };

  vector<int> sub_items(toret.size());
  for (int i=0;i<toret.size();i++) {
    sub_items[i] = i;
  };
  sort(sub_items.begin(),sub_items.end(),DecreaseSWC(toret));

  return sub_items;

};

int BPP::upper_bound_ffd(Graph & conflicts,vector<int> & sub_items, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  vector<pair<int,list<int> > > bins;

  for (int i=0;i<sub_items.size();i++) {
    int j;
    for (j=0;j<bins.size();j++) {
      if (bins[j].first + items[sub_items[i]] <= capacity) {
        bool t =false;
        for (list<int>::iterator it = bins[j].second.begin(); it != bins[j].second.end(); it++) {
          if (conflicts.has_edge(*it,sub_items[i])) {
            t = true;
            break;
          };
        };
        if (!t) {
          break;
        };
      };
    };

    if (j >= bins.size()) {
      bins.push_back(pair<int,list<int> >(0,list<int>(0)));
    };


    bins[j].first += items[sub_items[i]];
    bins[j].second.push_back(sub_items[i]);

  };

  for (int i=0;i<bins.size();i++) {
    feasible_bins.insert(bins[i]);
  };
  pool.push_back(bins);

  return bins.size();

};

int BPP::upper_bound_bf(Graph & conflicts, vector<int> & sub_items, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  vector<pair<int,list<int> > > bins;

  for (int i=0;i<sub_items.size();i++) {
    int res = -1;
    int val = -1;
    for (int j=0;j<bins.size();j++) {
      if (bins[j].first + items[sub_items[i]] <= capacity) {
        bool not_conflict = true;
        for (list<int>::iterator it = bins[j].second.begin();it != bins[j].second.end(); it++) {
          if (conflicts.has_edge(*it,sub_items[i])) {
            not_conflict = false;
          };
        };
        if (not_conflict) {
          if (bins[j].first + items[sub_items[i]] > res) {
            res = bins[j].first + items[sub_items[i]];
            val = j;
          };
        };
      };
    };

    if (val == -1) {
      bins.push_back(pair<int,list<int> >(0,list<int>(0)));
      val = bins.size()-1;
    };

    bins[val].first += items[sub_items[i]];
    bins[val].second.push_back(sub_items[i]);

  };

  for (int i=0;i<bins.size();i++) {
    feasible_bins.insert(bins[i]);
  };
  pool.push_back(bins);

  return bins.size();

};

int BPP::upper_bound_wf(Graph & conflicts,vector<int> & sub_items, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins)
{

  vector<pair<int,list<int> > > bins;

  for (int i=0;i<sub_items.size();i++) {
    int res = INF;
    int val = -1;
    for (int j=0;j<bins.size();j++) {
      if (bins[j].first + items[sub_items[i]] <= capacity) {
        bool not_conflict = true;
        for (list<int>::iterator it = bins[j].second.begin();it != bins[j].second.end(); it++) {
          if (conflicts.has_edge(*it,sub_items[i])) {
            not_conflict = false;
          };
        };
        if (not_conflict) {
          if (bins[j].first + items[sub_items[i]] < res) {
            res = bins[j].first + items[sub_items[i]];
            val = j;
          };
        };
      };
    };

    if (val == -1) {
      bins.push_back(pair<int,list<int> >(0,list<int>(0)));
      val = bins.size()-1;
    };

    bins[val].first += items[sub_items[i]];
    bins[val].second.push_back(sub_items[i]);

  };

  for (int i=0;i<bins.size();i++) {
    feasible_bins.insert(bins[i]);
  };
  pool.push_back(bins);

  return bins.size();

};

int BPP::item_weight(int i)
{
  return items[i];
};
