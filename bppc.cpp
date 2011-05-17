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


#include "bppc.h"

void BPPC::read_line(int line, ifstream & file)
{
  int c;
  file >> c;
  file >> (*items)[line];
  string cur_line;
  getline(file,cur_line);
  stringstream ss(cur_line);
  int conflict;
  while (ss >> conflict) {
    conflict--;
    conflicts->add_bidirectional_edge(line,conflict,1);
  };
};

BPPC::BPPC(string file_name)
{
  ifstream bppc_file;
  bppc_file.open(file_name.c_str());
  int n_items;
  bppc_file >> n_items;
  bppc_file >> capacity;
  conflicts = new Graph(n_items);
  items = new vector<int>(n_items);
  for (int i=0;i<items->size();i++) {
    read_line(i,bppc_file);
  };
  for (int i=0;i<items->size();i++) {
    cout << (*items)[i] << endl;
  };
}

BPPC::~BPPC()
{
  delete conflicts;
  delete items;
}

