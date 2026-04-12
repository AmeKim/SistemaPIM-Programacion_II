//
// Created by ailem on 11/4/2026.
//

#include <random>
#include <sstream>
#include "Simulador.h"
#include "EquipoComputo.h"
#include "EquipoLaboratorio.h"
#include "Utiles.h"

using namespace std;

Simulador::Simulador() : diaActual(0), backlog(0), riesgoGlobal(0.0), generador(random_device{}()){ }

Simulador::~Simulador(){
    for (int i = 0; i < equipos.size(); i++) {
        delete equipos[i];
    }
    for (int i = 0; i < incidencias.size(); i++) {
        delete incidencias[i];
    }
}

void Simulador::agregarEquipo(Equipo* equipo){
    if (equipo == nullptr) {
        throw OperacionInconsistenteException("No se puede agregar un equipo nulo");
    }
    equipos.push_back(equipo);
}

void Simulador::mergeSort(vector<Equipo*>& vec, int inicio, int fin){
    if (inicio < fin){
        int mid = (inicio + fin) / 2;
        mergeSort(vec, inicio, mid);
        mergeSort(vec, mid + 1, fin);
        merge(vec, inicio, mid, fin);
    }
}

void Simulador::merge(vector<Equipo*>& vec, int inicio, int mid, int fin){
    int n1 = mid - inicio + 1;
    int n2 = fin - mid;

    vector<Equipo*> izq(n1);
    vector<Equipo*> der(n2);

    for (int i = 0; i < n1; i++){
        izq[i] = vec[inicio + i];
    }

    for (int j = 0; j < n2; j++){
        der[j] = vec[mid + 1 + j];
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2){
        if (izq[i]->calcularPrioridad() >= der[j]->calcularPrioridad()) {
            vec[k] = izq[i];
            i++;
        }else{
            vec[k] = der[j];
            j++;
        }
        k++;
    }

    while (i < n1) { vec[k] = izq[i]; i++; k++;}
    while (j < n2) { vec[k] = der[i]; i++; k++;}
}

Equipo* Simulador::buscarEquipoPorID(const string& id) {
    int inicio = 0;
    int fin = equipos.size() -1;
    while (inicio <= fin){
        int mid = (inicio + fin) / 2;
        if (equipos[mid]->getId() == id) {
            return equipos[mid];
        } else if (equipos[mid]->getId() < id) {
            inicio = mid + 1;
        }else{
            fin = mid - 1;
        }
    }
    throw OperacionInconsistenteException("Equipo " + id + " no encontrado");
}

void Simulador::generarIncidencias() {
    uniform_int_distribution<int>distProbabilidad(0,99);
    uniform_int_distribution<int>distSeveridad(0,3);

    for (int i = 0; i <equipos.size(); i++) {
        if (distProbabilidad(generador) < 20) {
            Severidad sev;
            switch (distSeveridad(generador)) {
                case 0: sev = Severidad::Baja; break;
                case 1: sev = Severidad::Media; break;
                case 2: sev = Severidad::Alta; break;
                case 3: sev = Severidad::Critica; break;
            }
            stringstream s;
            s << "INC- " << diaActual << "-" << equipos[i]->getId();
            string idInc = s.str();
            Incidencia* inc = new Incidencia(idInc, equipos[i]->getId(), sev, diaActual);
            equipos[i]->agregarIncidencia(inc);
            incidencias.push_back(inc);
        }
    }
}

void Simulador::calcularRiesgoGlobal() {
    double total = 0.0;
    for (int i = 0; i < equipos.size(); i++) {
        total += equipos[i]->calcularPrioridad();
    }
    riesgoGlobal = total / equipos.size();
}

IMantenimiento* Simulador::seleccionarEstrategia(Equipo* equipo){
    if (equipo->getEstado() < 30.0 || equipo->contarIncidenciasActivas() >= 3) {
        return new MantCorrectivo();
    }
    return new MantPreventivo();
}

void Simulador::ejecutarDia() {
    diaActual++;

    stringstream sDia;
    sDia << "\n=== DIA " << diaActual << " ===\n";
    Utiles::print(sDia.str());

    //Degradacion
    for (int i = 0; i < equipos.size(); i++){
        equipos[i]->degradar();
    }

    // Nuevas Incidencias
    generarIncidencias();

    // Calcular prioridad y Ordenar
    mergeSort(equipos, 0, equipos.size() - 1);

    // Seleccionar los 3 mas urgentes
    int limite = min(3, (int)equipos.size());

    Utiles::print("3 Equipos Prioritarios:\n");
    Utiles::imprimirEncabezadoEquipos();
    for (int i = 0; i < limite; i++){
        Equipo* e = equipos[i];
        stringstream sEquipo;
        sEquipo << left
             << setw(14) << e->getId()
             << setw(12) << Utiles::formatear(e->calcularPrioridad())
             << setw(11) << Utiles::formatear(e->getEstado())
             << setw(25) << e->getTipo() << "\n";
        Utiles::print(sEquipo.str());
    }

    // Mantenimiento con Strategy y downcasting
    Utiles::print("Mantenimiento aplicado:\n");
    for (int i = 0; i < limite; i++){
        Equipo* e = equipos[i];
        IMantenimiento* estrategia = seleccionarEstrategia(e);
        estrategia->ejecutar(*e);

        stringstream sMant;
        sMant << left
              << setw(14) << e->getId()
              << setw(25) << estrategia->getNombre()
              << setw(11) << Utiles::formatear(e->getEstado())
              << setw(12) << e->contarIncidenciasActivas() << "\n";
        Utiles::print(sMant.str());

        EquipoComputo* ec = dynamic_cast<EquipoComputo*>(e);
        if (ec != nullptr){
            stringstream sEC;
            sEC << left
                << setw(14) << " "
                << "RAM: " << ec->getId()
                <<"GB: | SO: " << ec->getSistemaOperativo() << endl;
            Utiles::print(sEC.str());
        }

        EquipoLaboratorio* el = dynamic_cast<EquipoLaboratorio*>(e);
        if (el != nullptr) {
            stringstream sEL;
            sEL << left
                << setw(14) << " "
                << "Tipo: " << el->getTipo()
                <<" | Calibrado: " << (el->isCalibrado() ? "Si" : "No") << endl;
            Utiles::print(sEL.str());
        }

        delete estrategia;
    }

    // Actualizar backlog y riesgo
    backlog = equipos.size() - limite;
    calcularRiesgoGlobal();

    // Resumen del Dia
    stringstream sResumen;
    sResumen  << "Backlog pendiente: " << backlog << endl
              << "Resigo Global: " << Utiles::formatear(riesgoGlobal) << endl;
    Utiles::print(sResumen.str());
}

void Simulador::ejecutarSimulacion(){
    if (equipos.empty()) {
        throw OperacionInconsistenteException("No hay equipos registrados para simular");
    }

    Utiles::print("Iniciando simulacion de 30 dias... \n");
    for (int i = 0; i < 30 ; i++){
        ejecutarDia();
    }

    stringstream sFinal;
    sFinal << "\n=== SIMULACION COMPLETADA === \n"
           << "Riesgo Global final: " << Utiles::formatear(riesgoGlobal) << endl;
    Utiles::print(sFinal.str());
}


