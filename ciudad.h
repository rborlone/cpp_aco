#pragma once

struct Ciudad {
    Ciudad *siguiente;
    Ciudad *anterior;
    int posicion;
    int idCiudad;
};