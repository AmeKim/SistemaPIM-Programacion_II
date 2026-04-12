//
// Created by ailem on 11/4/2026.
//

#ifndef SISTEMAPIM_MANTPREVENTIVO_H
#define SISTEMAPIM_MANTPREVENTIVO_H
#include "IMantenimiento.h"

using namespace std;
class MantPreventivo : public IMantenimiento{
    public:
    void ejecutar(Equipo& e) override;
    string getNombre() const override;

};


#endif //SISTEMAPIM_MANTPREVENTIVO_H