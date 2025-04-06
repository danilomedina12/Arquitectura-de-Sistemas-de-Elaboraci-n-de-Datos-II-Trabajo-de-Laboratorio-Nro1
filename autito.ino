#include <NewPing.h>

// Pines del sensor HC-SR04
#define TRIG_PIN 10
#define ECHO_PIN 11
// Parámetros del sensor
#define DISTANCIA_MAX_SENSOR 200
#define DISTANCIA_DE_GIRO 15

// Pines del Puente H (motores)
#define DELAN_IN1 3
#define DELAN_IN2 5
#define DELAN_IN3 6
#define DELAN_IN4 9

NewPing sonar(TRIG_PIN, ECHO_PIN, DISTANCIA_MAX_SENSOR);

void setup() {
  // Configurar pines como salidas
  pinMode(DELAN_IN1, OUTPUT);
  pinMode(DELAN_IN2, OUTPUT);
  pinMode(DELAN_IN3, OUTPUT);
  pinMode(DELAN_IN4, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (obtenerDistancia() < DISTANCIA_DE_GIRO) {
    avanzar();
  }
  else {
    girarSentidoHorario();
    delay(300); // Ajustar tiempo de giro
  }
  delay(50);
}
// Funciones Auxiliares:

void avanzar() {
  girarRuedasIzquierdas(false);
  girarRuedasDerechas(false);
}

void girarSentidoHorario() {
  girarRuedasDerechas(false);
  girarRuedasIzquierdas(true);
}

void aplicarEstadoMotor(int motor, bool high) {
  analogWrite(motor, high ? 128 : 0);
}

// Funciones para control de motores

void girarRuedasIzquierdas(bool enReversa) {
  aplicarEstadoMotor(DELAN_IN1, enReversa);
  aplicarEstadoMotor(DELAN_IN2, !enReversa);
}
void girarRuedasDerechas(bool enReversa) {
  aplicarEstadoMotor(DELAN_IN3, !enReversa);
  aplicarEstadoMotor(DELAN_IN4, enReversa);
}

void imprimirPorLineas(int valor) {
  Serial.print(valor);
  Serial.println("\n");
}

int obtenerDistancia() {
  int distancia = sonar.ping_cm();
  if (distancia == 0) distancia = DISTANCIA_MAX_SENSOR;
  imprimirPorLineas(distancia);
  return distancia; 
}
