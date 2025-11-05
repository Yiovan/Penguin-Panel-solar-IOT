# Sistema de Conmutación Automática Solar/Batería

Sistema de control automático que alterna entre alimentación solar y batería según el nivel de carga, implementado en Arduino.

## 📋 Descripción

Este proyecto gestiona automáticamente dos fuentes de energía mediante relés, conmutando entre panel solar y batería basándose en el voltaje medido. Ideal para sistemas de energía renovable con respaldo.

## ⚡ Características

- Monitoreo continuo del voltaje de batería
- Conmutación automática entre fuentes de energía
- Control mediante relés activo-LOW
- Indicadores visuales con LEDs
- Histéresis para evitar cambios bruscos

## 🔧 Componentes

- **Arduino** (Uno, Nano, Mega, etc.)
- **2 Relés** o módulo de 2 relés (activo-LOW)
- **2 LEDs** (rojo y amarillo) con resistencias de 220Ω
- **Divisor de voltaje** (2 resistencias iguales para lectura de batería)
- **Batería LiPo/Li-ion** (3.7V nominal)
- **Panel solar** con regulador

## 📌 Conexiones

```
Arduino Pin 8  → Relé Solar / LED Rojo
Arduino Pin 9  → Relé Batería / LED Amarillo
Arduino Pin A0 → Divisor de voltaje (punto medio)
Arduino GND    → GND común
```

### Divisor de voltaje
```
Vbat (+) ---[R1]--- A0 ---[R2]--- GND
              (10kΩ)         (10kΩ)
```

## ⚙️ Configuración

### Umbrales de voltaje

```cpp
float Vmax = 4.1;  // Batería cargada → activa solar
float Vmin = 3.6;  // Batería baja → mantiene batería
```

Ajusta estos valores según tu batería:
- **LiPo 1S**: 3.0V (mín) - 4.2V (máx)
- **LiFePO4**: 2.5V (mín) - 3.65V (máx)

### Divisor resistivo

El código asume un divisor 1:2. Si usas otros valores:

```cpp
Vbat = (lectura * 5.0 / 1023.0) * (R1 + R2) / R2;
```

## 🚀 Instalación

1. Conecta los componentes según el diagrama
2. Abre el código en Arduino IDE
3. Selecciona tu placa y puerto COM
4. Carga el sketch
5. Abre el Monitor Serial (9600 baud)

## 📊 Lógica de Funcionamiento

```
Vbat > 4.1V  → ☀️  Solar activo (batería cargada)
Vbat < 3.6V  → 🔋 Batería activa (carga baja)
3.6V - 4.1V  → ⚡ Batería activa (zona neutra)
```

**Zona neutra**: Previene oscilaciones manteniendo la batería activa en el rango intermedio.

## 🔍 Monitor Serial

Salida ejemplo:
```
Voltaje batería: 4.05 V
Fuente activa: Solar ☀️

Voltaje batería: 3.82 V
Fuente activa: Batería (zona neutra) ⚡

Voltaje batería: 3.45 V
Fuente activa: Batería 🔋
```

## 💻 Código Principal

```cpp
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
    Serial.println("Fuente activa: Solar ☀️");
  } 
  else if (Vbat < Vmin) {
    // Modo batería: poca carga
    setSolar(false);
    setBateria(true);
    Serial.println("Fuente activa: Batería 🔋");
  } 
  else {
    // Zona intermedia: mantener batería como predeterminado
    setSolar(false);
    setBateria(true);
    Serial.println("Fuente activa: Batería (zona neutra) ⚡");
  }
  
  delay(1000);
}
```

## ⚠️ Consideraciones

- Los relés son **activo-LOW** (LOW = encendido)
- Verifica que tu divisor de voltaje no exceda 5V en A0
- No conectes directamente cargas de alta potencia sin un circuito de protección
- Usa diodos de protección en las bobinas de los relés

## 🔄 Posibles Mejoras

- [ ] Agregar filtro de promedio para lecturas más estables
- [ ] Implementar protección por sobrecarga
- [ ] Añadir display LCD para visualización local
- [ ] Registrar datos en tarjeta SD
- [ ] Control remoto por WiFi/Bluetooth

## 📝 Licencia

Proyecto de código abierto. Libre para uso personal y educativo.

---

**Nota**: Este sistema es un prototipo educativo. Para aplicaciones críticas, implementa protecciones adicionales y consulta las especificaciones de tus componentes.