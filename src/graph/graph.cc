/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file graph.cc
 * @brief Fichero que contiene la definición de todos los metodos de la clase
 * Graph
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include "../../inc/graph/graph.h"

/**
 * @brief Devuelve el numero de vecinos del vertice dado
 * @param vertex Vertice del cual calcular el numero de vecinos
 * @return int
 */
int Graph::getNumberNeighbors(const Vertex& vertex) const {
  if (!existVertex(vertex))
    throw std::runtime_error("Vertex: " + vertex.str() + " not found");
  return adjacenciesMap_.at(vertex).size();
}

/**
 * @brief Devuelve la matriz de adyacencia del grafo en formato de mapa
 * @todo Si se hace lo de cambiar el nombre, pues cambiar el nombre aqui tambien
 * @return map<Vertex, map<Vertex, edge>>
 */
std::map<Vertex, std::set<Vertex>> Graph::getDataStructure() const {
  return adjacenciesMap_;
}

// devuelve las conexiones de un vertice
/**
 * @brief Devuele las conexiones de un vertice dado en forma de mapa
 * @param vertex El vertice a calcular sus conexiones
 * @return map<vertex, edge>
 */
std::set<Vertex> Graph::getDirectConnections(const Vertex& vertex) const {
  if (!existVertex(vertex))
    throw std::runtime_error("Vertex: " + vertex.str() + " not found");
  return adjacenciesMap_.at(vertex);
}

/**
 * @brief Comprueba si existe una arista desde el vertice i hasta el vertice j,
 * pero no de j a i
 * @param vertexI
 * @param vertexJ
 * @return true Si existe una arista del vertice i hasta el vertice J. @n
 * @return false Si no existe el vertice I en el grafo.
 * @return false Si no existe una artisa desde I hasta J
 */
bool Graph::existEdge(const Vertex& vertexI, const Vertex& vertexJ) const {
  if (!existVertex(vertexI)) return false;
  if (!existVertex(vertexJ)) return false;
  if (!adjacenciesMap_.at(vertexI).count(vertexJ)) return false;
  return true;
}

/**
 * @brief Comprueba si el vertice dado existe en el grafo.
 * @param vertex El vertice a comprobar
 * @return true Si el vertice se encuentra en el grafo.
 * @return false Si el vertice no se encuentra en el grafo.
 */
bool Graph::existVertex(const Vertex& aux) const {
  return adjacenciesMap_.count(aux);
} 

/**
 * @brief Añade un arco entre vertex I y vertex J.
 * @param vertexI
 * @param vertexJ
 * @param edge
 * @throws runtime_error 
 */
void Graph::addEdge(const Vertex& vertexI, const Vertex& vertexJ) {
  if (existEdge(vertexI, vertexJ))
    throw std::runtime_error("Already exist an edge between " + vertexI.str() +
                             " and " + vertexJ.str());
  if (!existVertex(vertexI))
    throw std::runtime_error("Vertex: " + vertexI.str() + " not found");
  if (!existVertex(vertexJ))
    throw std::runtime_error("Vertex: " + vertexJ.str() + " not found");
  adjacenciesMap_[vertexI].insert(vertexJ);
}

/**
 * @brief Añade un arco entre vertex I y vertex J y entre vertex J y vertex I.
 * @param vertexI
 * @param vertexJ
 * @param edge
 * @throws runtime_error 
 */
void Graph::addEdgeBI(const Vertex& vertexI, const Vertex& vertexJ) {
  if (existEdge(vertexI, vertexJ))
    throw std::runtime_error("Already exist an edge between " + vertexI.str() +
                             " and " + vertexJ.str());
  if (!existVertex(vertexI))
    throw std::runtime_error("Vertex: " + vertexI.str() + " not found");
  if (!existVertex(vertexJ))
    throw std::runtime_error("Vertex: " + vertexJ.str() + " not found");
  adjacenciesMap_[vertexI].insert(vertexJ);
  adjacenciesMap_[vertexJ].insert(vertexI);
}

/**
 * @brief Añade un nuevo vertice al grafo.
 * @details En caso de que el vertice exista la función no realiza ninguna
 * acción
 * @param vertex El vertice a añadir al grafo.
 * @throws runtime_error Si el vertice ya existe en el grafo
 */
void Graph::addVertex(const Vertex& vertex) {
  if (existVertex(vertex))
    throw std::runtime_error("The vertex: " + vertex.str() + " already exist");
  adjacenciesMap_[vertex];
}

/**
 * @brief Devuelve un std::set con todos los vertices del nodo
 * @todo tambien un set es mejor ya que no hay nodos repetidos (por qué habrían
 * nodos repetidos?)
 * @return vector<vertex> Conjunto de todos los vertices del grafo.
 */
std::vector<Vertex> Graph::getAllVertex() const {
  std::vector<Vertex> result;
  for (const auto& auxiliarPair : adjacenciesMap_)
    result.push_back(auxiliarPair.first);
  return result;
}

/**
 * @brief Vuelca los datos del objeto Graph en el flujo de salida output
 * @param output flujo de salida en el cual se volcará la información del grafo
 * @param Graph Grafo del cual se extraerá la información
 * @return ostream& El flujo de salida con la información del grafo
 */
std::ostream& operator<<(std::ostream& output, const Graph& graph) {
  if (!graph.getSize()) return output << "Empty graph";
  for (const auto& auxiliarPair : graph) {
    output << auxiliarPair.first << " : ";
    const std::set<Vertex> neighbors{
        graph.getDirectConnections(auxiliarPair.first)};
    for (const auto& neighbor : neighbors) {
      output << neighbor << " ";
    }
    output << "\n";
  }
  return output;
}