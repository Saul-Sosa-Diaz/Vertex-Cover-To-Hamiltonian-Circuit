/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file gadget.cc
 * @brief Fichero que contiene la definición de todos los metodos de la clase
 * Gadget
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include "../../inc/graph/gadget.h"

/**
 * @brief Construye un objeto de la clase Gadget
 *
 * @param vertexPair El par de vertices con los que se creará el gadget
 * @param mult (No se que es mult)
 */
Gadget::Gadget(const VertexPair& vertexPair, const int mult)
    : vertexPair_(vertexPair), mult_(mult) {
  graph_ = createStructure();
  left_ = setLeftSide();
  right_ = setRightSide();
}

/**
 * @brief Genera el gadget a partir de los vertices pasados y el factor mult
 *
 * @param mult
 * @return graph
 */
Graph Gadget::createStructure() const {
  Graph result;
  for (int i{ZERO}; i < TWELVE; ++i) {
    if (mult_ == ZERO)
      result.addVertex(Vertex{i});
    else
      result.addVertex(Vertex{i + mult_ * TWELVE});
  }
  int countOdd{ONE};
  int countEven{ZERO};
  for (int i{TWO}; i < TWELVE; ++i) {
    if (!(i % TWO)) {
      result.addEdgeBI(countEven + mult_ * TWELVE, i + mult_ * TWELVE);
      countEven += TWO;
    } else {
      result.addEdgeBI(countOdd + mult_ * TWELVE, i + mult_ * TWELVE);
      countOdd += TWO;
    }
  }
  result.addEdgeBI(Vertex{ZERO + mult_ * TWELVE},
                   Vertex{FIVE + mult_ * TWELVE});
  result.addEdgeBI(Vertex{ONE + mult_ * TWELVE}, Vertex{FOUR + mult_ * TWELVE});
  result.addEdgeBI(Vertex{SIX + mult_ * TWELVE},
                   Vertex{ELEVEN + mult_ * TWELVE});
  result.addEdgeBI(Vertex{SEVEN + mult_ * TWELVE},
                   Vertex{TEN + mult_ * TWELVE});
  return result;
}

/**
 * @brief Método auxiliar que construye el Vertex Pair izquierdo del Gadget
 * @return VertexPair 
 */
VertexPair Gadget::setLeftSide() const {
  return VertexPair{Vertex{ZERO + mult_ * TWELVE},
                    Vertex{TEN + mult_ * TWELVE}};
}

/**
 * @brief Método auxiliar que construye el Vertex Pair derecho del Gadget
 * @return VertexPair 
 */
VertexPair Gadget::setRightSide() const {
  return VertexPair{Vertex{ONE + mult_ * TWELVE},
                    Vertex{ELEVEN + mult_ * TWELVE}};
}

/**
 * @brief Devuelve las esquinas del Gadget en forma de vector
 * @return std::vector<Vertex> 
 */
std::vector<Vertex> Gadget::serialize() const {
  return {left_.getFirst(), left_.getSecond(), right_.getFirst(),
          right_.getSecond()};
}

/**
 * @brief Comprueba si el objeto actual es menor que el objeto other.
 * @details Esta comprobación se realiza utilizando los pares que generan los
 * gadgets. \n Este metodo es necesario para poder introducir objetos de la
 * clase Gadget en un std::map
 * @param other o another o otherGadget Objeto de la clase Gadget con el que
 * comparar los pares
 * @return true Si el objeto actual es menor que el otro objeto
 * @return false Si el objeto actual es mayor o igual que el otro objeto
 */
bool Gadget::operator<(const Gadget& gadget) const {
  return vertexPair_ < gadget.getOriginalPair();
}