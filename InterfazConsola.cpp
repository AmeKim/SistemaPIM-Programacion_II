//
// Created by ailem on 21/4/2026.
//

#include "InterfazConsola.h"
#include "InterfazConsola.h"
#include "EquipoComputo.h"
#include "EquipoLaboratorio.h"
#include <sstream>
#include <iomanip>
using namespace std;

void InterfazConsola::mostrarIniciSimulacion() {
    Utiles::print("Iniciando simulacion de 30 dias...\n");
}

void InterfazConsola::mostrarDia(int dia) {
    stringstream ss;
    ss << "\n=== DIA " << dia << " ===\n";
    Utiles::print(ss.str());
}

void InterfazConsola::mostrarTopPrioridad(const vector<Equipo*>& equipos, int limite) {
    Utiles::print("3 Equipos Prioritarios:\n");
    Utiles::imprimirEncabezadoEquipos();
    for (int i = 0; i < limite; i++) {
        Equipo* e = equipos[i];
        stringstream ss;
        ss << left
           << setw(14) << e->getId()
           << setw(12) << Utiles::formatear(e->calcularPrioridad())
           << setw(11) << Utiles::formatear(e->getEstado())
           << setw(25) << e->getTipo() << "\n";
        Utiles::print(ss.str());
    }
}

void InterfazConsola::mostrarEncabezadoMantenimiento() {
    Utiles::print("Mantenimiento aplicado:\n");
    Utiles::imprimirEncabezadoMantemiento();
}

void InterfazConsola::mostrarFilaMantenimiento(Equipo* equipo, const string& tipoMant) {
    stringstream ss;
    ss << left
       << setw(14) << equipo->getId()
       << setw(25) << tipoMant
       << setw(11) << Utiles::formatear(equipo->getEstado())
       << setw(12) << equipo->contarIncidenciasActivas() << "\n";
    Utiles::print(ss.str());
}

void InterfazConsola::mostrarDetalleEquipo(Equipo* equipo) {
    EquipoComputo* ec = dynamic_cast<EquipoComputo*>(equipo);
    if (ec != nullptr) {
        stringstream ss;
        ss << left << setw(14) << " "
           << "RAM: " << ec->getRamGB()
           << " GB | SO: " << ec->getSistemaOperativo() << "\n";
        Utiles::print(ss.str());
    }

    EquipoLaboratorio* el = dynamic_cast<EquipoLaboratorio*>(equipo);
    if (el != nullptr) {
        stringstream ss;
        ss << left << setw(14) << " "
           << "Tipo: " << el->getTipoEquipo()
           << " | Calibrado: " << (el->isCalibrado() ? "Si" : "No") << "\n";
        Utiles::print(ss.str());
    }
}

void InterfazConsola::mostrarResumenDia(int backlog, double riesgoGlobal, const string& nivelRiesgo) {
    stringstream ss;
    ss << "Backlog pendiente: " << backlog << "\n"
       << "Riesgo Global: " << Utiles::formatear(riesgoGlobal)
       << "% - " << nivelRiesgo << "\n";
    Utiles::print(ss.str());
}

void InterfazConsola::mostrarSimulacionCompletada(double riesgoGlobal, const string& nivelRiesgo) {
    stringstream ss;
    ss << "\n=== SIMULACION COMPLETADA ===\n"
       << "Riesgo Global final: " << Utiles::formatear(riesgoGlobal)
       << "% - " << nivelRiesgo << "\n";
    Utiles::print(ss.str());
}