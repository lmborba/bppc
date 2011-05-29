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

void Graph::unique()
{

};

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
  adjacency_lists[node_src].insert(Incidence(node_dst,cost));
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
    ss << "(" << adjacency_lists[i].size() << ") ";
    for (set<Incidence>::const_iterator it = adjacency_lists[i].begin(); it != adjacency_lists[i].end();it++) {
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

list<int> Graph::same_items(list<int> &rest, set<Incidence> &adjacency, list<int> & to_del)
{

  list<int>::iterator it_rest = rest.begin();
  set<Incidence>::iterator it_adj = adjacency.begin();
  list<int> res;

  while ((it_rest != rest.end()) && (it_adj != adjacency.end())) {
    //cout << *it_rest << ", " << it_adj->get_incident_node() << endl;
    if (*it_rest == it_adj->get_incident_node()) {
      //cout << *it_rest << ",";
      res.push_back(*it_rest);
      it_rest++;
      it_adj++;
    } else {
      if (*it_rest < it_adj->get_incident_node()) {
        to_del.push_back(*it_rest);
        it_rest++;
      } else {
        it_adj++;
      };
    };
  };

  //cout << endl;
  return res;

};

void Graph::calc_johnsons(list<int> & sub, vector<set<Incidence> > & sub_graph, list<int> & rest_list)
{

  while (rest_list.size()) {

    //cout << "Size: " << rest_list.size() << endl;

    int max = -1;
    int max_pos = -1;
    for (list<int>::iterator it = rest_list.begin(); it!=rest_list.end();it++) {
      int i = *it;
      if (((int) sub_graph[i].size()) > max) {
        max = sub_graph[i].size();
        max_pos = i;
      };
    };

    sub.push_back(max_pos);
    //cout << "Pos: " << max_pos << endl;

    list<int> todel;
    rest_list = same_items(rest_list,sub_graph[max_pos],todel);

    for (list<int>::iterator it = todel.begin();it!= todel.end() ;it++) {
      while (sub_graph[*it].begin() != sub_graph[*it].end()) {
        set<Incidence>::iterator current = sub_graph[*it].begin();
        set<Incidence>::iterator to_del = sub_graph[current->get_incident_node()].find(Incidence(*it,1));
        if (to_del != sub_graph[current->get_incident_node()].end()) {
          sub_graph[current->get_incident_node()].erase(to_del);
        };
        sub_graph[*it].erase(current);
      };
    };

  };

};

list<int> Graph::johnsons_maximal_clique()
{
  list<int> sub;
  vector<set<Incidence> > sub_graph = adjacency_lists;
  list<int> rest_list;

  for (int i=0;i<sub_graph.size();i++) {
    rest_list.push_back(i);
  };

  calc_johnsons(sub,sub_graph,rest_list);

  return sub;

};

list<int> Graph::johnsons_maximal_clique(list<int> & clique)
{

  vector<set<Incidence> > sub_graph(adjacency_lists.size());

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

  for (list<int>::iterator it = rest_list.begin(); it != rest_list.end(); it++) {
    for (set<Incidence>::iterator it2 = adjacency_lists[*it].begin(); it2 != adjacency_lists[*it].end(); it2++) {
      if (rest[it2->get_incident_node()]) {
        sub_graph[*it].insert(Incidence(it2->get_incident_node(),1));
      };
    };
  };

  calc_johnsons(sub,sub_graph,rest_list);

  return sub;

};


bool Graph::has_edge(int i, int j) {

  return adjacency_lists[i].find(Incidence(j,1)) != adjacency_lists[i].end();

};
