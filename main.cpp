#include "mapa.h"
#include "hormiga.h"
#include "colonia.h"
#include <iostream>
#include <optional>
#include <array>
#include <random>

const int CANTIDAD_HORMIGAS=25; //CANTIDAD DE HORMIGAS
const int THREADS=6; //CANTIDAD DE HILOS

int main() {



//      const int nrolls = 532; // number of experiments
//   const int nstars = 532;   // maximum number of stars to distribute

//   std::default_random_engine generator;
//   std::geometric_distribution<int> distribution(0.15);

//   int p[25]={};

//   for (int i=0; i<nrolls; ++i) {
//     int number = distribution(generator);
//     if (number<25) ++p[number];
//   }

//   std::cout << "geometric_distribution (0.3):" << std::endl;
//   for (int i=0; i<25; ++i)
//     std::cout << i << ": " << std::string(p[i]*nstars/nrolls,'*') << std::endl;

//   return 0;
    
    Mapa m {"/Users/rborlone/Proyectos/Estudio/TSP Problema/csharp_tsp_v2/data/att532.dat"};
    m.computarCandidatos(25);

    
    // Hormiga h {m};

    Colonia col {CANTIDAD_HORMIGAS, m};
    
    // std::cout<<"\tCosto de Hormiga:"<< h.costo ;

    return 0;
}


