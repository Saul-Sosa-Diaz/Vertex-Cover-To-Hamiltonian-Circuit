/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file algorithm_T.h
 * @brief Contiene la declaración de la clase Algorithm_T
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#ifndef ALGORITHM_T_H
#define ALGORITHM_T_H

/**
 * @class Algorithm_T
 * @brief Clase abstracta que ejerce la función de plantilla para los algortimos
 *    A implementar en el proyecto.
 * @tparam ReturnType Template que indica el tipo de valor a devolver por el
 * algoritmo
 * @tparam ArgType Template que indica los argumentos que acepta el algoritmo
 */
template <typename ReturnType, typename... ArgType>
class Algorithm_T {
 public:

  // Constructores y Destructor
  virtual ~Algorithm_T() {}

  // Métodos
  virtual ReturnType runAlgorithm(const ArgType&... arg) const = 0;

  // Getters y Setters
  /**
   * @brief Devuelve la instancia del objeto Algorithm_t
   * @return Algorithm_T& 
   */
  static Algorithm_T& getInstance() {
    static Algorithm_T instance;
    return instance;
  }

 protected:

 // Constructores y Destructor
  Algorithm_T() {}
  Algorithm_T(const Algorithm_T&) = delete;
  
  // Operadores
  Algorithm_T& operator=(const Algorithm_T&) = delete;
};

#endif