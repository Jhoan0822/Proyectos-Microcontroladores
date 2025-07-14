# Portafolio de Programación en C: Desde la Consola hasta Sistemas Embebidos

¡Hola! Soy **Jhoan Eduardo Saldarriaga Serna**, un apasionado Estudiante de ingeniería electrónica con un fuerte enfoque en la programación de bajo nivel y los sistemas embebidos.

Este repositorio es una colección curada de los proyectos que desarrollé durante mi curso de **Programación de Microcontroladores** en la Universidad del Valle. El objetivo es demostrar mis habilidades prácticas en la programación en C, tanto para aplicaciones de consola estándar como para el control de hardware en microcontroladores AVR.

---

## 🛠️ Habilidades y Tecnologías Demostradas

A través de estos proyectos, demuestro experiencia en las siguientes áreas:

*   **Lenguaje de Programación:** C (Estándar C11 y `avr-gcc`)
*   **Arquitectura de Microcontroladores:** AVR (ATmega32A)
*   **Periféricos de Hardware:**
    *   GPIO (Entrada/Salida de propósito general)
    *   Timers/Counters (Modo CTC, PWM, Captura de Entrada, Interrupciones por Desbordamiento)
    *   ADC (Convertidor Analógico-Digital)
    *   Interrupciones (Externas y por Periféricos)
*   **Protocolos de Comunicación Serial:**
    *   **I²C** (TWI)
    *   **SPI** (Serial Peripheral Interface)
*   **Componentes Externos:**
    *   Pantallas LCD (16x2)
    *   Teclados Matriciales (4x4)
    *   Sensores Ultrasónicos (HC-SR04)
    *   Motores DC y Drivers (L298N)
    *   Buzzers Piezoeléctricos
*   **Conceptos de Software:**
    *   Diseño modular y drivers
    *   Máquinas de estado (FSM)
    *   Manejo de punteros y memoria
    *   Manipulación de bits a nivel de registros
    *   Programación dirigida por interrupciones (ISR)
    *   Manejo de memoria no volátil (EEPROM)
*   **Herramientas y Entorno:**
    *   Microchip Studio (Atmel Studio)
    *   CMake para proyectos de consola
    *   Git y GitHub para control de versiones

---

## 📖 Índice de Proyectos

Cada proyecto está autocontenido en su carpeta y cuenta con su propio `README.md` detallado que incluye una descripción técnica, el esquema de conexión y una demostración.

### 🤖 Proyectos de Sistemas Embebidos (AVR)

| #  | Proyecto                                                                    | Descripción Breve                                                                   | Conceptos Clave                                     |
|----|-----------------------------------------------------------------------------|-------------------------------------------------------------------------------------|-----------------------------------------------------|
| 01 | [**AVR Port Blink**](./embedded-c-projects/01-AVR-Port-Blink/)              | El "Hola, Mundo" de los embebidos: parpadeo de 8 LEDs en un puerto.                  | `GPIO`, `Delay`                                     |
| 02 | [**AVR Song Player**](./embedded-c-projects/02-AVR-SongPlayer-TimerInterrupt/) | Reproductor de melodías en un buzzer usando Timers e Interrupciones para generar tonos. | `Timers (CTC)`, `Interrupts (ISR)`, `PWM`           |
| 03 | [**AVR Electronic Lock**](./embedded-c-projects/03-AVR-ElectronicLock-FullFeatured/) | Cerradura electrónica completa con reloj, control de motor PWM y modo administrador.    | `State Machine`, `GPIO`, `Timers`, `PWM`, `Interrupts`|
| 04 | [**AVR Frequency Generator**](./embedded-c-projects/04-AVR-FrequencyGenerator-Timer0-ISR/) | Generador de onda cuadrada de frecuencia precisa utilizando el modo CTC del Timer1.     | `Timers (CTC)`, `Hardware Signal Generation`        |
| 05 | [**AVR Ultrasonic Ranger**](./embedded-c-projects/05-AVR-UltrasonicRanger-InputCapture/) | Medidor de distancia con un sensor HC-SR04 usando la Captura de Entrada del Timer1.   | `Timers (Input Capture)`, `Interrupts`              |
| 06 | [**AVR Keypad Calculator**](./embedded-c-projects/06-AVR-KeypadCalculator/) | Calculadora aritmética con soporte de punto flotante, teclado y pantalla LCD.       | `Parsing`, `Floating Point`, `Drivers`              |
| 07 | [**AVR I2C Communication**](./embedded-c-projects/07-AVR-I2C-Communication/)  | Sistema Maestro-Esclavo por I²C para el control remoto de motores.                  | `I2C (TWI)`, `Interrupt-driven Slave`               |
| 08 | [**AVR SPI Communication**](./embedded-c-projects/08-AVR-SPI-Communication/)    | Sistema de adquisición de datos (DAQ) que envía lecturas de ADC por SPI a otro uC. | `SPI`, `ADC`, `EEPROM`                              |

### 🖥️ Proyectos de C Estándar (Consola)

| #  | Proyecto                                                                    | Descripción Breve                                                              | Conceptos Clave                                 |
|----|-----------------------------------------------------------------------------|--------------------------------------------------------------------------------|-------------------------------------------------|
| 01 | [**Console Hangman Game**](./standard-c-projects/01-ConsoleHangmanGame/)    | Implementación del clásico juego del Ahorcado para la línea de comandos.       | `Console I/O`, `String Manipulation`, `CMake`   |
| 02 | [**Fashion Advisor CLI**](./standard-c-projects/02-FashionAdvisorCLI/)        | Un sistema experto simple que recomienda prendas. Caso de estudio en refactorización. | `Data-Driven Design`, `Enums`, `Structs`, `CMake` |

---

## 🔗 Conecta Conmigo

¡Gracias por visitar mi portafolio! Estoy siempre abierto a feedback, preguntas o nuevas oportunidades.

*   **LinkedIn:** [**https://www.linkedin.com/in/jhoan-saldarriaga/**](https://www.linkedin.com/in/jhoan-saldarriaga/)
