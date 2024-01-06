/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file vertexPair.cc
 * @brief Fichero que contiene la definición de todos los metodos de la clase
 * VertexPair
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include "../../inc/graph/vertexPair.h"

/**
 * @brief Operador menor, Compara dos vertexPair
 * @param vertexPair 
 * @return true Si el objeto es menor que el otro vertexPair 
 * @return false Si el objeto es mayor o igual que el otro vertexPair 
 */
bool VertexPair::operator<(const VertexPair& vertexPair) const {
  return std::minmax(first_, second_) <
         std::minmax(vertexPair.getFirst(), vertexPair.getSecond());
}

/**
 * @brief Operador igual, Compara dos vertexPair
 * @param vertexPair 
 * @return true Si el objeto es igual que el otro vertexPair 
 * @return false Si el objeto es distinto que el otro vertexPair 
 */
bool VertexPair::operator==(const VertexPair& vertexPair) const {
  return (first_ == vertexPair.getFirst() && second_ == vertexPair.getSecond());
}

/**
 * @brief Operador igual, Compara dos vertexPair
 * @param vertexPair 
 * @return true Si el objeto es distinto que el otro vertexPair 
 * @return false Si el objeto es igual que el otro vertexPair 
 */
bool VertexPair::operator!=(const VertexPair& vertexPair) const {
  return !(*this == vertexPair);
}

/**
 * @brief Vuelca los datos del objeto VertexPair en el flujo de salida output
 * 
 * @param output flujo de salida en el cual se volcará la información del grafo
 * @param vertexPair VertexPair del cual se extraerá la información
 * @return std::ostream& El flujo de salida con la información del VertexPair
 */
std::ostream& operator<<(std::ostream& output, const VertexPair& vertexPair) {
  return output << vertexPair.getFirst() << " " << vertexPair.getSecond();
}