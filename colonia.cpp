#include "colonia.h"
#include "hormiga.h"
#include <thread>
#include <mutex>
#include <iostream>

Colonia::Colonia(int cantidadHormigas, const Mapa &mapa):listaHormigas(cantidadHormigas){
    auto inicio = std::chrono::high_resolution_clock::now();
    
    int ind=0;
    std::mutex mtx;
    std::vector<std::thread> threads;
    int general=cantidadHormigas/THREADS;
    int diferencia=cantidadHormigas%THREADS;

    for (int i=0;i<THREADS;i++){
        //setea el tamaño de individuos a generar (p o p+1)
        int k=(i<diferencia) ? general + 1 : general;
        threads.emplace_back([this,&mtx,&ind,&mapa,k](){
            
            for (int j=0;j<k;j++){
                mtx.lock();
                int indice=ind++;
                mtx.unlock();

                Hormiga hormiga (mapa);
                listaHormigas[indice]= hormiga;
                // assert(soluciones[indice]->isConexa());
            }
        });
    }
    for (auto &hilo:threads){
        hilo.join();
    }
    //reemplaza un individuo con el mejorAnterior
    // std::sort(soluciones.begin(),soluciones.end());
    // estadisticas();

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracion = fin - inicio;
    std::cout<<"Tiempo Generacion colonia de "<< cantidadHormigas << " hormigas, en: " << duracion.count()<<std::endl;

    mostrar();
}

void Colonia::mostrar() const {
    int indice = 0;
    while (indice != listaHormigas.size()){
        std::cout << "hormiga[" << indice + 1 << "]: " << listaHormigas[indice]->costo <<std::endl;
        indice++;
    }
}