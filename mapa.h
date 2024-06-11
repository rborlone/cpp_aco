#pragma once
#include <string>
#include <vector>

class Mapa
{
private:
    /* data */
public:
    Mapa(const std::string &filename);
     void computarCandidatos(int TAMVEC);
     void mostrarMapa();
     void mostrarCandidatos();
     //Matriz de candidatos.
     std::vector<std::vector<int>> candidatosDeNodo;
     //Matriz de mapas.
     std::vector<std::vector<int>> data;
};