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


#include "graph.h"

Graph::Graph(int n_nodes)
: adjacency_lists(n_nodes)
{
}

void Graph::set_parameters(const Graph& other)
{
  adjacency_lists = other.adjacency_lists;
};

Graph::Graph(const Graph& other)
{
  set_parameters(other);
}

Graph::~Graph()
{
}

void Graph::add_edge(int node_src, int node_dst, int cost)
{
  adjacency_lists[node_src].push_back(Incidence(node_dst,cost));
};

void Graph::add_bidirectional_edge(int node_a, int node_b, int cost)
{
  add_edge(node_a,node_b,cost);
  add_edge(node_b,node_a,cost);
};

Graph& Graph::operator=(const Graph& other)
{
  set_parameters(other);
  return *this;
};
