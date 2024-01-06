/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file vertex.cc
 * @brief Fichero que contiene la definición de todos los metodos de la clase
 * Vertex
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include "../../inc/graph/vertex.h"

/**
 * @brief Vuelca los datos del objeto vertex en el flujo de salida output
 * @param output flujo de salida en el cual se volcará la información del
 * vertice
 * @param vertex Vertice del cual se extraerá la información
 * @return ostream& El flujo de salida con la información del vertice
 */
std::ostream &operator<<(std::ostream &output, const Vertex &vertex) {
  return output << vertex.getIndex();
}