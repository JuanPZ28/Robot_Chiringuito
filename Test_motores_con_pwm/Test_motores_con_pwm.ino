#include <ESP32Servo.h>

//Definir pin rpm
int pinRPM= 23;
int contador= 0;
int estadoAnterior = HIGH;
// Definir pin del servomotor
int pinServo = 14;
Servo servo;

// Definir pines del sensor ultrasónico
int echo = 12;    // Receptor del sensor ultrasónico
int trigger = 13; // Emisor del sensor ultrasónico

//Pines del control pwm
int pwmMI= 26;
int pwmMD= 27;
// Pines del L298N para control de motores
int IN1 = 16;  // Motor A (rueda izquierda)
int IN2 = 17;  // Motor A (rueda izquierda)
int IN3 = 18;  // Motor B (rueda derecha)
int IN4 = 19;  // Motor B (rueda derecha)

// Configuración PWM
const int canalMI = 0;
const int canalMD = 1;
const int frecuencia = 1000;
const int resolucion = 8;  // 0-255, Cantidad de velocidades en bits, 2^8 


void setup() {
  Serial.begin(115200);

  // Configurar pines de motores como salidas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pwmMI,OUTPUT);
  pinMode(pwmMD,OUTPUT);
  pinMode(pinRPM, INPUT_PULLUP);
  // Configurar PWM
  ledcSetup(canalMI, frecuencia, resolucion);
  ledcSetup(canalMD, frecuencia, resolucion);

  ledcAttachPin(pwmMI, canalMI);
  ledcAttachPin(pwmMD, canalMD);

  Serial.println("Robot futbolito");

    // Configurar servomotor
  servo.attach(pinServo, 500, 2500);
  servo.write(0);
  delay(500);


}

void loop() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //float distancia = 0.01723 * lecturaUltrasonico(trigger, echo); // Medición de distancia en cm es bloqueante

  int estadoActual = digitalRead(pinRPM);

  // Detectar flanco HIGH -> LOW
  if (estadoAnterior == HIGH && estadoActual == LOW) {
    contador++;
    Serial.print("Pasos: ");
    Serial.println(contador);
  }

  estadoAnterior = estadoActual;

}

// ======= FUNCIONES DE MOVIMIENTO =======

void adelante() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

long lecturaUltrasonico(int trigger, int echo) {
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH); // Devuelve el tiempo en microsegundos
}








