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


#ifndef BPP_H
#define BPP_H

#include <boost/unordered_set.hpp>
using namespace boost;

#include <vector>
#include <list>
#include "graph.h"
#include <algorithm>
using namespace std;

#define INF 1000000

/**
 * \brief Classe que define um Bin Packing Problem.
 */
class BPP
{

 private:
  int capacity; ///< A capacidade das caixas.
  vector<int> items; ///< O vetor com o tamanho de cada um dos itens.

 public:
  /**
   * \brief Construtor.
   *
   * Inicializa o problema do bin packing problem.
   *
   * \param _capacity a capacidade das caixas do problema.
   */
  BPP(int _capacity);

  /**
   * \brief Construtor de cópia.
   *
   * Inicializa um clone de um BPP.
   *
   * \param other problema BPP a ser clonado.
   */
  BPP(const BPP& other);

  /**
   * \brief Destrutor
   */
  virtual ~BPP();

  /**
   * \brief Clona os dados de outro BPP.
   *
   * \param other problema BPP a ser clonado.
   */
  virtual BPP& operator=(const BPP& other);

  /**
   * \brief Getter do vetor de itens de um BPP.
   *
   * Obtém os tamanhos de cada um dos itens do problema em um vetor.
   *
   * \return Vetor com os tamanhos de cada um dos itens, na ordem em que foram setados.
   */
  vector<int> get_items();
  int get_items_size();

  /**
   * \brief Getter da capacidade das caixas do problema.
   *
   * \return Capacidade das caixas do problema.
   */
  int get_capacity();

  /**
   * \brief Insere um novo item no BPP.
   *
   * Insere um novo item no vetor de itens, com peso weight.
   *
   * \param weight o peso do item a ser inserido.
   */
  void add_item(int weight);

  /**
   * \brief Cálculo simples de limitante inferior do BPP.
   *
   * Método de cálculo: \n
   * 1. Soma todos os pesos e divide pela capacidade das caixas. \n
   * 2. Retorna o menor inteiro com valor maior ou igual ao do resultado do passo 1.
   *
   * \return Limitante inferior do Bin Packing Problem.
   */
  int lower_bound_0();

  double average_weight();

  int upper_bound_ffd(Graph & conflicts, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  int upper_bound_bf(Graph & conflicts, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  int upper_bound_wf(Graph & conflicts, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);

  int upper_bound_ffd(Graph & conflicts, vector<int> &sub_items, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  int upper_bound_bf(Graph & conflicts,vector<int> & sub_items, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  int upper_bound_wf(Graph & conflicts,vector<int> & sub_items, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  void order(list<int> & a);
  /**
   *
   */
  void add_size_conflicts(Graph & conflicts);

  int transportation(list<int> & items, Graph & conflicts);

  int transport_problem(vector<int> & a, vector<int> & b, vector<vector<int> > & c, vector<vector<int> > & x);

  int calc_transportation(int l, vector<bool> &not_used_items, vector<int> & residuals, list<int> & prev_items, Graph & conflicts, int min_index, int min);

  vector<int> get_surrogate_bpp(double alpha, Graph & conflicts);

  int item_weight(int i);

 private:
  /**
   * \internal
   * \brief Seta os dados do objeto iguais aos de arg1.
   *
   * \param arg1 BPP a ser copiado.
   */
  void set_parameters(const BPP & arg1);

};

#endif // BPP_H
