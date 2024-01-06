/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file menu.h
 * @brief Contiene la declaración de las funciones necesarias para hacer
 * funcionar el menu
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef MENU_H
#define MENU_H

#include <filesystem>
#include <regex>

#include "../graph/graphParser.h"
#include "../algorithms/polyReduction.h"

std::vector<std::string> readFolder();
void trimFileNames(const std::vector<std::string>& files);
void convertToJson(const Graph& graph, const std::string& fileName);
void menu();

#endif