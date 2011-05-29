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

/**
 * \brief Classe que define a incidência de uma aresta em um nodo de um grafo.
 */
class Incidence
{

private:
  int incident_node; ///< O nodo incidido pela aresta.
  int cost; ///< O custo da aresta.

public:
  /**
   * \brief Construtor padrão.
   *
   * Cria a incidência.
   *
   * \param _incident_node O nó incidido.
   * \param _cost O custo da aresta.
   */
  Incidence(int _incident_node, int _cost);

  /**
   * \brief Construtor de cópia.
   *
   * Copia os dados de other para o objeto atual.
   *
   * \param other o objeto sendo copiado.
   */
  Incidence(const Incidence& other);

  /**
   * \brief Destrutor.
   */
  virtual ~Incidence();

  /**
   * \brief Copia um Incidence.
   *
   * Copia os dados de other para o objeto atual.
   *
   * \param other o objeto sendo copiado.
   */
  virtual Incidence& operator=(const Incidence& other);

  /**
   * \brief Getter que retorno o nodo incidido.
   */
  int get_incident_node() const;

  /**
   * \brief Getter que retorna o custo da aresta.
   */
  int get_cost() const;

  /**
   * \brief Seta o nodo incidido.
   *
   * \param _incident_node o novo nodo incidido.
   */
  void set_incident_node(int _incident_node);

  /**
   * \brief Seta o custo da aresta
   *
   * \param _cost o novo custo.
   */
  void set_cost(int _cost);
  bool operator==(const Incidence& other) const;
  bool operator<(const Incidence& other) const;
  bool operator>(const Incidence& other) const;
  bool operator<=(const Incidence& other) const;
  bool operator>=(const Incidence& other) const;


private:

  /**
   * \brief Seta os dados do objeto atual de acordo com os parâmetros de other.
   *
   * \param other O Incidence a ser copiado.
   */
  void set_parameters(const Incidence& other);

};

#endif // INCIDENCE_H
