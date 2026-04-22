#include "Simulador.h"
#include "EquipoComputo.h"
#include "EquipoLaboratorio.h"
#include <random>
#include <sstream>
using namespace std;

Simulador::Simulador() : diaActual(0), backlog(0), riesgoGlobal(0.0),
    generador(random_device{}()) {
    reporte  = new Reporte("reporte_diario.txt", "reporte_acumulado.txt");
    reporte->abrirArchivos();
    interfaz = new InterfazConsola();
}

Simulador::~Simulador() {
    delete reporte;
    delete interfaz;
    for (int i = 0; i < equipos.size(); i++) {
        delete equipos[i];
    }
    for (int i = 0; i < incidencias.size(); i++) {
        delete incidencias[i];
    }
}

void Simulador::agregarEquipo(Equipo* equipo) {
    if (equipo == nullptr) {
        throw OperacionInconsistenteException("No se puede agregar un equipo nulo");
    }
    equipos.push_back(equipo);
}

void Simulador::merge(vector<Equipo*>& vec, int inicio, int mid, int fin) {
    int n1 = mid - inicio + 1;
    int n2 = fin - mid;

    vector<Equipo*> izq(n1);
    vector<Equipo*> der(n2);

    for (int i = 0; i < n1; i++) {
        izq[i] = vec[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        der[j] = vec[mid + 1 + j];
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (izq[i]->calcularPrioridad() >= der[j]->calcularPrioridad()) {
            vec[k] = izq[i];
            i++;
        } else {
            vec[k] = der[j];
            j++;
        }
        k++;
    }

    while (i < n1) { vec[k] = izq[i]; i++; k++; }
    while (j < n2) { vec[k] = der[j]; j++; k++; }
}

void Simulador::mergeSort(vector<Equipo*>& vec, int inicio, int fin) {
    if (inicio < fin) {
        int mid = (inicio + fin) / 2;
        mergeSort(vec, inicio, mid);
        mergeSort(vec, mid + 1, fin);
        merge(vec, inicio, mid, fin);
    }
}

Equipo* Simulador::buscarEquipoPorID(const string& id) {
    int inicio = 0;
    int fin = equipos.size() - 1;
    while (inicio <= fin) {
        int mid = (inicio + fin) / 2;
        if (equipos[mid]->getId() == id) {
            return equipos[mid];
        } else if (equipos[mid]->getId() < id) {
            inicio = mid + 1;
        } else {
            fin = mid - 1;
        }
    }
    throw OperacionInconsistenteException("Equipo " + id + " no encontrado");
}

void Simulador::generarIncidencias() {
    uniform_int_distribution<int> distProbabilidad(0, 99);
    uniform_int_distribution<int> distSeveridad(0, 3);

    for (int i = 0; i < equipos.size(); i++) {
        if (distProbabilidad(generador) < 20) {
            Severidad sev;
            switch (distSeveridad(generador)) {
                case 0:  sev = Severidad::Baja;    break;
                case 1:  sev = Severidad::Media;   break;
                case 2:  sev = Severidad::Alta;    break;
                case 3:  sev = Severidad::Critica; break;
                default: sev = Severidad::Baja;    break;
            }
            stringstream ss;
            ss << "INC-" << diaActual << "-" << equipos[i]->getId();
            string idInc = ss.str();
            Incidencia* inc = new Incidencia(idInc, equipos[i]->getId(), sev, diaActual);
            equipos[i]->agregarIncidencia(inc);
            incidencias.push_back(inc);
        }
    }
}

void Simulador::calcularRiesgoGlobal() {
    int criticos = 0;
    for (int i = 0; i < equipos.size(); i++) {
        if (equipos[i]->getEstado() < 30.0) criticos++;
    }
    riesgoGlobal = (criticos * 100.0) / equipos.size();
}

string Simulador::nivelRiesgo() const {
    if (riesgoGlobal <= 10.0) return "BAJO";
    if (riesgoGlobal <= 20.0) return "MEDIO";
    if (riesgoGlobal <= 35.0) return "ALTO";
    return "CRITICO";
}

IMantenimiento* Simulador::seleccionarEstrategia(Equipo* equipo) {
    if (equipo->getEstado() < 20.0 || equipo->contarIncidenciasActivas() >= 5) {
        return new MantCorrectivo();
    }
    return new MantPreventivo();
}

void Simulador::ejecutarDia() {
    diaActual++;
    interfaz->mostrarDia(diaActual);

    // Degradacion
    for (int i = 0; i < equipos.size(); i++) {
        equipos[i]->degradar();
    }

    // Nuevas incidencias
    generarIncidencias();

    // Calcular prioridad y ordenar
    mergeSort(equipos, 0, equipos.size() - 1);

    //Seleccionar top 3
    int limite = min(3, (int)equipos.size());
    interfaz->mostrarTopPrioridad(equipos, limite);

    // Mantenimiento
    interfaz->mostrarEncabezadoMantenimiento();
    for (int i = 0; i < limite; i++) {
        Equipo* e = equipos[i];
        IMantenimiento* estrategia = seleccionarEstrategia(e);
        estrategia->ejecutar(*e);
        interfaz->mostrarFilaMantenimiento(e, estrategia->getNombre());
        interfaz->mostrarDetalleEquipo(e);
        delete estrategia;
    }

    // Actualizar backlog y riesgo
    backlog = equipos.size() - limite;
    calcularRiesgoGlobal();

    // Resumen del dia
    interfaz->mostrarResumenDia(backlog, riesgoGlobal, nivelRiesgo());
    reporte->registrarDia(diaActual, equipos, limite, backlog, riesgoGlobal);
}

void Simulador::ejecutarSimulacion() {
    if (equipos.empty()) {
        throw OperacionInconsistenteException("No hay equipos registrados para simular");
    }

    interfaz->mostrarIniciSimulacion();
    for (int i = 0; i < 30; i++) {
        ejecutarDia();
    }

    reporte->registrarResumenFinal(30, riesgoGlobal);
    interfaz->mostrarSimulacionCompletada(riesgoGlobal, nivelRiesgo());
}