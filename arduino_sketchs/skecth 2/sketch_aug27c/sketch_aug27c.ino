// LED pins
const int LEDRED = 10;
const int LEDGREEN = 11;
const int LEDYELLOW = 12;

// Botón en pin 9
const int BUTTON = 9;

// Estado de parpadeo
bool blinkMode = false;

// Contador de clicks del botón
int clickCount = 0;

void setup() {
    pinMode(LEDRED, OUTPUT);
    pinMode(LEDYELLOW, OUTPUT);
    pinMode(LEDGREEN, OUTPUT);

    pinMode(BUTTON, INPUT_PULLUP); // botón con resistencia pull-up

    Serial.begin(9600);

    mainMenu();
    
}

void loop() {
    // --- CONTROL POR BOTÓN ---
    if (digitalRead(BUTTON) == LOW) {
        delay(200); // anti-rebote

        clickCount++;
        if (clickCount > 10) clickCount = 1; // reiniciar

        ejecutarOpcion(clickCount);
    }

    // --- CONTROL POR SERIAL ---
    if (Serial.available() > 0) {
        char opt = Serial.read();

        if (opt >= '0' && opt <= '9') {
            int opcion = opt - '0'; // convertir char en número
            if (opcion == 0) opcion = 10; // mapear 0 -> 10
            ejecutarOpcion(opcion);
        } else if (opt == 'm') {
            mainMenu();
        } else {
            Serial.println("Opción inválida. Presiona 'm' para mostrar el menú.");
        }
    }

    // --- MODO PARPADEO ---
    if (blinkMode) {
        digitalWrite(LEDRED, HIGH);
        digitalWrite(LEDGREEN, HIGH);
        digitalWrite(LEDYELLOW, HIGH);
        delay(500);

        digitalWrite(LEDRED, LOW);
        digitalWrite(LEDGREEN, LOW);
        digitalWrite(LEDYELLOW, LOW);
        delay(500);
    }
}

void ejecutarOpcion(int opt) {
    switch (opt) {
        case 1:
            digitalWrite(LEDRED, HIGH);
            Serial.println("Opción 1 -> LED ROJO ENCENDIDO");
            break;
        case 2:
            digitalWrite(LEDRED, LOW);
            Serial.println("Opción 2 -> LED ROJO APAGADO");
            break;
        case 3:
            digitalWrite(LEDYELLOW, HIGH);
            Serial.println("Opción 3 -> LED AMARILLO ENCENDIDO");
            break;
        case 4:
            digitalWrite(LEDYELLOW, LOW);
            Serial.println("Opción 4 -> LED AMARILLO APAGADO");
            break;
        case 5:
            digitalWrite(LEDGREEN, HIGH);
            Serial.println("Opción 5 -> LED VERDE ENCENDIDO");
            break;
        case 6:
            digitalWrite(LEDGREEN, LOW);
            Serial.println("Opción 6 -> LED VERDE APAGADO");
            break;
        case 7:
            digitalWrite(LEDRED, HIGH);
            digitalWrite(LEDGREEN, HIGH);
            digitalWrite(LEDYELLOW, HIGH);
            Serial.println("Opción 7 -> TODOS ENCENDIDOS");
            break;
        case 8:
            blinkMode = false;
            digitalWrite(LEDRED, LOW);
            digitalWrite(LEDGREEN, LOW);
            digitalWrite(LEDYELLOW, LOW);
            Serial.println("Opción 8 -> TODOS APAGADOS (y se detiene blink)");
            break;
        case 9:
            blinkMode = true;
            Serial.println("Opción 9 -> INICIO MODO PARPADEO (usar opción 8 para salir)");
            break;
        case 10:
            blinkMode = false;
            digitalWrite(LEDRED, LOW);
            digitalWrite(LEDGREEN, LOW);
            digitalWrite(LEDYELLOW, LOW);
            Serial.println("Opción 10 -> SALIR (todo apagado)");
            break;
    }
}

void mainMenu() {
    Serial.println("\n::: MENU PRINCIPAL :::");
    Serial.println("[1]. Encender LED ROJO");
    Serial.println("[2]. Apagar LED ROJO");
    Serial.println("[3]. Encender LED AMARILLO");
    Serial.println("[4]. Apagar LED AMARILLO");
    Serial.println("[5]. Encender LED VERDE");
    Serial.println("[6]. Apagar LED VERDE");
    Serial.println("[7]. Encender TODOS los LEDs");
    Serial.println("[8]. Apagar TODOS los LEDs (y salir de blink)");
    Serial.println("[9]. Modo intermitente");
    Serial.println("[0]. Salir (apagar todo)");
    Serial.println("[m]. Mostrar este menú");
    Serial.println("\n También puedes usar el BOTÓN (pin 9) para avanzar de 1 a 10 secuencialmente.\n");
}