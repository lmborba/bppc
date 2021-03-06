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


#include "incidence.h"

void Incidence::set_parameters(const Incidence& other)
{
  incident_node = other.incident_node;
  cost = other.cost;
}

Incidence::Incidence(int _incident_node, int _cost)
{
  incident_node = _incident_node;
  cost = _cost;
}

Incidence::Incidence(const Incidence& other)
{
  set_parameters(other);
}

Incidence::~Incidence()
{
}

bool Incidence::operator==(const Incidence& other) const
{
  return (other.get_incident_node() == get_incident_node());
};

bool Incidence::operator<(const Incidence& other) const
{
  return (other.get_incident_node() > get_incident_node());
};

bool Incidence::operator<=(const Incidence& other) const
{
  return (other.get_incident_node() >= get_incident_node());
};

bool Incidence::operator>=(const Incidence& other) const
{
  return (other.get_incident_node() <= get_incident_node());
};

bool Incidence::operator>(const Incidence& other) const
{
  return (other.get_incident_node() < get_incident_node());
};

Incidence& Incidence::operator=(const Incidence& other)
{
  set_parameters(other);
  return *this;
}

int Incidence::get_incident_node() const
{
  return incident_node;
};

int Incidence::get_cost() const
{
  return cost;
};

void Incidence::set_incident_node(int _incident_node)
{
  incident_node = _incident_node;
};

void Incidence::set_cost(int _cost)
{
  cost = _cost;
};
