//
// Created by ailem on 11/4/2026.
//

#ifndef SISTEMAPIM_MANTCORRECTIVO_H
#define SISTEMAPIM_MANTCORRECTIVO_H
#include "IMantenimiento.h"

using namespace std;

class MantCorrectivo : public IMantenimiento{
public:
    void ejecutar(Equipo& e) override;
    string getNombre() const override;
};


#endif //SISTEMAPIM_MANTCORRECTIVO_H