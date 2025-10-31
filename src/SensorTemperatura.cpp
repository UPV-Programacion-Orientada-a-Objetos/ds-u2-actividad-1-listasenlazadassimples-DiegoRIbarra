/**
 * @file SensorTemperatura.cpp
 * @brief Implementación del sensor de temperatura
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#include "SensorTemperatura.h"

SensorTemperatura::SensorTemperatura(const char* nombre) : SensorBase(nombre) {
    std::cout << "[Sensor Temperatura] Sensor '" << nombre << "' creado." << std::endl;
}

SensorTemperatura::~SensorTemperatura() {
    std::cout << "[Destructor Sensor " << nombre << "] Liberando Lista Interna..." << std::endl;
    // El destructor de ListaSensor<float> se llama automáticamente
}

void SensorTemperatura::registrarLectura(float valor) {
    historial.insertarAlFinal(valor);
}

void SensorTemperatura::procesarLectura() {
    std::cout << "\n-> Procesando Sensor " << nombre << "..." << std::endl;
    
    if (historial.estaVacia()) {
        std::cout << "[Sensor Temp] No hay lecturas para procesar." << std::endl;
        return;
    }

    // Eliminar el valor más bajo
    float masBajo = historial.eliminarMasBajo();
    std::cout << "[Sensor Temp] Lectura más baja (" << masBajo << ") eliminada." << std::endl;

    // Calcular promedio de las lecturas restantes
    if (!historial.estaVacia()) {
        float promedio = historial.calcularPromedio();
        std::cout << "[Sensor Temp] Promedio restante: " << promedio << std::endl;
    } else {
        std::cout << "[Sensor Temp] No quedan lecturas después de eliminar la más baja." << std::endl;
    }
}

void SensorTemperatura::imprimirInfo() const {
    std::cout << "\n[" << nombre << "] (Temperatura - FLOAT)" << std::endl;
    std::cout << "Lecturas actuales (" << historial.getTamanio() << "): ";
    historial.imprimir();
}
