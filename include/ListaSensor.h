/**
 * @file ListaSensor.h
 * @brief Implementación de Lista Enlazada Simple Genérica para sensores IoT
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 */

#ifndef LISTA_SENSOR_H
#define LISTA_SENSOR_H

#include <iostream>

/**
 * @brief Estructura de Nodo genérico para la lista enlazada
 * @tparam T Tipo de dato a almacenar en el nodo
 */
template <typename T>
struct Nodo {
    T dato;                 ///< Dato almacenado en el nodo
    Nodo<T>* siguiente;     ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor del nodo
     * @param valor Valor a almacenar en el nodo
     */
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

/**
 * @brief Clase de Lista Enlazada Simple Genérica
 * @tparam T Tipo de dato a almacenar en la lista
 * 
 * Esta clase implementa una lista enlazada simple genérica con
 * gestión manual de memoria mediante punteros.
 */
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza;        ///< Puntero al primer nodo de la lista
    int tamanio;            ///< Número de elementos en la lista

public:
    /**
     * @brief Constructor por defecto
     */
    ListaSensor() : cabeza(nullptr), tamanio(0) {
        std::cout << "[Log] ListaSensor creada." << std::endl;
    }

    /**
     * @brief Destructor - Libera toda la memoria de la lista
     */
    ~ListaSensor() {
        std::cout << "[Log] Liberando ListaSensor..." << std::endl;
        liberarTodo();
    }

    /**
     * @brief Constructor de copia (Regla de los Tres)
     * @param otra Lista a copiar
     */
    ListaSensor(const ListaSensor& otra) : cabeza(nullptr), tamanio(0) {
        Nodo<T>* actual = otra.cabeza;
        while (actual != nullptr) {
            insertarAlFinal(actual->dato);
            actual = actual->siguiente;
        }
    }

    /**
     * @brief Operador de asignación (Regla de los Tres)
     * @param otra Lista a asignar
     * @return Referencia a esta lista
     */
    ListaSensor& operator=(const ListaSensor& otra) {
        if (this != &otra) {
            liberarTodo();
            Nodo<T>* actual = otra.cabeza;
            while (actual != nullptr) {
                insertarAlFinal(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;
    }

    /**
     * @brief Inserta un elemento al final de la lista
     * @param valor Valor a insertar
     */
    void insertarAlFinal(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        std::cout << "[Log] Insertando Nodo<T> con valor: " << valor << std::endl;
        
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        tamanio++;
    }

    /**
     * @brief Busca un valor en la lista
     * @param valor Valor a buscar
     * @return true si el valor existe, false en caso contrario
     */
    bool buscar(T valor) const {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato == valor) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    /**
     * @brief Calcula el promedio de los elementos (requiere tipo numérico)
     * @return Promedio de los elementos
     */
    T calcularPromedio() const {
        if (tamanio == 0) return static_cast<T>(0);
        
        T suma = static_cast<T>(0);
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            suma += actual->dato;
            actual = actual->siguiente;
        }
        return suma / static_cast<T>(tamanio);
    }

    /**
     * @brief Encuentra y elimina el valor más bajo de la lista
     * @return Valor más bajo que fue eliminado
     */
    T eliminarMasBajo() {
        if (cabeza == nullptr) {
            return static_cast<T>(0);
        }

        // Encontrar el valor más bajo
        Nodo<T>* actual = cabeza;
        T minimo = cabeza->dato;
        while (actual != nullptr) {
            if (actual->dato < minimo) {
                minimo = actual->dato;
            }
            actual = actual->siguiente;
        }

        // Eliminar el primer nodo con el valor mínimo
        if (cabeza->dato == minimo) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            std::cout << "[Log] Nodo<T> " << temp->dato << " liberado." << std::endl;
            delete temp;
            tamanio--;
        } else {
            Nodo<T>* anterior = cabeza;
            actual = cabeza->siguiente;
            while (actual != nullptr && actual->dato != minimo) {
                anterior = actual;
                actual = actual->siguiente;
            }
            if (actual != nullptr) {
                anterior->siguiente = actual->siguiente;
                std::cout << "[Log] Nodo<T> " << actual->dato << " liberado." << std::endl;
                delete actual;
                tamanio--;
            }
        }

        return minimo;
    }

    /**
     * @brief Obtiene el tamaño de la lista
     * @return Número de elementos en la lista
     */
    int getTamanio() const {
        return tamanio;
    }

    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool estaVacia() const {
        return cabeza == nullptr;
    }

    /**
     * @brief Imprime todos los elementos de la lista
     */
    void imprimir() const {
        Nodo<T>* actual = cabeza;
        std::cout << "[ ";
        while (actual != nullptr) {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        std::cout << "]" << std::endl;
    }

private:
    /**
     * @brief Libera toda la memoria de la lista
     */
    void liberarTodo() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            std::cout << "[Log] Nodo<T> " << temp->dato << " liberado." << std::endl;
            delete temp;
        }
        tamanio = 0;
    }
};

#endif // LISTA_SENSOR_H
