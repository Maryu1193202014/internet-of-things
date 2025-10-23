
const int TRIG_PIN = 9;  
const int ECHO_PIN = 10; 


const int LED_VERDE = 5;    // LED verde - Nivel seguro
const int LED_AMARILLO = 6; // LED amarillo - Alerta media
const int LED_ROJO = 7;     // LED rojo - Nivel peligroso

// Variables para la medición
long duracion;
float distancia;

// Umbrales de distancia en centímetros
const float UMBRAL_PELIGRO = 8.0;   // Menor a 8 cm = peligro
const float UMBRAL_ALERTA = 15.0;   // Entre 8-15 cm = alerta

void setup() {
  
  // Inicializar comunicación serial para monitoreo
  Serial.begin(9600);
  Serial.println("Sistema de Detección de Nivel de Agua");
  Serial.println("=====================================");
  
  // Configurar pines del sensor HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Configurar pines de los LEDs como salidas
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  
  // Apagar todos los LEDs al inicio
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
  
  delay(1000); // Espera inicial de 1 segundo
}

void loop() {
  // Medir distancia con el sensor ultrasónico
  distancia = medirDistancia();
  
  // Mostrar la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print(" cm - ");
  
  // Evaluar nivel de agua y activar LED correspondiente
  if (distancia < UMBRAL_PELIGRO) {
    // NIVEL PELIGROSO - Agua muy cerca
    activarLED(LED_ROJO);
    Serial.println("¡PELIGRO! Nivel de agua ALTO");
  } 
  else if (distancia >= UMBRAL_PELIGRO && distancia < UMBRAL_ALERTA) {
    // NIVEL DE ALERTA - Agua en aumento
    activarLED(LED_AMARILLO);
    Serial.println("ALERTA: Nivel de agua MEDIO");
  } 
  else {
    // NIVEL SEGURO - Agua lejos o normal
    activarLED(LED_VERDE);
    Serial.println("NORMAL: Nivel de agua SEGURO");
  }
  
  // Esperar medio segundo antes de la siguiente medición
  delay(500);
}

// Función para medir la distancia con el sensor HC-SR04
float medirDistancia() {
  // Limpiar el pin TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Generar pulso de 10 microsegundos en TRIG
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Leer el tiempo del pulso en ECHO
  duracion = pulseIn(ECHO_PIN, HIGH);
  
  // Calcular distancia en centímetros
  // Velocidad del sonido = 343 m/s = 0.0343 cm/microsegundo
  // Distancia = (tiempo * velocidad) / 2
  float dist = (duracion * 0.0343) / 2;
  
  return dist;
}

// Función para activar solo un LED y apagar los demás
void activarLED(int pinLED) {
  // Apagar todos los LEDs
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
  
  // Encender solo el LED seleccionado
  digitalWrite(pinLED, HIGH);
}
