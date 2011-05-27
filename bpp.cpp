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

  vector<int> Il;
  vector<int> Ill;
  vector<int> Illl;
  for (int i=0;i<items.size();i++) {
    if (not_used_items[i]) {
      if (items[i] < l) {
        Ill.push_back(items[i]);
      } else if ((items[i] >= l) && (items[i] <= (capacity-min))) {
        Il.push_back(items[i]);
      } else {
        Illl.push_back(items[i]);
      };
    };
  };

  vector<vector<int> > c(residuals.size(),vector<int>(Il.size()));
  vector<vector<int> > x(residuals.size(),vector<int>(Il.size()));
  for (int i=0;i<Il.size();i++) {
    c[0][i] = items.size();
  };
  for (int i=0;i<Il.size();i++) {
    list<int>::iterator it = prev_items.begin();
    for (int j=1;j<residuals.size();j++) {
      if (conflicts.has_edge(i,*it)) {
        c[j][i] = INF;
      } else {
        c[j][i] = 1;
      };
      it++;
    };
  };
  vector<int> b = Il;
  vector<int> a = residuals;
  int ko = transport_problem(a,b,c,x);

  int cima = 0;
  for (int i=0;i<x.size();i++) {
    cima += x[i][0];
  };

  for (int i=0;i<Illl.size();i++) {
    cima += Illl[i];
  };

  int zl = 0;
  for (int i=0;i<Ill.size();i++) {
    zl += Ill[i];
  };
  for (int i=0;i<x.size();i++) {
    for (int j=1;j<x[i].size();j++) {
      zl += x[i][j];
    };
  };
  for (int i=1;i<residuals.size();i++) {
    zl -= residuals[i];
  };

  zl = (zl > 0) ? zl : 0;

  cima += zl;

  int sec = (cima/capacity) + ((cima%capacity) ? 1 : 0);

  return sec + prev_items.size();

};

int BPP::transportation(list<int> & prev_items, Graph & conflicts)
{
  vector<int> residuals;
  residuals.push_back(INF);
  int min = items[*(prev_items.begin())];
  int min_index = 1;
  vector<bool> not_used_items(items.size(),true);
  for (list<int>::iterator it = prev_items.begin(); it != prev_items.end(); it++) {
    residuals.push_back(capacity-items[*it]);
    if (items[*it] < min) {
      min_index = residuals.size()-1;
      min = items[*it];
    };
    not_used_items[*it] = false;
  };

  int max = calc_transportation(0, not_used_items, residuals, prev_items, conflicts, min_index, min);

  /*
  for (int i=0;i<= (capacity - min);i++) {
    int val = calc_transportation(i, not_used_items, residuals, prev_items, conflicts, min_index, min);
    cout << val << endl;
    if (val > max) {
      max = val;
    };
    };*/

  return max;

};
