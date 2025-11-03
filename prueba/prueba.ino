#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 2/*pin de conexion del sensor DHT22*/
#define DHTTYPE DHT22 /*cambiado a DHT22 */
#define SOIL_MOISTURE_PIN A0 /*lee el pin del sensor de humedad del suelo */
#define WATER_LEVEL_PIN A1 /*PIN DEL SENSOR DEL NIVEL DE AGUA*/
#define RELAY_PUMP 7 /*PIN DEL RELE PARA LA BOMBA DE AGUA */
#define RELAY_FAN 8 /*PIN DEL RELE PARA EL VEINTILADOR */


DHT dht(DHTPIN, DHTTYPE);

// Configuración del LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección I2C del LCD, tamaño 16x2

void setup() {
  Serial.begin(9600);      // Inicialización del monitor serial
  dht.begin();             // Inicialización del sensor DHT22
  lcd.begin(16, 2);        // Inicialización del LCD
  lcd.backlight();         // Activa la luz de fondo del LCD

  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(WATER_LEVEL_PIN, INPUT);
  pinMode(RELAY_PUMP, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);

  digitalWrite(RELAY_PUMP, HIGH); // Bomba apagada al iniciar
  digitalWrite(RELAY_FAN, HIGH);  // Ventilador apagado al iniciar
}

void loop() {
  // Lecturas de los sensores
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  int waterLevelValue = analogRead(WATER_LEVEL_PIN);
  float temperature = dht.readTemperature();  // Lectura de la temperatura
  float humidity = dht.readHumidity();        // Lectura de la humedad ambiente

  // Convertir valor de humedad del suelo (ajustar según pruebas)
  int soilMoisturePercent = map(soilMoistureValue, 1023, 0, 0, 100);

  // Mostrar datos en el monitor serial
  Serial.print("Humedad de suelo: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");

  Serial.print("Nivel de agua: ");
  Serial.print(waterLevelValue > 500 ? "Suficiente" : "Bajo");
  Serial.println();

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println("°C");

  Serial.print("Humedad ambiente: ");
  Serial.print(humidity);
  Serial.println("%");

  // Mostrar datos en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C Hum: ");
  lcd.print(humidity);
  lcd.setCursor(0, 1);
  lcd.print("Suelo: ");
  lcd.print(soilMoisturePercent);
  lcd.print("% Agua: ");
  lcd.print(waterLevelValue > 500 ? "OK" : "Bajo");

  // Control de la bomba de agua
  if (soilMoisturePercent < 40) {  // Ajusta el umbral según tus pruebas
    digitalWrite(RELAY_PUMP, LOW); // Activa la bomba
    Serial.println("Bomba: Activada");
  } else {
    digitalWrite(RELAY_PUMP, HIGH); // Apaga la bomba
    Serial.println("Bomba: Apagada");
  }

  // Control del ventilador
  if (temperature >= 30) {
    digitalWrite(RELAY_FAN, LOW); // Activa el ventilador
    Serial.println("Ventilador: Activado");
  } else {
    digitalWrite(RELAY_FAN, HIGH); // Apaga el ventilador
    Serial.println("Ventilador: Apagado");
  }

  delay(2000); // Pausa de 2 segundos antes de la siguiente lectura
}