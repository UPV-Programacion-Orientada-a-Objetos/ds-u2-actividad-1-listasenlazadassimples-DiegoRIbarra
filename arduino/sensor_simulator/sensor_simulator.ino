/**
 * @file sensor_simulator.ino
 * @brief Simulador de sensores IoT para Arduino
 * @author Diego Ibarra
 * @date 30 de octubre de 2025
 * 
 * Este programa simula el envío de lecturas de sensores de temperatura
 * y presión a través del puerto serial.
 * 
 * Formato de salida: TIPO,ID,VALOR
 * Ejemplos:
 *   T,T-001,25.5  (Temperatura)
 *   P,P-105,80    (Presión)
 */

// Configuración
const int BAUDRATE = 9600;
const int DELAY_LECTURA = 2000; // 2 segundos entre lecturas

// Variables para simulación
float temperaturaBase = 20.0;
int presionBase = 75;

void setup() {
  // Inicializar comunicación serial
  Serial.begin(BAUDRATE);
  
  // Inicializar generador de números aleatorios
  randomSeed(analogRead(0));
  
  // Mensaje de inicio
  delay(1000);
  Serial.println("# Sistema de Sensores IoT Iniciado");
  Serial.println("# Formato: TIPO,ID,VALOR");
  Serial.println("# T = Temperatura (°C), P = Presión (Pa)");
}

void loop() {
  // Simular lectura de temperatura
  float temperatura = temperaturaBase + random(-50, 50) / 10.0;
  Serial.print("T,T-001,");
  Serial.println(temperatura, 1);
  
  delay(DELAY_LECTURA);
  
  // Simular otra lectura de temperatura
  temperatura = temperaturaBase + random(-30, 70) / 10.0;
  Serial.print("T,T-002,");
  Serial.println(temperatura, 1);
  
  delay(DELAY_LECTURA);
  
  // Simular lectura de presión
  int presion = presionBase + random(-10, 15);
  Serial.print("P,P-105,");
  Serial.println(presion);
  
  delay(DELAY_LECTURA);
  
  // Simular otra lectura de presión
  presion = presionBase + random(-5, 20);
  Serial.print("P,P-106,");
  Serial.println(presion);
  
  delay(DELAY_LECTURA);
}
