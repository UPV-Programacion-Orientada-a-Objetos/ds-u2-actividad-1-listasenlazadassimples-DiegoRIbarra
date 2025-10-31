/**
 * @file SerialReader.cpp
 * @brief Implementación de la clase de lectura desde puerto serial
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#include "SerialReader.h"
#include <cstring>

SerialReader::SerialReader() {
#ifdef WINDOWS_SERIAL
    hSerial = INVALID_HANDLE_VALUE;
    conectado = false;
#endif
}

SerialReader::~SerialReader() {
    desconectar();
}

bool SerialReader::conectar(const char* puerto) {
#ifdef WINDOWS_SERIAL
    // Abrir el puerto serial
    hSerial = CreateFileA(puerto,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "[Serial] Error al abrir puerto " << puerto << std::endl;
        return false;
    }

    // Configurar parámetros del puerto
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "[Serial] Error al obtener estado del puerto." << std::endl;
        CloseHandle(hSerial);
        return false;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "[Serial] Error al configurar puerto." << std::endl;
        CloseHandle(hSerial);
        return false;
    }

    // Configurar timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "[Serial] Error al configurar timeouts." << std::endl;
        CloseHandle(hSerial);
        return false;
    }

    conectado = true;
    std::cout << "[Serial] Conectado exitosamente a " << puerto << std::endl;
    return true;
#else
    std::cout << "[Serial] Modo simulación - puerto serial no disponible en esta plataforma." << std::endl;
    return false;
#endif
}

bool SerialReader::leerLinea(char* buffer, int maxSize) {
#ifdef WINDOWS_SERIAL
    if (!conectado) return false;

    DWORD bytesRead;
    char c;
    int i = 0;

    while (i < maxSize - 1) {
        if (!ReadFile(hSerial, &c, 1, &bytesRead, NULL)) {
            return false;
        }

        if (bytesRead == 1) {
            if (c == '\n') {
                buffer[i] = '\0';
                return true;
            }
            if (c != '\r') {
                buffer[i++] = c;
            }
        }
    }

    buffer[i] = '\0';
    return true;
#else
    return false;
#endif
}

bool SerialReader::estaConectado() const {
#ifdef WINDOWS_SERIAL
    return conectado;
#else
    return false;
#endif
}

void SerialReader::desconectar() {
#ifdef WINDOWS_SERIAL
    if (conectado) {
        CloseHandle(hSerial);
        conectado = false;
        std::cout << "[Serial] Conexión cerrada." << std::endl;
    }
#endif
}
