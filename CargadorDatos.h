//
// Created by antho on 12/4/2026.
//

#ifndef SISTEMAPIM_CARGADORDATOS_H
#define SISTEMAPIM_CARGADORDATOS_H
#include <string>
#include <vector>
#include "Equipo.h"
#include "Incidencia.h"
#include "Excepciones.h"

using namespace std;

class CargadorDatos {
private:
    static Severidad parsearSeveridad(const string& s);
public:
    static void cargarDesdeArchivo(const string& nombreArchivo,
                                   vector<Equipo*>& equipos,
                                   vector<Incidencia*>& incidencias);
};
#endif //SISTEMAPIM_CARGADORDATOS_H