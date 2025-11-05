# 🌱 Sistema de Riego Automatizado con Arduino

Sistema inteligente de riego automatizado para competencia de programación, que utiliza Arduino para controlar el suministro de agua mediante un módulo de relé y monitorear el estado de la tierra a través de una pantalla LCD.

![Diagrama del Circuito](docs/circuit-diagram.png)

## 📋 Descripción del Proyecto

Este proyecto implementa un sistema de riego automatizado que activa una bomba de agua durante 21 segundos cuando detecta que la tierra está seca. El sistema muestra el estado actual (Tierra Seca/Tierra Húmeda) en una pantalla LCD I2C y envía información por el puerto serial para monitoreo.

### Características Principales

- ✅ Control automatizado de riego por tiempo definido
- ✅ Pantalla LCD I2C 16x2 para visualización del estado
- ✅ Módulo de relé para control de bomba de agua
- ✅ Sensor de humedad del suelo
- ✅ Comunicación serial para monitoreo y debugging
- ✅ Sistema de seguridad con detención automática

## 🔧 Componentes Necesarios

| Componente | Cantidad | Especificaciones |
|------------|----------|------------------|
| Arduino UNO | 1 | Microcontrolador principal |
| LCD I2C 16x2 | 1 | Dirección 0x27 |
| Módulo de Relé 5V | 1 | 1 canal |
| Sensor de Humedad | 1 | Sensor capacitivo o resistivo |
| Bomba de Agua | 1 | 5-12V DC |
| Cables Jumper | Varios | Macho-Macho y Macho-Hembra |
| Fuente de Alimentación | 1 | Según bomba de agua |

## 📐 Diagrama de Conexiones

### Conexiones Arduino

```
Arduino UNO:
├── Pin 8  → Módulo de Relé (IN)
├── Pin 6  → Sensor de Humedad (OUT)
├── SDA    → LCD I2C (SDA)
├── SCL    → LCD I2C (SCL)
├── 5V     → Alimentación sensores y LCD
└── GND    → Tierra común
```

### Conexiones del Módulo de Relé

```
Relé 5V:
├── VCC  → Arduino 5V
├── GND  → Arduino GND
├── IN   → Arduino Pin 8
├── COM  → Fuente de alimentación (+)
└── NO   → Bomba de agua (+)
```

### Conexiones del Sensor de Humedad

```
Sensor de Humedad:
├── VCC  → Arduino 5V
├── GND  → Arduino GND
└── DO   → Arduino Pin 6
```

## 💻 Instalación y Configuración

### Requisitos Previos

1. **Arduino IDE** instalado (versión 1.8.x o superior)
2. Librería **LiquidCrystal_I2C** instalada

### Instalación de Librerías

#### Método 1: Mediante el Gestor de Librerías

```
1. Abrir Arduino IDE
2. Ir a Sketch → Incluir Librería → Administrar Librerías
3. Buscar "LiquidCrystal I2C"
4. Instalar "LiquidCrystal I2C" por Frank de Brabander
```

#### Método 2: Manual

```bash
cd ~/Arduino/libraries/
git clone https://github.com/johnrickman/LiquidCrystal_I2C.git
```

### Carga del Código

1. Clonar este repositorio:
```bash
git clone https://github.com/tu-usuario/sistema-riego-arduino.git
cd sistema-riego-arduino
```

2. Abrir el archivo `codigo_FINAL__1_.ino` en Arduino IDE

3. Seleccionar la placa y puerto correcto:
   - Herramientas → Placa → Arduino UNO
   - Herramientas → Puerto → (Seleccionar el puerto COM correspondiente)

4. Verificar y cargar el código al Arduino

## 🚀 Uso del Sistema

### Funcionamiento Básico

1. **Encendido**: Al conectar el Arduino, el LCD mostrará "Sistema de Riego" durante 2 segundos
2. **Detección**: El sistema detecta tierra seca y muestra "Tierra Seca" en el LCD
3. **Riego**: Activa automáticamente la bomba durante 21 segundos
4. **Finalización**: Muestra "Tierra Humeda" y detiene el sistema

### Monitoreo Serial

Abrir el Monitor Serial en Arduino IDE (Herramientas → Monitor Serial) a **9600 baudios** para ver los mensajes de estado:

```
Tierra Seca
Tierra Humeda
```

## ⚙️ Configuración Avanzada

### Ajustar Tiempo de Riego

Modificar la línea 34 del código:

```cpp
delay(21000); // Cambiar 21000 por el tiempo deseado en milisegundos
```

### Cambiar Dirección I2C del LCD

Si tu LCD usa una dirección diferente, modificar la línea 5:

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2); // Cambiar 0x27 por tu dirección
```

Para encontrar la dirección I2C, usar el sketch **I2C Scanner**.

### Activar Ciclo Continuo

Para que el sistema funcione en ciclos repetitivos, eliminar el bucle `while(true)` de las líneas 44-46 y agregar un delay:

```cpp
// Reemplazar líneas 44-46 por:
delay(300000); // Esperar 5 minutos antes del próximo ciclo
```

## 🐛 Solución de Problemas

### El LCD no muestra nada

- Verificar las conexiones SDA y SCL
- Ajustar el potenciómetro del LCD para el contraste
- Verificar la dirección I2C con I2C Scanner
- Revisar que la librería LiquidCrystal_I2C esté instalada

### El relé no activa la bomba

- Verificar la conexión del pin 8 al módulo de relé
- Comprobar que el LED del relé se encienda
- Verificar la alimentación externa de la bomba
- Revisar las conexiones COM y NO del relé

### El sensor no detecta humedad

- Verificar la conexión del pin 6
- Comprobar la alimentación del sensor (5V y GND)
- Calibrar el sensor según las instrucciones del fabricante

## 📝 Código Fuente

El código principal se encuentra en `codigo_FINAL__1_.ino` y está estructurado de la siguiente manera:

- **Setup**: Inicialización de pines, LCD y comunicación serial
- **Loop**: Ciclo principal con detección, riego y visualización

## 🏆 Competencia de Programación

Este proyecto fue desarrollado para una competencia de programación enfocada en sistemas embebidos y automatización. El objetivo es demostrar:

- Integración de múltiples componentes electrónicos
- Control de actuadores mediante microcontroladores
- Interfaz de usuario mediante LCD
- Lógica de programación para automatización

## 📚 Recursos Adicionales

- [Documentación Arduino](https://www.arduino.cc/reference/en/)
- [LiquidCrystal_I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C)
- [Tutorial de Módulos de Relé](https://www.arduino.cc/en/Tutorial/BuiltInExamples)

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📄 Licencia

Este proyecto está bajo la Licencia MIT - ver el archivo `LICENSE` para más detalles.

## ✍️ Autor

Desarrollado para competencia de programación

## 🙏 Agradecimientos

- Comunidad Arduino por la documentación y soporte
- Autores de la librería LiquidCrystal_I2C
- Organizadores de la competencia de programación

---

⭐ Si este proyecto te fue útil, no olvides darle una estrella en GitHub
