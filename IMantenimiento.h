//
// Created by ailem on 11/4/2026.
//

#ifndef SISTEMAPIM_IMANTENIMIENTO_H
#define SISTEMAPIM_IMANTENIMIENTO_H
#include "Equipo.h"
#include <string>

using namespace std;

class IMantenimiento{
public:
    virtual ~IMantenimiento() = default;

    virtual void ejecutar(Equipo& e) = 0;
    virtual string getNombre() const =0;

};


#endif //SISTEMAPIM_IMANTENIMIENTO_H