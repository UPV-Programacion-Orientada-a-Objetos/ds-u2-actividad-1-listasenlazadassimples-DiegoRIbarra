/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los sensores del sistema IoT
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <cstring>
#include <iostream>

/**
 * @brief Clase base abstracta que define la interfaz común para todos los sensores
 * 
 * Esta clase utiliza métodos virtuales puros para forzar la implementación
 * de procesamiento y visualización en las clases derivadas.
 */
class SensorBase {
protected:
    char nombre[50];    ///< Identificador único del sensor

public:
    /**
     * @brief Constructor por defecto
     */
    SensorBase();

    /**
     * @brief Constructor con nombre del sensor
     * @param nombre Identificador del sensor
     */
    SensorBase(const char* nombre);

    /**
     * @brief Destructor virtual para garantizar liberación correcta en polimorfismo
     */
    virtual ~SensorBase();

    /**
     * @brief Método virtual puro para procesar las lecturas del sensor
     * 
     * Cada tipo de sensor debe implementar su propia lógica de procesamiento
     */
    virtual void procesarLectura() = 0;

    /**
     * @brief Método virtual puro para imprimir información del sensor
     * 
     * Cada tipo de sensor debe implementar su propia forma de mostrar información
     */
    virtual void imprimirInfo() const = 0;

    /**
     * @brief Obtiene el nombre del sensor
     * @return Puntero al nombre del sensor
     */
    const char* getNombre() const;
};

#endif // SENSOR_BASE_H
