/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file gadget.h
 * @brief Contiene la declaración de la clase Gadget
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef GADGET_H
#define GADGET_H

#include <vector>
#include "../graph/graph.h"
#include "../graph/vertexPair.h"
#include "vertex.h"

/**
 * @struct neighborInfo gadget.h
 * @brief Estructura que almacena varios VertexPair para poder recuperar su 
 *        información más adelante.
 */
struct neighborInfo {
  VertexPair vertexPair;
  VertexPair left_;
  VertexPair right_;
};

/**
 * @class Gadget gadget.h
 * @brief Clase auxiliar representa los gadgets necesarios para demostrar
 *    la transformación polinomial de VC a HC
 */
class Gadget {
 public:
  // Constructores y destructor
  Gadget(const VertexPair& vertexPair, const int mult = ZERO);

  // Getters y Setters

  /**
   * @brief Devuelve el grafo correspondiente al Gadget
   * @return graph
   */
  Graph getGraph() const { return graph_; }

  /**
   * @brief Devuelve el par de vertex que generaron el Gadget
   * @return vertexPair
   */
  VertexPair getOriginalPair() const { return vertexPair_; }

  VertexPair getLeftSide() const { return left_; }
  VertexPair getRightSide() const { return right_; }
  Vertex getLeftSideFirst() const { return left_.getFirst(); }
  Vertex getLeftSideLast() const { return left_.getSecond(); }
  Vertex getRightSideFirst() const { return right_.getFirst(); }
  Vertex getRightSideLast() const { return right_.getSecond(); }

  /**
   * @brief Devuelve el vertex izquierdo del Gadget
   * @return vertex
   */
  Vertex getOriginalLeft() const { return vertexPair_.getFirst(); }

  /**
   * @brief Devuelve el vertex derecho del Gadget
   * @return vertex
   */
  Vertex getOriginalRight() const { return vertexPair_.getSecond(); }

  // Métodos

  std::vector<Vertex> serialize() const;

  // Operadores
  bool operator<(const Gadget& gadget) const;

 private:
  Graph createStructure() const;
  VertexPair setLeftSide() const;
  VertexPair setRightSide() const;
  
  // Atributos
  Graph graph_{}; /**! El objeto grafo que contiene la información del Gadget */
  VertexPair vertexPair_{
      Vertex{},
      Vertex{}}; /** los pares de Vertex con los que se crearon el Gadget */
  VertexPair left_{Vertex{}, Vertex{}};
  VertexPair right_{Vertex{}, Vertex{}};
  int mult_{ZERO}; /** Multiplicador que indica que número de gadget corresponde*/
};

#endif