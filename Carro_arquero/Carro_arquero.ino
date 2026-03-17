#include <ESP32Servo.h>
#include <NewPing.h>

//Definir pin rpm
int pinRPM= 23;
int contador= 0;
int estadoAnterior = HIGH;


// Definir pines del sensor ultrasónico
int echo = 12;    
int trigger = 13;
int distancia_maxima =200;
 
NewPing sensor_1(trigger, echo, distancia_maxima); 

//Pines del control pwm
int pwmMI= 26;
int pwmMD= 27;


// Pines del L298N para control de motores
int IN1 = 16;
int IN2 = 17;
int IN3 = 18;
int IN4 = 19;

// Configuración PWM
const int canalMI = 0;
const int canalMD = 1;
const int frecuencia = 1000;
const int resolucion = 8;


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

  // PWM nuevo ESP32
  ledcAttach(pwmMI, frecuencia, resolucion);
  ledcAttach(pwmMD, frecuencia, resolucion);

  Serial.println("Robot futbolito");

}

void loop() {

  Serial.print("distancia del sensor: ");
  Serial.print(sensor_1.ping_cm());
  Serial.println("cm");

  // velocidad motores
  ledcWrite(pwmMD, 200);
  ledcWrite(pwmMI, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  int estadoActual = digitalRead(pinRPM);

  if (estadoAnterior == HIGH && estadoActual == LOW) {
    contador++;
    Serial.print("Pasos: ");
    Serial.println(contador);
  }

  estadoAnterior = estadoActual;
}

// ======= FUNCIONES DE MOVIMIENTO =======

void adelante() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
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

  return pulseIn(echo, HIGH);
}