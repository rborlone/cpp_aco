#include "hormiga.h"
#include <vector>
#include <random>
#include <iostream>

/// @brief Constructor de Hormiga
/// @param mapa recibe el mapa
Hormiga::Hormiga(const Mapa &mapa):ady(mapa.data.size()) {

    std::random_device semilla;
    const auto seed {semilla.entropy() ? semilla() : time(nullptr)};
    std::mt19937 engine{ static_cast<std::mt19937::result_type>(seed)};

    largo=mapa.data.size();
    std::uniform_int_distribution<int> dist(0,largo-1);
    std::vector<bool> ciudadesVisitadas (largo,false);

    //Ciudad Inicial de la Hormiga
    ciudadInicial=dist(engine);
    int actual=ciudadInicial;
    int cont=0;
    while (cont++<largo){
        ady[actual].idCiudad=actual;
        ciudadesVisitadas[actual]=true;

        int siguiente=ciudadInicial;
        if (cont<largo){
            std::vector<int> candidatos_disponibles;
            auto & candidatos=mapa.candidatosDeNodo[actual];
            for (auto c:candidatos){
                if (!ciudadesVisitadas[c]) 
                    candidatos_disponibles.push_back(c);
            }
            if (candidatos_disponibles.size()!=0){       //seleccion por candidatos
                // std::discrete_distribution<int> dist2(candidatos_disponibles.begin(),candidatos_disponibles.end());
                siguiente=candidatos_disponibles[prioritize_short_distance(candidatos_disponibles)];
            } else {                                    //seleccion al azar
                int posible=dist(engine);
                while (ciudadesVisitadas[posible]){
                    posible=(posible+1)%largo;
                }
                siguiente=posible;
            } 
        }
        ady[actual].siguiente=&ady[siguiente];
        ady[siguiente].anterior=&ady[actual];
        actual=siguiente;
    }
    
    //actualiza posiciones
    Ciudad *inicio=&ady[0];
    inicio->posicion=0;
    Ciudad *ptr_actual=inicio->siguiente;
    int pos=1;
    while (ptr_actual!=inicio){
        ptr_actual->posicion=pos++;
        ptr_actual=ptr_actual->siguiente;
    }

    // mostrar();
    calcularCosto(mapa);
}

void Hormiga::calcularCosto(const Mapa &mapa)  {
    Ciudad *inicio=&ady[0];
    Ciudad *ptr=inicio->siguiente;
    int suma=0;
    while(ptr!=inicio) {
        suma+=mapa.data[ptr->anterior->idCiudad][ptr->idCiudad];
        ptr=ptr->siguiente;
    }
    suma+=mapa.data[ptr->anterior->idCiudad][ptr->idCiudad];
    costo = suma;
}

// Función para generar un índice basado en probabilidades ponderadas
int get_weighted_index(const std::vector<double>& weights, std::mt19937& gen) {
    std::discrete_distribution<> dist(weights.begin(), weights.end());
    return dist(gen);
}

// Función para retornar una distancia de manera aleatoria privilegiando las más cortas
int Hormiga::prioritize_short_distance(const std::vector<int>& distances) {
    // Generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generar pesos inversamente proporcionales a las distancias
    std::vector<double> weights(distances.size());
    std::transform(distances.begin(), distances.end(), weights.begin(), [](int distance) {
        return 1.0 / distance;
    });

    // Obtener el índice privilegiando las distancias más cortas
    int index = get_weighted_index(weights, gen);

    // Retornar la distancia correspondiente
    return index;
}

void Hormiga::mostrar() const {
    std::cout<<"0,";
    const Ciudad * inicio=&ady[0];
    const Ciudad * actual=inicio->siguiente;
    while (actual!=inicio){
        std::cout<<actual->idCiudad<<",";
        actual=actual->siguiente;
    }
    std::cout<<"0"<<std::endl;

    std::cout<<ady.size()<<std::endl;
}
