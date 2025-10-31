cmake_minimum_required(VERSION 3.10)
project(SistemaIoTSensores VERSION 1.0)

# Configurar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorios de cabeceras
include_directories(include)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/SensorBase.cpp
    src/SensorTemperatura.cpp
    src/SensorPresion.cpp
    src/ListaGeneral.cpp
    src/SerialReader.cpp
)

# Crear el ejecutable
add_executable(SistemaIoTSensores ${SOURCES})

# Para Windows, agregar soporte de puerto serial
if(WIN32)
    target_compile_definitions(SistemaIoTSensores PRIVATE WINDOWS_SERIAL)
endif()

# Configuración de instalación
install(TARGETS SistemaIoTSensores DESTINATION bin)
