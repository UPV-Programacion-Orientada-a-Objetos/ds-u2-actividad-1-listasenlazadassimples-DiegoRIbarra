/**
 * @file SensorPresion.cpp
 * @brief Implementación del sensor de presión
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#include "SensorPresion.h"

SensorPresion::SensorPresion(const char* nombre) : SensorBase(nombre) {
    std::cout << "[Sensor Presion] Sensor '" << nombre << "' creado." << std::endl;
}

SensorPresion::~SensorPresion() {
    std::cout << "[Destructor Sensor " << nombre << "] Liberando Lista Interna..." << std::endl;
    // El destructor de ListaSensor<int> se llama automáticamente
}

void SensorPresion::registrarLectura(int valor) {
    historial.insertarAlFinal(valor);
}

void SensorPresion::procesarLectura() {
    std::cout << "\n-> Procesando Sensor " << nombre << "..." << std::endl;
    
    if (historial.estaVacia()) {
        std::cout << "[Sensor Presion] No hay lecturas para procesar." << std::endl;
        return;
    }

    // Calcular promedio
    int promedio = historial.calcularPromedio();
    std::cout << "[Sensor Presion] Promedio de lecturas: " << promedio << std::endl;
    std::cout << "[Sensor Presion] Total de lecturas: " << historial.getTamanio() << std::endl;
}

void SensorPresion::imprimirInfo() const {
    std::cout << "\n[" << nombre << "] (Presion - INT)" << std::endl;
    std::cout << "Lecturas actuales (" << historial.getTamanio() << "): ";
    historial.imprimir();
}
