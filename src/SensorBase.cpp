/**
 * @file SensorBase.cpp
 * @brief Implementación de la clase base abstracta SensorBase
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#include "SensorBase.h"

SensorBase::SensorBase() {
    nombre[0] = '\0';
}

SensorBase::SensorBase(const char* nombre) {
    strncpy(this->nombre, nombre, 49);
    this->nombre[49] = '\0';
}

SensorBase::~SensorBase() {
    std::cout << "[Destructor SensorBase] Liberando sensor base." << std::endl;
}

const char* SensorBase::getNombre() const {
    return nombre;
}
