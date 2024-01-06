/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file vertex.h
 * @brief Contains the declaration of all the methods of the Vertex class
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>

#include "../constVariables/constVariables.h"

/**
 * @class Vertex
 * @brief La clase vertex se encarga de representar un vertice de un grafo.
 *    Posee todos los métodos necesarios para trabajar con un vertice
 * @todo Poner el nombre de la clase en CamelCase
 */
class Vertex {
 public:
  // Constructores y destructor
  /**
   * @brief Construye un nuevo objeto de la clase Vertex
   * @param index Indice con el cual identificar el objeto, por defecto es
   * infinito.
   */
  Vertex(const int index = INFINITE) { newIndex(index); }

  // Getters y Setters

  /**
   * @brief Devuelve la ID almacenada del objeto
   * @return int
   */
  int getIndex() const { return index_; }

  /**
   * @brief Permite asignarle una nueva ID al objeto
   * @param newIndex El nuevo valor de la ID del objeto
   * @throw runtime_error Si el indice es menor que Cero
   */
  void newIndex(const int index) {
    if (index < ZERO)
      throw std::runtime_error("The new index must be equal or greater than 0");
    index_ = index;
  }

  // Operadores
  /**
   * @brief Comprueba si el objeto actual es menor que el objeto other.
   * @details Esta comprobación se lleva a cabo comparando los valores de los ID
   * de cada objeto. \n Este metodo es necesario para poder introducir objetos
   * de la clase Vertex en un std::map
   * @param other o another o otherVertex Objeto de la clase Vertex con el que
   * comparar la ID
   * @return true Si el objeto actual es menor que el otro objeto
   * @return false Si el objeto actual es mayor o igual que el otro objeto
   */
  bool operator<(const Vertex &vertex) const {
    return index_ < vertex.getIndex();
  }

  /**
   * @brief Comprueba si el objeto actual es mayor que el objeto other.
   * @details Esta comprobación se lleva a cabo comparando los valores de los ID
   * de cada objeto
   * @param other o another o otherVertex Objeto de la clase Vertex con el que
   * comparar la ID
   * @return true Si el objeto actual es mayor que el otro objeto
   * @return false Si el objeto actual es menor o igual que el otro objeto
   */
  bool operator>(const Vertex &vertex) const {
    return index_ > vertex.getIndex();
  }

  /**
   * @brief Comprueba si el objeto actual es igual que el objeto other.
   * @details Esta comprobación se lleva a cabo comparando los valores de los ID
   * de cada objeto .
   * @param other o another o otherVertex Objeto de la clase Vertex con el que
   * comparar la ID
   * @return true Si el objeto actual es igual que el otro objeto
   * @return false Si el objeto actual es distinto que el otro objeto
   */
  bool operator==(const Vertex &vertex) const {
    return index_ == vertex.getIndex();
  }
  bool operator!=(const Vertex &vertex) const {
    return !(index_ == vertex.getIndex());
  }

  /**
   * @brief Crea una string con la información del vértice 
   * @return std::string 
   */
  std::string str() const { return std::to_string(index_); }

  friend std::ostream &operator<<(std::ostream &output, const Vertex &vertex_);

 private:
  int index_{INFINITE}; /*! ID del vertice para poder identificarlo en el grafo, 
                          por defecto es infinito */
};

#endif