/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file graphParser.cc
 * @brief Fichero que contiene la definición de todos los metodos de la clase
 * GraphParser
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include <stdexcept>

#include "../../inc/graph/graphParser.h"

/**
 * @brief Extrae la información de un fichero .json para generar un objeto de la
 * clase Graph
 * @param fileName Nombre del fichero .json
 * @return Graph El objeto construido a partir de los datos del fichero .json
 * @throws runtime_error Si no es capaz de abrir el fichero .json o esta mal estructurado
 */
Graph GraphParser::readFile(const std::string& fileName) const {
  std::ifstream file(fileName);
  nlohmann::json json_data;
  if (!file.is_open()) throw std::runtime_error("Unable to open file");
  file >> json_data;
  // estructura de datos del grafo
  Graph graph;
  nlohmann::json adjacencies = json_data["adjacencies"];
  const int graphSize{int(adjacencies.size())};
  for (int i{ZERO}; i < graphSize; ++i) {
    // creamos el vertex aqui en caso de que sea un nodo sin vecinos
    const Vertex auxVertex{i};
    if (!graph.existVertex(auxVertex)) graph.addVertex(auxVertex);
    const std::string keyValue{std::to_string(i)};
    const std::vector<int> neighborsIndex{
        adjacencies[keyValue].get<std::vector<int>>()};
    for (const auto& neighborIndex : neighborsIndex) {
      if (neighborIndex < ZERO) {
        throw std::runtime_error(
            "Index of vertex must be equal or greater than 0");
      } else if (neighborIndex == i) {
        throw std::runtime_error("The graph doesn´t accept edge of type (i,i)");
      } else {
        const Vertex aux2Vertex{neighborIndex};
        if (!graph.existVertex(aux2Vertex)) graph.addVertex(aux2Vertex);
        if (!graph.existEdge(auxVertex, aux2Vertex))
          graph.addEdgeBI(auxVertex, aux2Vertex);
      }
    }
  }
  return graph;
}