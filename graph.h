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

/**
 * \brief Classe que define um grafo.
 */
class Graph
{

private:
  vector<list<Incidence> > adjacency_lists; ///< Vetor com uma lista para cada nodo, representando os itens que são adjacentes a estes nodos.

public:

  /**
   * \brief Construtor de um grafo.
   *
   * Inicializa um grafo com numero n_nodes de nodos.
   *
   * \param n_nodes Número de nodos no grafo.
   */
  Graph(int n_nodes);

  /**
   * \brief Construtor de cópia.
   *
   * Inicializa um grafo com os dados de outro.
   *
   * \param other O grafo a ser copiado.
   */
  Graph(const Graph& other);

  /**
   * \brief Destrutor
   */
  virtual ~Graph();

  /**
   * \brief Clona dados para a atual instância do graph.
   *
   * Clona os dados de other para o objeto atual.
   *
   * \param other Objeto a ser clonado.
   */
  virtual Graph& operator=(const Graph& other);

  /**
   * \brief Adiciona uma aresta ao grafo.
   *
   * Adiciona uma aresta direcionada ao grafo, partindo de node_src para node_dst.
   *
   * \param node_src Nodo de saída da aresta direcionada.
   * \param node_dst Nodo de chegada da aresta direcionada.
   * \param cost Custo da aresta.
   */
  void add_edge(int node_src, int node_dst, int cost);

  /**
   * \brief Adiciona uma aresta bidirecional ao grafo.
   *
   * Adiciona uma aresta de node_a para node_b e de node_b para node_a.
   * \note Na prática, usa duas vezes a função add_edge com as duas direções.
   *
   * \param node_a Um dos nodos da aresta.
   * \param node_b Um dos nodos da aresta.
   * \param cost Custo da aresta.
   */
  void add_bidirectional_edge(int node_a, int node_b, int cost);

  list<int> johnsons_maximal_clique(list<int> & clique);

  /**
   * \brief Exibe o grafo em um stream de saída.
   *
   * Transforma o grafo em um formato de string para a apresentação e o coloca em uma stream de saída.
   *
   * \param out A stream de saída.
   * \param gra O grafo a ser impresso.
   * \return A própria stream de saída.
   */
  friend ostream& operator<<(ostream& out, const Graph& gra);

  /**
   * \brief Transforma o grafo em uma string para exibição.
   *
   * \return a string de saída.
   */
  string to_string() const;

  /**
   * \brief Calcula o clique maximal do grafo aproximado.
   *
   * Utiliza-se a heuristica de Johnson (no artigo de 1974: Aproximation Algorithms for Combinatorial Problems)
   * para o cálculo do clique maximal do grafo de forma aproximada.
   *
   * \return Lista dos nodos pertencentes ao clique máximo aproximado.
   */
  list<int> johnsons_maximal_clique();

  /**
   * \brief Retorna o número de nodos no grafo.
   *
   * \return Número de nodos no grafo
   */
  int number_of_nodes();

  bool has_edge(int i, int j);

private:
  /**
   * Copia os parametros de other para o objeto atual.
   */
  void set_parameters(const Graph& other);
};

#endif // GRAPH_H
