/**
 * @file SerialReader.h
 * @brief Clase para lectura de datos desde puerto serial (Arduino)
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#ifndef SERIAL_READER_H
#define SERIAL_READER_H

#ifdef WINDOWS_SERIAL
#include <windows.h>
#endif

#include <iostream>

/**
 * @brief Clase para comunicación con dispositivo Arduino mediante puerto serial
 * 
 * Esta clase permite leer datos enviados desde un Arduino conectado
 * al puerto serial de la computadora.
 */
class SerialReader {
private:
#ifdef WINDOWS_SERIAL
    HANDLE hSerial;             ///< Handle del puerto serial en Windows
    bool conectado;             ///< Estado de conexión
#endif

public:
    /**
     * @brief Constructor por defecto
     */
    SerialReader();

    /**
     * @brief Destructor que cierra la conexión
     */
    ~SerialReader();

    /**
     * @brief Conecta con el puerto serial especificado
     * @param puerto Nombre del puerto (ej: "COM3")
     * @return true si la conexión fue exitosa
     */
    bool conectar(const char* puerto);

    /**
     * @brief Lee una línea de datos desde el puerto serial
     * @param buffer Buffer donde se almacenará la línea leída
     * @param maxSize Tamaño máximo del buffer
     * @return true si se leyó correctamente
     */
    bool leerLinea(char* buffer, int maxSize);

    /**
     * @brief Verifica si hay conexión activa
     * @return true si está conectado
     */
    bool estaConectado() const;

    /**
     * @brief Cierra la conexión con el puerto serial
     */
    void desconectar();
};

#endif // SERIAL_READER_H
