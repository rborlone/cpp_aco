#include "mapa.h"
#include <fstream>
#include <functional>
#include <iterator>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>

/// @brief Constructor para leer los datos del mapa.
/// @param filename Recibe el nombre y la ruta del archivo.
Mapa::Mapa(const std::string &filename)
{
    // Abre el archivo en modo lectura
    std::ifstream file(filename);

    // Verifica si el archivo se abrió correctamente
    if (!file.is_open())
    {
        throw std::runtime_error("Error al abrir el archivo");
    }

    // Lee cada línea del archivo
    std::string line;
    while (getline(file, line))
    {
        // Stream para dividir la línea en campos separados por comas
        std::stringstream ss{line};
        std::vector<int> row;
        std::string field;

        // Lee cada campo separado por comas y lo agrega al vector row
        while (getline(ss, field, ','))
        {
            row.push_back(std::stol(field));
        }

        // Agrega la fila al vector de datos
        data.push_back(row);
    }

    // Cierra el archivo
    file.close();
}

/// @brief Metodo para los candidatgos computados
/// @param TAMVEC recibe el tamano del vector
void Mapa::computarCandidatos(int TAMVEC)
{
    int n = data.size();
    candidatosDeNodo.resize(n);

    for (int i = 0; i < n; i++)
    {
        using par = std::pair<int, int>;
        std::priority_queue<par, std::vector<par>, std::greater<par>> cola;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            cola.push({data[i][j], j});
        }
        for (int k = 0; k < TAMVEC; k++)
        {
            auto aux = cola.top();
            candidatosDeNodo[i].push_back(aux.second);
            cola.pop();
        }
    }
}