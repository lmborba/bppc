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

string Graph::to_string() const
{
  stringstream ss;
  for (int i=0;i<adjacency_lists.size();i++) {
    ss << i  << " => ";
    for (list<Incidence>::const_iterator it = adjacency_lists[i].begin(); it != adjacency_lists[i].end();it++) {
      ss << it->get_incident_node() << " ";
    };
    ss << endl;
  };
  return ss.str();
};

ostream& operator<<(ostream& out, const Graph& gra)
{
  out << gra.to_string();
  return out;
};

int Graph::number_of_nodes()
{
  return adjacency_lists.size();
};

list<int> Graph::johnsons_maximal_clique()
{

  list<int> sub;
  int n_nodes = number_of_nodes();
  vector<bool> rest(n_nodes,true);
  list<int> rest_list;
  for (int i=0;i<n_nodes;i++) {
    rest_list.push_back(i);
  };

  while (rest_list.size()) {
    int cur = -1;
    int max = -1;
    for (list<int>::iterator nd = rest_list.begin(); nd != rest_list.end(); nd++) {
      int val = 0;
      for (list<Incidence>::iterator it = adjacency_lists[*nd].begin(); it != adjacency_lists[*nd].end(); it++) {
        if (rest[it->get_incident_node()]) {
          val++;
        };
      };
      if (val > max) {
        cur = *nd;
        max = val;
      };
    };
    sub.push_back(cur);
    rest_list = list<int>(0);
    vector<bool> new_rest(n_nodes,false);
    for (list<Incidence>::iterator it = adjacency_lists[cur].begin(); it != adjacency_lists[cur].end(); it++) {
      if (rest[it->get_incident_node()]) {
        new_rest[it->get_incident_node()] = true;
        rest_list.push_back(it->get_incident_node());
      };
    };
    rest = new_rest;

  };

  return sub;

};

list<int> Graph::johnsons_maximal_clique(list<int> & clique)
{

  list<int> sub = clique;
  int n_nodes = number_of_nodes();
  vector<bool> rest(n_nodes,true);
  list<int> rest_list;
  for (list<int>::iterator it = sub.begin(); it != sub.end(); it++) {
    rest[*it] = false;
  };
  for (int i=0;i<rest.size();i++) {
    if (rest[i]) {
      rest_list.push_back(i);
    };
  };

  for (list<int>::iterator it = clique.begin(); it != clique.end(); it++) {
    list<int> new_list;
    for (list<int>::iterator it2 =rest_list.begin();it2 != rest_list.end(); it2++) {
      if (has_edge(*it,*it2)) {
        new_list.push_back(*it2);
      };
    };
    rest_list = new_list;
  };

  rest.clear();
  rest.resize(n_nodes,false);
  for (list<int>::iterator it = rest_list.begin(); it != rest_list.end(); it++) {
    rest[*it] = true;
  };

  while (rest_list.size()) {
    int cur = -1;
    int max = -1;
    for (list<int>::iterator nd = rest_list.begin(); nd != rest_list.end(); nd++) {
      int val = 0;
      for (list<Incidence>::iterator it = adjacency_lists[*nd].begin(); it != adjacency_lists[*nd].end(); it++) {
        if (rest[it->get_incident_node()]) {
          val++;
        };
      };
      if (val > max) {
        cur = *nd;
        max = val;
      };
    };
    sub.push_back(cur);
    rest_list = list<int>(0);
    vector<bool> new_rest(n_nodes,false);
    for (list<Incidence>::iterator it = adjacency_lists[cur].begin(); it != adjacency_lists[cur].end(); it++) {
      if (rest[it->get_incident_node()]) {
        new_rest[it->get_incident_node()] = true;
        rest_list.push_back(it->get_incident_node());
      };
    };
    rest = new_rest;

  };

  return sub;

};


bool Graph::has_edge(int i, int j) {

  for (list<Incidence>::iterator it = adjacency_lists[i].begin(); it != adjacency_lists[i].end(); it++) {
    if (it->get_incident_node() == j) {
      return true;
    };
  };

  return false;

};
