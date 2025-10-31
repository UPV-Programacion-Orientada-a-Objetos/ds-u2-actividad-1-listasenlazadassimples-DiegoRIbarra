/**
 * @file ListaGeneral.h
 * @brief Lista enlazada NO genérica para gestión polimórfica de sensores
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#ifndef LISTA_GENERAL_H
#define LISTA_GENERAL_H

#include "SensorBase.h"
#include <iostream>

/**
 * @brief Nodo para la lista de gestión polimórfica
 */
struct NodoSensor {
    SensorBase* sensor;         ///< Puntero a la clase base (polimorfismo)
    NodoSensor* siguiente;      ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param s Puntero al sensor
     */
    NodoSensor(SensorBase* s) : sensor(s), siguiente(nullptr) {}
};

/**
 * @brief Lista enlazada para gestión polimórfica de sensores
 * 
 * Esta lista almacena punteros a la clase base SensorBase*,
 * permitiendo almacenar diferentes tipos de sensores en una única estructura.
 */
class ListaGeneral {
private:
    NodoSensor* cabeza;     ///< Puntero al primer nodo

public:
    /**
     * @brief Constructor por defecto
     */
    ListaGeneral();

    /**
     * @brief Destructor - Libera toda la memoria incluyendo los sensores
     */
    ~ListaGeneral();

    /**
     * @brief Inserta un sensor al final de la lista
     * @param sensor Puntero al sensor a insertar
     */
    void insertarSensor(SensorBase* sensor);

    /**
     * @brief Busca un sensor por su nombre
     * @param nombre Nombre del sensor a buscar
     * @return Puntero al sensor encontrado o nullptr si no existe
     */
    SensorBase* buscarSensor(const char* nombre);

    /**
     * @brief Procesa todos los sensores de la lista polimórficamente
     */
    void procesarTodosSensores();

    /**
     * @brief Imprime información de todos los sensores
     */
    void imprimirTodos() const;

    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const;
};

#endif // LISTA_GENERAL_H
