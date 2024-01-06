/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file polyReduction.cc
 * @brief Fichero que contiene la definición de todos los metodos de la clase
 * PolyReduction
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include <stdexcept>

#include "../../inc/algorithms/polyReduction.h"

/**
 * @brief Crea los Gadgets, cada nuevo gadget empieza en el indice después del anterior
 * @details Primero en el rango de (0, 11), el siguiente (12, 23)...
 * @param graph Grafo del cual sacar la información
 * @return std::set<Gadget> Conjunto con todos los Gadgets creados
 */
std::set<Gadget> PolyReduction::createGadgets(const Graph& graph) const {
  std::set<Gadget> gadgets{};
  int mult{ZERO};
  for (const auto& vertex : graph) {
    const std::set<Vertex> neigbors{graph.getDirectConnections(vertex.first)};
    for (const auto& neighbor : neigbors) {
      VertexPair couple{Vertex{vertex.first}, Vertex{neighbor}};
      size_t previousSize{gadgets.size()};
      gadgets.insert(Gadget{couple, mult});
      if (previousSize < gadgets.size())
        ++mult;
    }
  }
  return gadgets;
}

/**
 * @brief Conecta por ambos lados los vértices de los Gadgets 
 * @param solution Grafo solución
 * @param gadgetVertex Vertice del Gadget
 * @param neighborVertex Vertice vécino
 */
void PolyReduction::linkGadgetsCommon(Graph& solution,
                                      const Vertex& gadgetVertex,
                                      const Vertex& neighborVertex) const {
  if (!solution.existVertex(neighborVertex)) solution.addVertex(neighborVertex);
  if (!solution.existEdge(gadgetVertex, neighborVertex))
    solution.addEdgeBI(gadgetVertex, neighborVertex);
}

/**
 * @brief Conecta el lado izquierdo de un Gadget con el lado izquierdo o derecho de otro
 * @param solution Grafo solución
 * @param gadgetSide Lado izquierdo del Gadget 
 * @param neigborSide El Gadget a conectar 
 */
void PolyReduction::linkGadgetsLLR(Graph& solution,
                                   const VertexPair& gadgetSide,
                                   const VertexPair& neigborSide) const {
  linkGadgetsCommon(solution, gadgetSide.getFirst(), neigborSide.getSecond());
}

/**
 * @brief Conecta el lado derecho de un Gadget con el lado izquierdo o derecho de otro
 * @param solution Grafo solución
 * @param gadgetSide Lado derecho del Gadget 
 * @param neigborSide El Gadget a conectar 
 */
void PolyReduction::linkGadgetsRRL(Graph& solution,
                                   const VertexPair& gadgetSide,
                                   const VertexPair& neigborSide) const {
  linkGadgetsCommon(solution, gadgetSide.getSecond(), neigborSide.getFirst());
}

/**
 * @brief Conecta todos los extremos de lo Gadgets 
 * @param solution Grafo solución 
 * @param gadget El gadget a conectar
 * @param info La información necesaria para las conexiones
 */
void PolyReduction::linkGadgets(Graph& solution, const Gadget& gadget,
                                const neighborInfo& info) const {
  // unimos los extremos
  const VertexPair gadgetOriginalPair{gadget.getOriginalPair()};
  const VertexPair neigborOriginalPair{info.vertexPair};
  VertexPair gadgetSide;
  VertexPair neigborSide;
  if (gadgetOriginalPair == neigborOriginalPair) return;
  if (gadgetOriginalPair.getFirst() == neigborOriginalPair.getFirst()) {
    gadgetSide = gadget.getLeftSide();
    neigborSide = info.left_;
    linkGadgetsLLR(solution, gadgetSide, neigborSide);
  } else if (gadgetOriginalPair.getFirst() == neigborOriginalPair.getSecond()) {
    gadgetSide = gadget.getLeftSide();
    neigborSide = info.right_;
    linkGadgetsLLR(solution, gadgetSide, neigborSide);
  } else if (gadgetOriginalPair.getSecond() == neigborOriginalPair.getFirst()) {
    gadgetSide = gadget.getRightSide();
    neigborSide = info.left_;
    linkGadgetsRRL(solution, gadgetSide, neigborSide);
  } else if (gadgetOriginalPair.getSecond() ==
             neigborOriginalPair.getSecond()) {
    gadgetSide = gadget.getRightSide();
    neigborSide = info.right_;
    linkGadgetsRRL(solution, gadgetSide, neigborSide);
  }
}

