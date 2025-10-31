/**
 * @file main.cpp
 * @brief Programa principal del Sistema IoT de Monitoreo Polimórfico
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#include <iostream>
#include <cstring>
#include "ListaGeneral.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "SerialReader.h"

using namespace std;

/**
 * @brief Muestra el menú principal del sistema
 */
void mostrarMenu() {
    cout << "\n========================================" << endl;
    cout << "  Sistema IoT de Monitoreo Polimorfico" << endl;
    cout << "========================================" << endl;
    cout << "1. Crear Sensor de Temperatura (FLOAT)" << endl;
    cout << "2. Crear Sensor de Presión (INT)" << endl;
    cout << "3. Registrar Lectura Manual" << endl;
    cout << "4. Leer desde Puerto Serial (Arduino)" << endl;
    cout << "5. Ejecutar Procesamiento Polimórfico" << endl;
    cout << "6. Mostrar Estado de Sensores" << endl;
    cout << "7. Cerrar Sistema (Liberar Memoria)" << endl;
    cout << "Opcion: ";
}

/**
 * @brief Crea un sensor de temperatura
 * @param lista Lista general de sensores
 */
void crearSensorTemperatura(ListaGeneral& lista) {
    char nombre[50];
    cout << "\nNombre del sensor (ej: T-001): ";
    cin >> nombre;
    
    SensorTemperatura* sensor = new SensorTemperatura(nombre);
    lista.insertarSensor(sensor);
}

/**
 * @brief Crea un sensor de presión
 * @param lista Lista general de sensores
 */
void crearSensorPresion(ListaGeneral& lista) {
    char nombre[50];
    cout << "\nNombre del sensor (ej: P-105): ";
    cin >> nombre;
    
    SensorPresion* sensor = new SensorPresion(nombre);
    lista.insertarSensor(sensor);
}

/**
 * @brief Registra una lectura manual en un sensor
 * @param lista Lista general de sensores
 */
void registrarLecturaManual(ListaGeneral& lista) {
    char nombre[50];
    cout << "\nID del sensor: ";
    cin >> nombre;
    
    SensorBase* sensor = lista.buscarSensor(nombre);
    if (sensor == nullptr) {
        cout << "Error: Sensor no encontrado." << endl;
        return;
    }
    
    cout << "Tipo (T=Temperatura, P=Presión): ";
    char tipo;
    cin >> tipo;
    
    if (tipo == 'T' || tipo == 't') {
        float valor;
        cout << "Valor (float): ";
        cin >> valor;
        
        SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
        if (sensorTemp) {
            sensorTemp->registrarLectura(valor);
            cout << "Lectura registrada en " << nombre << endl;
        } else {
            cout << "Error: El sensor no es de tipo Temperatura." << endl;
        }
    } else if (tipo == 'P' || tipo == 'p') {
        int valor;
        cout << "Valor (int): ";
        cin >> valor;
        
        SensorPresion* sensorPres = dynamic_cast<SensorPresion*>(sensor);
        if (sensorPres) {
            sensorPres->registrarLectura(valor);
            cout << "Lectura registrada en " << nombre << endl;
        } else {
            cout << "Error: El sensor no es de tipo Presión." << endl;
        }
    }
}

/**
 * @brief Lee datos desde el puerto serial
 * @param lista Lista general de sensores
 */
void leerDesdeSerial(ListaGeneral& lista) {
    char puerto[10];
    cout << "\nPuerto COM (ej: COM3): ";
    cin >> puerto;
    
    SerialReader serial;
    if (!serial.conectar(puerto)) {
        cout << "No se pudo conectar al puerto serial." << endl;
        cout << "Ejecutando en modo simulación..." << endl;
        
        // Datos de simulación
        cout << "\n[Simulación] Creando sensores de prueba..." << endl;
        SensorTemperatura* t1 = new SensorTemperatura("T-001");
        t1->registrarLectura(45.3f);
        t1->registrarLectura(42.1f);
        lista.insertarSensor(t1);
        
        SensorPresion* p1 = new SensorPresion("P-105");
        p1->registrarLectura(80);
        p1->registrarLectura(85);
        lista.insertarSensor(p1);
        
        return;
    }
    
    cout << "Leyendo datos del Arduino (presione Ctrl+C para detener)..." << endl;
    cout << "Formato esperado: TIPO,ID,VALOR (ej: T,T-001,25.5)" << endl;
    
    char buffer[100];
    int lecturas = 0;
    
    while (lecturas < 10 && serial.leerLinea(buffer, 100)) {
        // Parsear: TIPO,ID,VALOR
        char* tipo = strtok(buffer, ",");
        char* id = strtok(nullptr, ",");
        char* valor = strtok(nullptr, ",");
        
        if (tipo && id && valor) {
            SensorBase* sensor = lista.buscarSensor(id);
            
            if (tipo[0] == 'T' || tipo[0] == 't') {
                if (!sensor) {
                    sensor = new SensorTemperatura(id);
                    lista.insertarSensor(sensor);
                }
                SensorTemperatura* sensorTemp = dynamic_cast<SensorTemperatura*>(sensor);
                if (sensorTemp) {
                    sensorTemp->registrarLectura(atof(valor));
                    cout << "[Arduino] " << id << ": " << valor << "°C" << endl;
                    lecturas++;
                }
            } else if (tipo[0] == 'P' || tipo[0] == 'p') {
                if (!sensor) {
                    sensor = new SensorPresion(id);
                    lista.insertarSensor(sensor);
                }
                SensorPresion* sensorPres = dynamic_cast<SensorPresion*>(sensor);
                if (sensorPres) {
                    sensorPres->registrarLectura(atoi(valor));
                    cout << "[Arduino] " << id << ": " << valor << " Pa" << endl;
                    lecturas++;
                }
            }
        }
    }
    
    cout << "\nTotal de lecturas capturadas: " << lecturas << endl;
}

/**
 * @brief Función principal
 */
int main() {
    ListaGeneral sistema;
    int opcion;
    
    cout << "==================================================" << endl;
    cout << "  Sistema de Gestión Polimórfica de Sensores IoT" << endl;
    cout << "  Listas Enlazadas Simples + Polimorfismo" << endl;
    cout << "==================================================" << endl;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                crearSensorTemperatura(sistema);
                break;
            case 2:
                crearSensorPresion(sistema);
                break;
            case 3:
                registrarLecturaManual(sistema);
                break;
            case 4:
                leerDesdeSerial(sistema);
                break;
            case 5:
                cout << "\n--- Opción 4: Ejecutar Procesamiento Polimórfico ---" << endl;
                sistema.procesarTodosSensores();
                break;
            case 6:
                sistema.imprimirTodos();
                break;
            case 7:
                cout << "\n--- Opción 5: Cerrar Sistema (Liberar Memoria) ---" << endl;
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
        }
        
    } while (opcion != 7);
    
    // El destructor de ListaGeneral liberará toda la memoria automáticamente
    return 0;
}
