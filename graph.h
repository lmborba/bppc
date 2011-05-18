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


#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include "incidence.h"

using namespace std;

class Graph
{

private:
  vector<list<Incidence> > adjacency_lists;

public:
  Graph(int n_nodes);
  Graph(const Graph& other);
  virtual ~Graph();
  virtual Graph& operator=(const Graph& other);
  void add_edge(int node_src, int node_dst, int cost);
  void add_bidirectional_edge(int node_a, int node_b, int cost);
  friend ostream& operator<<(ostream& out, const Graph& gra);
  string to_string() const;

private:
  void set_parameters(const Graph& other);
};

#endif // GRAPH_H
