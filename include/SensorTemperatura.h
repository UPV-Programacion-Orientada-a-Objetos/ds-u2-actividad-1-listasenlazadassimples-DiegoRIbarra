/**
 * @file SensorTemperatura.h
 * @brief Sensor de temperatura que maneja lecturas de tipo float
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @brief Clase derivada que representa un sensor de temperatura
 * 
 * Este sensor maneja lecturas de tipo float y almacena el historial
 * de mediciones en una lista enlazada genérica.
 */
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> historial;   ///< Lista de lecturas de temperatura

public:
    /**
     * @brief Constructor con nombre del sensor
     * @param nombre Identificador del sensor de temperatura
     */
    SensorTemperatura(const char* nombre);

    /**
     * @brief Destructor que libera la lista de historial
     */
    ~SensorTemperatura() override;

    /**
     * @brief Registra una nueva lectura de temperatura
     * @param valor Valor de temperatura en grados
     */
    void registrarLectura(float valor);

    /**
     * @brief Procesa las lecturas eliminando el valor más bajo y calculando promedio
     * 
     * Implementación del método virtual puro de SensorBase
     */
    void procesarLectura() override;

    /**
     * @brief Imprime la información del sensor y su historial
     * 
     * Implementación del método virtual puro de SensorBase
     */
    void imprimirInfo() const override;
};

#endif // SENSOR_TEMPERATURA_H
