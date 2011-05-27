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

  //list<int> a = conflicts_big->johnsons_maximal_clique();
  //cout << a.size() << endl;
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

BPPC::~BPPC()
{
  delete conflicts_big;
  delete conflicts;
  delete bin_packing;
}
