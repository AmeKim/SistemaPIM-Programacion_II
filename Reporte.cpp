//
// Created by antho on 12/4/2026.
//

#include "Reporte.h"
#include "EquipoComputo.h"
#include "EquipoLaboratorio.h"
#include "Utiles.h"
#include <sstream>
using namespace std;

Reporte::Reporte(const string& nombreDiario, const string& nombreAcumulado)
    : nombreDiario(nombreDiario), nombreAcumulado(nombreAcumulado) {}

Reporte::~Reporte() {
    cerrarArchivos();
}

void Reporte::abrirArchivos() {
    archivoDiario.open(nombreDiario);
    if (!archivoDiario.is_open()) {
        throw runtime_error("No se pudo abrir el archivo diario: " + nombreDiario);
    }
    archivoAcumulado.open(nombreAcumulado);
    if (!archivoAcumulado.is_open()) {
        throw runtime_error("No se pudo abrir el archivo acumulado: " + nombreAcumulado);
    }
}

void Reporte::cerrarArchivos() {
    if (archivoDiario.is_open())   archivoDiario.close();
    if (archivoAcumulado.is_open()) archivoAcumulado.close();
}

void Reporte::registrarDia(int dia,
                            const vector<Equipo*>& equipos,
                            int limite,
                            int backlog,
                            double riesgoGlobal) {
    stringstream ss;
    ss << "\n=== DIA " << dia << " ===\n";
    ss << "Equipos atendidos:\n";
    ss << left
       << setw(14) << "ID"
       << setw(12) << "Prioridad"
       << setw(11) << "Estado"
       << setw(25) << "Tipo" << "\n";
    ss << "------------ ----------- ---------- -------------------------\n";

    for (int i = 0; i < limite; i++) {
        Equipo* e = equipos[i];
        ss << left
           << setw(14) << e->getId()
           << setw(12) << Utiles::formatear(e->calcularPrioridad())
           << setw(11) << Utiles::formatear(e->getEstado())
           << setw(25) << e->getTipo() << "\n";

        EquipoComputo* ec = dynamic_cast<EquipoComputo*>(e);
        if (ec != nullptr) {
            ss << setw(14) << " "
               << "RAM: " << ec->getRamGB()
               << " GB | SO: " << ec->getSistemaOperativo() << "\n";
        }

        EquipoLaboratorio* el = dynamic_cast<EquipoLaboratorio*>(e);
        if (el != nullptr) {
            ss << setw(14) << " "
               << "Tipo: " << el->getTipoEquipo()
               << " | Calibrado: " << (el->isCalibrado() ? "Si" : "No") << "\n";
        }
    }

    ss << "\nEquipos pendientes:\n";
    for (int i = limite; i < equipos.size(); i++) {
        Equipo* e = equipos[i];
        ss << left
           << setw(14) << e->getId()
           << setw(12) << Utiles::formatear(e->calcularPrioridad())
           << setw(25) << e->getTipo() << "\n";
    }

    ss << "\nBacklog pendiente: " << backlog << "\n";
    ss << "Riesgo Global: " << Utiles::formatear(riesgoGlobal) << "\n";

    archivoDiario << ss.str();
    archivoAcumulado << ss.str();
}

void Reporte::registrarResumenFinal(int totalDias, double riesgoFinal) {
    stringstream ss;
    ss << "\n=== RESUMEN FINAL ===\n"
       << "Total de dias simulados: " << totalDias << "\n"
       << "Riesgo Global final: " << Utiles::formatear(riesgoFinal) << "\n";

    archivoAcumulado << ss.str();
}