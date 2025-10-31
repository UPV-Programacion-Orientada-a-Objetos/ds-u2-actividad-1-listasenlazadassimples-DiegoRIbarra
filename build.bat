@echo off
echo ================================================
echo   Sistema IoT - Script de Compilacion
echo ================================================

REM Verificar si existe el directorio build
if exist build (
    echo Limpiando directorio build anterior...
    rmdir /s /q build
)

REM Crear directorio build
echo Creando directorio build...
mkdir build
cd build

REM Ejecutar CMake
echo Ejecutando CMake...
cmake ..

REM Compilar el proyecto
echo Compilando el proyecto...
cmake --build .

echo.
echo ================================================
echo   Compilacion completada!
echo ================================================
echo.
echo Para ejecutar el programa:
echo   cd build
echo   Debug\SistemaIoTSensores.exe    (MSVC)
echo   SistemaIoTSensores.exe          (MinGW)
echo.

pause
