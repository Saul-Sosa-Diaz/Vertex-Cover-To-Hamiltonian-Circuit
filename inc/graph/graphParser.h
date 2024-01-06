/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file graphParser.h
 * @brief Contiene la declaración de la clase GraphParser
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef GRAPHPARSER_H
#define GRAPHPARSER_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "graph.h"

/**
 * @class GraphParser (Creo que seria un nombre más representativo)
 * @brief La clase GraphParser se encarga de leer los ficheros .json y crear
 * objetos de la clase Graph
 * @details Se utiliza la librería nlohmann para tratar los ficheros .json
 */
class GraphParser {
 public:
  // Constructores y destructor
  /**
   * @brief Obtiene la instancia única de GraphParser
   * @return Instancia única de GraphParser
   */
  static GraphParser& getInstance() {
    static GraphParser instance;  // Se crea solo en la primera llamada
    return instance;
  }

  // Métodos 
  Graph readFile(const std::string& fileName) const;

  // Patrón singleton
  GraphParser(const GraphParser&) = delete;
  GraphParser& operator=(const GraphParser&) = delete;

 private:
  GraphParser() = default;
};

#endif