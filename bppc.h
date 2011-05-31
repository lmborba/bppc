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


#ifndef BPPC_H
#define BPPC_H

#include <sstream>
#include <fstream>
#include "graph.h"
#include "bpp.h"
#include <iostream>

using namespace std;

/**
 * \brief Classe que define o Bin Packing Problem with Conflicts
 *
 */
class BPPC
{

 private:
  Graph * conflicts; ///< Grafo de conflitos.
  Graph * conflicts_big; ///< Grafo G' descrito no artigo.
  BPP * bin_packing; ///< O problema bin packing sem o grafo de conflitos.

 public:

  /**
   * \brief Construtor do problema BPPC.
   *
   * Dado um arquivo com dados de entrada padronizados, define um Bin Packing Problem with Conflicts.
   * \param[in] file_name Path para o arquivo que contém os dados do problema.
   */
  BPPC(string file_name);

  /**
   * \brief Destrutor.
   */
  virtual ~BPPC();

  /**
   * \brief Cálculo simples de limitante inferior baseado no BPP.
   *
   * Método de cálculo: \n
   * 1. Soma todos os pesos e divide pela capacidade das caixas. \n
   * 2. Retorna o menor inteiro com valor maior ou igual ao do resultado do passo 1.
   *
   * \return Limitante inferior baseado no Bin Packing Problem.
   */
  int lower_bound_0_bpp();

  int lower_bound_cp_imp();

  /**
   *
   */
  int lower_bound_cp();

  int upper_bound_ff(list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  int upper_bound_bf(list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  int upper_bound_wf(list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  vector<double> get_surrogate_bpp(double alpha);
  void get_surrogate_fits(int &upper_ff, int &upper_bf, int &upper_wf, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);

  void first_phase(int &lower, int &upper, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  void second_phase(int &lower, int &upper, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);

  void population_heuristic(int & k, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  //void tabu_search(int & k,vector<pair<int,list<int> > > & bins);

  double surrogate(list<int> & data, double avg_degree, double avg_weight, double alpha);

  bool tabu_search(int & k,vector<pair<int,list<int> > > & bins);
  bool population_heuristic(int k, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);
  void third_phase(int &lower, int &upper, list<vector<pair<int,list<int> > > > & pool, unordered_set<pair<int,list<int> > > & feasible_bins);

 private:

  /**
   * \internal
   * \brief Lê uma linha do arquivo, referente a um dos itens do Bin Packing Problem.
   *
   * A primeira linha do arquivo define o número de itens e a capacidade de cada caixa.
   * A seguir, cada um dos itens é descrito, com peso e os itens que não podem estar contidos na mesma caixa.
   * Este método privado lê cada uma destas linhas, armazenando os dados no grafo de conflitos e no BPP.
   * \param line Número da linha sendo lida.
   * \param file stream do arquivo sendo lido.
   */
  void read_line(int line, ifstream & file);

  /**
   * \internal
   * \brief Gera o grafo G' descrito no artigo, com base nos dados do BPP.
   *
   * Dado o grafo original, adiciona arestas entre os nodos cuja soma dos pesos
   * é maior que a capacidade.
   */
  void generate_conflicts_big();

};

#endif // BPPC_H
