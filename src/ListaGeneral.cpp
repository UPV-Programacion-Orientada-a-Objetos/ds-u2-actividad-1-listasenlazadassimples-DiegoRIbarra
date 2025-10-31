/**
 * @file ListaGeneral.cpp
 * @brief Implementación de la lista polimórfica de sensores
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#include "ListaGeneral.h"
#include <cstring>

ListaGeneral::ListaGeneral() : cabeza(nullptr) {
    std::cout << "[ListaGeneral] Sistema de gestión inicializado." << std::endl;
}

ListaGeneral::~ListaGeneral() {
    std::cout << "\n--- Liberación de Memoria en Cascada ---" << std::endl;
    
    while (cabeza != nullptr) {
        NodoSensor* temp = cabeza;
        cabeza = cabeza->siguiente;
        
        std::cout << "[Destructor General] Liberando Nodo: " << temp->sensor->getNombre() << std::endl;
        delete temp->sensor;  // Llama al destructor virtual de la clase derivada
        delete temp;
    }
    
    std::cout << "Sistema cerrado. Memoria limpia." << std::endl;
}

void ListaGeneral::insertarSensor(SensorBase* sensor) {
    NodoSensor* nuevo = new NodoSensor(sensor);
    
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        NodoSensor* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    
    std::cout << "[ListaGeneral] Sensor '" << sensor->getNombre() << "' insertado en lista de gestión." << std::endl;
}

SensorBase* ListaGeneral::buscarSensor(const char* nombre) {
    NodoSensor* actual = cabeza;
    while (actual != nullptr) {
        if (strcmp(actual->sensor->getNombre(), nombre) == 0) {
            return actual->sensor;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void ListaGeneral::procesarTodosSensores() {
    std::cout << "\n--- Ejecutando Polimorfismo ---" << std::endl;
    
    NodoSensor* actual = cabeza;
    while (actual != nullptr) {
        actual->sensor->procesarLectura();  // Polimorfismo en acción
        actual = actual->siguiente;
    }
}

void ListaGeneral::imprimirTodos() const {
    std::cout << "\n=== Estado Actual de Sensores ===" << std::endl;
    
    NodoSensor* actual = cabeza;
    int contador = 1;
    while (actual != nullptr) {
        std::cout << "\nSensor #" << contador << ":";
        actual->sensor->imprimirInfo();
        actual = actual->siguiente;
        contador++;
    }
}

bool ListaGeneral::estaVacia() const {
    return cabeza == nullptr;
}