/**
 * @brief Inserta un Gadget en el Grafo resultado
 * @param solution Grafo solución
 * @param gadget Gadget a introducir 
 */
void PolyReduction::insertGadget(Graph& solution, const Gadget& gadget) const {
  // introducimos los indices del gadget
  const Graph gadgetStructure{gadget.getGraph()};
  for (const auto& vertex : gadgetStructure) {
    const std::set<Vertex> neigbors{vertex.second};
    if (!solution.existVertex(vertex.first)) solution.addVertex(vertex.first);
    for (const auto& neigbor : neigbors) {
      if (!solution.existVertex(neigbor)) solution.addVertex(neigbor);
      if (!solution.existEdge(vertex.first, neigbor))
        solution.addEdgeBI(vertex.first, neigbor);
    }
  }
}

/**
 * @brief Comprueba si ambos VertexPair son compatibles 
 * @param vertexPairI
 * @param vertexPairJ 
 * @return true Si ambos son compatibles 
 * @return false En cualquier otro caso
 */
bool PolyReduction::compatibleVertexPairs(const VertexPair& vertexPairI,
                                          const VertexPair& vertexPairJ) const {
  if (vertexPairI.getFirst() == vertexPairJ.getFirst()) return true;
  if (vertexPairI.getFirst() == vertexPairJ.getSecond()) return true;
  if (vertexPairI.getSecond() == vertexPairJ.getFirst()) return true;
  if (vertexPairI.getSecond() == vertexPairJ.getSecond()) return true;
  return false;
}

/**
 * @brief Comprueba si ambos Gadgets son compatibles 
 * @param gadgetI
 * @param gadgetJ 
 * @return true Si ambos son compatibles 
 * @return false En cualquier otro caso
 */
bool PolyReduction::compatibleGadgets(const Gadget& gadgetI,
                                      const Gadget& gadgetJ) const {
  const VertexPair& vertexPairI{gadgetI.getOriginalPair()};
  const VertexPair& vertexPairJ{gadgetJ.getOriginalPair()};
  return compatibleVertexPairs(vertexPairI, vertexPairJ);
}

/**
 * @brief 
 * 
 * @param doublePair 
 * @param vertexPairI 
 * @param vertexPairJ 
 * @return true 
 * @return false 
 */
bool PolyReduction::notInDoublePair(
    const std::set<std::pair<VertexPair, VertexPair>>& doublePair,
    const VertexPair& vertexPairI, const VertexPair& vertexPairJ) const {
  if (doublePair.count({vertexPairI, vertexPairJ})) return false;
  if (doublePair.count({vertexPairJ, vertexPairI})) return false;
  return true;
}

/**
 * @brief Comprueba si existe una posible conexión entre gadgets 
 * @param gadgetI 
 * @param gadgetJ 
 * @param doublePair 
 * @return true Si existe la posible conexión 
 * @return false En cualquier otro caso
 */
bool PolyReduction::possibleConnection(
    const Gadget& gadgetI, const Gadget& gadgetJ,
    const std::set<std::pair<VertexPair, VertexPair>>& doublePair) const {
  return compatibleGadgets(gadgetI, gadgetJ) &&
         notInDoublePair(doublePair, gadgetI.getOriginalPair(),
                         gadgetJ.getOriginalPair());
}

