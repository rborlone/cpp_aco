#pragma once
#include "mapa.h"
#include "ciudad.h"
#include <vector>

class Hormiga
{
private:
    std::vector<Ciudad> ady;
    int prioritize_short_distance(const std::vector<int>& distances);

public:
    // constructor
    Hormiga(const Mapa &mapa);
    void calcularCosto(const Mapa &mapa);
    void mostrar() const;
    void mover();
    int costo;
    int largo;
    int ciudadInicial;
    
};