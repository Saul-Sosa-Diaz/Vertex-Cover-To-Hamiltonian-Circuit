/*!
 * Universidad de La Laguna
 * Escuela Superior de Ingenierıa y Tecnologıa
 * Grado en Ingenierıa Informatica
 * Curso: 4º
 * Asignatura: Complejidad Computacional
 * @file menu.cc
 * @brief Fichero que contiene la definición de los metodos necesarios para
 * hacer funcionar el menu
 * @version 1.0
 * @date 6/12/2023
 * @author Raimon Mejias Hernandez (alu0101390161@ull.edu.es)
 * @author Evian Concepción Peña (alu0101395548@ull.edu.es)
 * @author Eva Peso Adán (alu0101398037@ull.edu.es)
 * @author Francisco Marques Armas (alu0101438412@ull.edu.es)
 * @author Saul Sosa Diaz (alu0101404141@ull.edu.es)
 */

#include "../../inc/utils/menu.h"

/**
 * @brief Lee los ficheros contenidos en el directorio graphIntances
 *     y los imprime por pantalla
 * @todo si solo lee ese directorio sería mejor ponerlo en el nombre de la
 * función
 * @return vector<string> Con los ficheros .json del directorio
 */
std::vector<std::string> readFolder() {
  const std::regex jsonFileRegex("graphInstances/[^/]+\\.json");
  const std::string path = "graphInstances";
  const std::string closeProgram = "Close program";
  std::vector<std::string> fileNames{};
  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    const std::string name = entry.path();
    // solo guardamos los .json
    if (std::regex_match(name, jsonFileRegex)) {
      fileNames.emplace_back(name);
    }
  }
  fileNames.emplace_back(closeProgram);
  return fileNames;
}

/**
 * @brief Corta el Path y la extensión .json de los ficheros,
 *    dejando solo el nombre de los ficheros.
 * @param files Vector con el path completo de los ficheros .json obtenidos.
 */
void trimFileNames(const std::vector<std::string>& files) {
  // count es para que el usuario pueda elejir por pantalla
  int count{ONE};
  for (auto name : files) {
    // quitamos el camino hasta el fichero
    size_t lastSlashPos = name.find_last_of('/');
    name = name.substr(lastSlashPos + ONE);
    // le quitamos la extension
    size_t lastDotPos = name.find_last_of('.');
    name = name.substr(ZERO, lastDotPos);
    std::cout << "   " << count << ": " << name << std::endl;
    ++count;
  }
}

/**
 * @brief Convierte la información de un grafo en un fichero .Json
 * @param graph Grafo del cual se leerá la información
 * @param fileName Nombre del fichero de escritura
 * @throws runtime_error Si no es posible abrir el fichero
 */
void convertToJson(const Graph& graph, const std::string& fileName) {
  std::ofstream file{fileName};
  if (!file.is_open()) throw std::runtime_error("Unable to open the file");
  file << "{\n";
  file << "   \"adjacencies\" : {\n";
  std::string line{};
  for (auto vertex_it = graph.begin(); vertex_it != graph.end(); ++vertex_it) {
    const auto& vertex = *vertex_it;
    line += "   \"";
    line += vertex.first.str();
    line += "\" : [";
    const std::set<Vertex>& neighbors = vertex.second;
    for (auto neighbor_it = neighbors.begin(); neighbor_it != neighbors.end();
         ++neighbor_it) {
      line += neighbor_it->str();
      if (std::next(neighbor_it) != neighbors.end()) {
        line += ", ";
      }
    }
    line += "]";
    if (std::next(vertex_it) != graph.end()) {
      line += ",";
    }
    line += "\n";
    file << line;
    line.clear();
  }
  file << "   }\n}";
  file.close(); 
}

/**
 * @brief Permite al usuario interactuar con el programa a través de
 *   un bucle que lee los inputs del usuario
 */
void menu() {
  // llamada al sistema para limpiar la terminal
  system("clear");
  while (true) {
    int option;
    std::cout << "Menu options:\n";
    // recogemos los nombres de los ficheros
    // (todo el path desde donde el makefile)
    std::vector<std::string> files = readFolder();
    // mostramos por pantalla de manera bonita
    trimFileNames(files);
    std::cout << "Choose instance: ";
    std::cin >> option;
    // de momento una excepcion pero le podemos dejar insertar de nuevo
    if (size_t(option) > files.size() || option < ONE)
      throw std::runtime_error("That option doesnt exist");
    // en caso de que decida cerrar el programa
    if (size_t(option) == files.size()) {
      system("clear");
      std::cout << "Closing program...\n";
      return;
    }
    // leemos el grafo desde un fichero json
    Graph gf = GraphParser::getInstance().readFile(files[option - ONE]);
    system("clear");
    std::cout << "Instance:\n" << gf << std::endl;
    int maxSize;
    std::cout << "Choose the biggest Vertex Cover possible size: ";
    std::cin >> maxSize;
    auto& reduc{PolyReduction::getInstance()};
    const Graph solution{reduc.runAlgorithm(gf, maxSize)};
    std::cout << solution << "\n";
    char tofile;
    std::cout << "Convert solution into .json (Y/N): ";
    std::cin >> tofile;
    if (tofile == 'Y' || tofile == 'y') {
      system("clear");
      std::string fileName;
      std::cout << "Introduce the file name: ";
      std::cin >> fileName;
      const std::string json{".json"};
      convertToJson(solution, "graphResults/" + fileName + json);
      const std::string pathJulia{"julia ./src/plots/showPlot.jl ./graphResults/"};
      system((pathJulia + fileName + json).c_str());
    }
    system("clear");
  }
} 