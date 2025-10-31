/**
 * @file SensorPresion.h
 * @brief Sensor de presión que maneja lecturas de tipo int
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @brief Clase derivada que representa un sensor de presión
 * 
 * Este sensor maneja lecturas de tipo int y almacena el historial
 * de mediciones en una lista enlazada genérica.
 */
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> historial;     ///< Lista de lecturas de presión

public:
    /**
     * @brief Constructor con nombre del sensor
     * @param nombre Identificador del sensor de presión
     */
    SensorPresion(const char* nombre);

    /**
     * @brief Destructor que libera la lista de historial
     */
    ~SensorPresion() override;

    /**
     * @brief Registra una nueva lectura de presión
     * @param valor Valor de presión
     */
    void registrarLectura(int valor);

    /**
     * @brief Procesa las lecturas calculando el promedio
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

#endif // SENSOR_PRESION_H
