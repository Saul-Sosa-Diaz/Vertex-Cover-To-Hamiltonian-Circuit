/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file polyReduction.h
 * @brief Contiene la declaración de la clase PolyReduction
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef POLYREDUCTION_H
#define POLYREDUCTION_H

#include <vector>

#include "../graph/gadget.h"
#include "algorithm_T.h"

/**
 * @class PolyReduction
 * @extends Algorithm_T
 * @brief La clase representa la reducción polinomial del Vertex Cover a
 * Hamiltonian Cycle
 * @details Es una clase que concreta a la clase Algorithm_T
 */
class PolyReduction final : public Algorithm_T<Graph, Graph, int> {
 public:

  // Getters y Setters
  /**
   * @brief Devuelve la instancia del objeto PolyReduction
   * @return PolyReduction& 
   */
  static PolyReduction& getInstance() {
    static PolyReduction instance;  // This will be created once
    return instance;
  }

  // Métodos 
  Graph runAlgorithm(const Graph& graph, const int& k) const override;

 private:
  std::set<Gadget> createGadgets(const Graph& graph) const;
  void insertGadget(Graph& graph, const Gadget& gadget) const;
  bool compatibleGadgets(const Gadget& gadgetI, const Gadget& gadgetJ) const;
  bool compatibleVertexPairs(const VertexPair& vertexPairI,
                             const VertexPair& vertexPairJ) const;
  bool notInDoublePair(
      const std::set<std::pair<VertexPair, VertexPair>>& doublePair,
      const VertexPair& vertexPairI, const VertexPair& vertexPairJ) const;
  bool possibleConnection(
      const Gadget& gadgetI, const Gadget& gadgetJ,
      const std::set<std::pair<VertexPair, VertexPair>>& doublePair) const;
  void linkGadgets(Graph& solution, const Gadget& gadget,
                   const neighborInfo& info) const;
  void linkGadgetsCommon(Graph& solution, const Vertex& gadgetVertex,
                         const Vertex& neighborVertex) const;
  void linkGadgetsLLR(Graph& solution, const VertexPair& gadgetSide,
                      const VertexPair& neigborSide) const;
  void linkGadgetsRRL(Graph& solution, const VertexPair& gadgetSide,
                      const VertexPair& neigborSide) const;
  Graph connectGadgets(const std::set<Gadget>& gadgets) const;
  void connectSelectors(Graph& solution, const std::set<Gadget>& gadgets,
                        const int k) const;
  void connectFirstSelector(Graph& solution, const std::set<Gadget>& gadgets,
                            const Vertex& firstSelector) const;
  void connectRestOfSelector(Graph& solution, const Vertex& firstSelector,
                             const int maxSizeSolution) const;
  PolyReduction(){};
};

#endif