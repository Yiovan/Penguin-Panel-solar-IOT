// Pines de conexión
const int rele_solar = 8;    // LED rojo / Relé solar (activo-LOW)
const int rele_bateria = 9;  // LED amarillo / Relé batería (activo-LOW)
const int pin_voltaje = A0;  // Lectura del voltaje de la batería

// Variables de voltaje
float Vbat = 0;
float Vmax = 4.1;  // Umbral superior (batería cargada)
float Vmin = 3.6;  // Umbral inferior (batería baja)

// Funciones para controlar relés/LEDs (modo activo-LOW)
void setSolar(bool on) {
  digitalWrite(rele_solar, on ? LOW : HIGH);  // LOW = encendido
}

void setBateria(bool on) {
  digitalWrite(rele_bateria, on ? LOW : HIGH);  // LOW = encendido
}

void setup() {
  pinMode(rele_solar, OUTPUT);
  pinMode(rele_bateria, OUTPUT);
  Serial.begin(9600);

  // Estado inicial: ambos apagados
  setSolar(false);
  setBateria(false);
}

void loop() {
  // Leer voltaje de la batería desde A0 (divisor resistivo)
  int lectura = analogRead(pin_voltaje);
  Vbat = (lectura * 5.0 / 1023.0) * 2;  // Multiplicamos por 2 por el divisor

  // Mostrar voltaje en el monitor serial
  Serial.print("Voltaje batería: ");
  Serial.print(Vbat, 2);
  Serial.println(" V");

  // Lógica de conmutación
  if (Vbat > Vmax) {
    // Modo solar: batería cargada
    setSolar(true);
    setBateria(false);
    Serial.println("Fuente activa: Solar ");
  } 
  else if (Vbat < Vmin) {
    // Modo batería: poca carga
    setSolar(false);
    setBateria(true);
    Serial.println("Fuente activa: Batería ");
  } 
  else {
    // Zona intermedia: mantener batería como predeterminado
    setSolar(false);
    setBateria(true);
    Serial.println("Fuente activa: Batería (zona neutra) ");
  }

  delay(1000);
}