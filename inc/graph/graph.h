/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file graph.h
 * @brief Contiene la declaración de la clase Graph
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <set>
#include <vector>

#include "vertex.h"

/**
 * @class Graph graph.h
 * @brief La clase Graph se encarga de representar un grafo.
 * @details Contiene todos los métodos necesarios para trabajar con un grafo.
 */
class Graph {
 public:
  // Constructores y destructor.
  Graph() {}  

  /**
   * @brief Construye un objeto de la clase Graph utilizando la informacion del
   * mapa
   * @details Para que la clase parser pueda devolver un grafo no vacio (no
   * entiendo esta parte)
   * @param adjacenciesMap Matriz de adyacencia a almacenar en el grafo.
   * @todo No se si podriamos a;adir comprobaciones para ver si esta correcto.
   */
  Graph(const std::map<Vertex, std::set<Vertex>>& adjacenciesMap)
      : adjacenciesMap_{adjacenciesMap} {}

  // Getters y Setters
  /**
   * @brief Devuelve la cantidad de nodos del grafo
   * @return int
   */
  int getSize() const { return adjacenciesMap_.size(); }
  int getNumberNeighbors(const Vertex& vertex) const;
  std::map<Vertex, std::set<Vertex>> getDataStructure() const;
  std::set<Vertex> getDirectConnections(const Vertex& vertex) const;
  std::vector<Vertex> getAllVertex() const;
  auto begin() const { return adjacenciesMap_.begin(); }
  auto end() const { return adjacenciesMap_.end(); }

  void addEdge(const Vertex& firstVertex, const Vertex& secondVertex);
  void addEdgeBI(const Vertex& firstVertex, const Vertex& secondVertex);
  void addVertex(const Vertex& vertex);

  // Métodos
  bool existEdge(const Vertex& firstVertex, const Vertex& secondVertex) const;
  bool existVertex(const Vertex& vertex) const;

  // Operadores
  friend std::ostream& operator<<(std::ostream& output, const Graph& graph);

 private:
  std::map<Vertex, std::set<Vertex>>
      adjacenciesMap_{}; /* Matriz de adyacencia del grafo */
};

#endif