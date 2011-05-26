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

list<int> & BPP::get_items()
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
  for (list<int>::iterator it = items.begin(); it != items.end(); it++) {
    sum += *it;
  };
  int lower_bound = sum/capacity;
  lower_bound += sum%capacity ? 1 : 0;
  return lower_bound;
};
