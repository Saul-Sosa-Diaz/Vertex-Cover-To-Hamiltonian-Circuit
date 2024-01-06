/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file vertexPair.h
 * @brief Contains the declaration of all the methods of the VertexPair class
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef VERTEXPAIR_H
#define VERTEXPAIR_H

#include <algorithm>
#include <ostream>

#include "vertex.h"

class VertexPair final {
 public:
  // Constructores y destructor
  VertexPair() {}
  VertexPair(const Vertex& first, const Vertex& second)
      : first_(first), second_(second){};
  
  // Getters y Setters 
  Vertex getFirst() const { return first_; }
  Vertex getSecond() const { return second_; }

  // Operadores
  bool operator<(const VertexPair& aux) const;
  bool operator==(const VertexPair& aux) const;
  bool operator!=(const VertexPair& aux) const;
  friend std::ostream& operator<<(std::ostream& output, const VertexPair& vertexPair);

 private:
  Vertex first_{}; /* El vértice que forma la parte izquierda del Gadget*/
  Vertex second_{}; /* El vértice que forma la parte derecha del Gadget*/
};

#endif