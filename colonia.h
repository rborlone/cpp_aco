#pragma once
#include <optional>
#include <random>
#include <vector>
#include "hormiga.h"
#include "mapa.h"


extern const int CANTIDAD_HORMIGAS; //CANTIDAD DE HORMIGAS
extern const int THREADS; //CANTIDAD DE HILOS

class Colonia {
    public:
      Colonia(int cantidadHormigas, const Mapa &mapa);
      void mostrar() const;
      
      void reporte();
      
      int mejorValor;
      int peorValor;
      double promedio;
      void estadisticas();

    private:
        std::vector<std::optional<Hormiga>> listaHormigas;
        
};