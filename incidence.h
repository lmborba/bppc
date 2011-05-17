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


#ifndef INCIDENCE_H
#define INCIDENCE_H

class Incidence
{

private:
  int incident_node;
  int cost;
  
public:
  Incidence(int _incident_node, int _cost);
  Incidence(const Incidence& other);
  virtual ~Incidence();
  virtual Incidence& operator=(const Incidence& other);
  int get_incident_node();
  int get_cost();
  void set_incident_node(int _incident_node);
  void set_cost(int _cost);
  
private:
  void set_parameters(const Incidence& other);
  
};

#endif // INCIDENCE_H
