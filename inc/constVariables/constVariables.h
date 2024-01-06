/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file constVariables.h
 * @brief Contiene diferentes constantes que se repiten a lo largo de todo el proyecto.
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include <limits>

inline constexpr int ZERO{0};
inline constexpr int ONE{1};
inline constexpr int TWO{2};
inline constexpr int THREE{3};
inline constexpr int FOUR{4};
inline constexpr int FIVE{5};
inline constexpr int SIX{6};
inline constexpr int SEVEN{7};
inline constexpr int TEN{10};
inline constexpr int ELEVEN{11};
inline constexpr int TWELVE{12};
inline constexpr int INFINITE{std::numeric_limits<int>::infinity()};