/**
 * @brief Conecta todos los Gagets entre si 
 * 
 * @param gadgets Conjunto con todos los Gagets 
 * @return Graph Grafo solución de la transformación
 */
Graph PolyReduction::connectGadgets(const std::set<Gadget>& gadgets) const {
  std::set<std::pair<VertexPair, VertexPair>> doublePair{};
  Graph solution{};
  for (const auto& gadgetI : gadgets) {
    for (const auto& gadgetJ : gadgets) {
      const VertexPair vertexPairI{gadgetI.getOriginalPair()};
      const VertexPair vertexPairJ{gadgetJ.getOriginalPair()};
      if (possibleConnection(gadgetI, gadgetJ, doublePair)) {
        doublePair.insert({vertexPairI, vertexPairJ});
        neighborInfo infoJ{vertexPairJ, gadgetJ.getLeftSide(),
                           gadgetJ.getRightSide()};
        insertGadget(solution, gadgetI);
        linkGadgets(solution, gadgetI, infoJ);
      }
    }
  }
  return solution;
}

/**
 * @brief Conecta las esquinas faltantes de los Gadgets con el primer selector
 * @param solution Grafo solución
 * @param gadgets Conjunto de Gadgets 
 * @param firstSelector 
 */
void PolyReduction::connectFirstSelector(Graph& solution,
                                         const std::set<Gadget>& gadgets,
                                         const Vertex& firstSelector) const {
  solution.addVertex(firstSelector);
  for (auto& gadget : gadgets) {
    const std::vector<Vertex> serial{gadget.serialize()};
    for (const auto& vertex : serial) {
      if (solution.getNumberNeighbors(vertex) < THREE) {
        solution.addEdgeBI(vertex, firstSelector);
      }
    }
  }
}

/**
 * @brief Conecta las esquinas faltantes de los Gadgets con el resto selectores
 * @param solution Grafo solución
 * @param firstSelector Primer selector 
 * @param maxSizeSolution Número máximo de selectores
 */
void PolyReduction::connectRestOfSelector(Graph& solution,
                                          const Vertex& firstSelector,
                                          const int maxSizeSolution) const {
  const int secondSelectorIndex{solution.getSize()};
  const std::set<Vertex> firstSelectorNeighbors{
      solution.getDirectConnections(firstSelector)};
  for (int i{secondSelectorIndex}; i < maxSizeSolution; ++i) {
    const Vertex selector{i};
    solution.addVertex(selector);
    for (const auto& neighbor : firstSelectorNeighbors) {
      if (!solution.existEdge(selector, neighbor)) {
        solution.addEdgeBI(selector, neighbor);
      }
    }
  }
}

/**
 * @brief Conecta los selectores con los Gadgets 
 * @param solution Grafo solución
 * @param gadgets Conjunto de Gadgets 
 * @param k Número de selectores 
 */
void PolyReduction::connectSelectors(Graph& solution,
                                     const std::set<Gadget>& gadgets,
                                     const int k) const {
  if (k == ZERO) return;
  const Vertex firstSelector{solution.getSize()};
  connectFirstSelector(solution, gadgets, firstSelector);
  const int maxSizeSolution{solution.getSize() + k - ONE};
  connectRestOfSelector(solution, firstSelector, maxSizeSolution);
}

/**
 * @brief Ejecuta el algoritmo para realizar la reduccion polinomial
 * @details
 * @param gf El grafo original del Vertex Cover
 * @param k El número de nodos @todo (no me acuerdo el nombre) a incluir
 * @return Graph El nuevo grafo generado para poder realizar el hamiltonian
 * cycle
 */
Graph PolyReduction::runAlgorithm(const Graph& graph, const int& k) const {
  if (k < ZERO) throw std::runtime_error("K must be equal or greater than 0");
  const std::set<Gadget> gadgets{createGadgets(graph)};
  Graph solution{connectGadgets(gadgets)};
  connectSelectors(solution, gadgets, k);
  return solution;
}