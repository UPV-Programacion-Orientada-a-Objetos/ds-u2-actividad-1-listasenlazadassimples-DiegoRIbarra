#!/bin/bash

echo "================================================"
echo "  Sistema IoT - Script de Compilación"
echo "================================================"

# Limpiar build anterior
if [ -d "build" ]; then
    echo "Limpiando directorio build anterior..."
    rm -rf build
fi

# Crear directorio build
echo "Creando directorio build..."
mkdir build
cd build

# Ejecutar CMake
echo "Ejecutando CMake..."
cmake ..

# Compilar el proyecto
echo "Compilando el proyecto..."
cmake --build .

echo ""
echo "================================================"
echo "  Compilación completada!"
echo "================================================"
echo ""
echo "Para ejecutar el programa:"
echo "  cd build"
echo "  ./SistemaIoTSensores"
echo ""
