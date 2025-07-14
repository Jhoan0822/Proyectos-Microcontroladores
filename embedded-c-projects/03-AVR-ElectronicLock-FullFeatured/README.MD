# Proyecto 03: Cerradura Electrónica Multifunción con Reloj y Control de Motor

Este es un proyecto avanzado de sistema embebido que implementa una cerradura electrónica completa en un microcontrolador ATmega32A. El sistema no solo gestiona el acceso mediante contraseñas, sino que también incluye un reloj en tiempo real, control de un motor DC a través de PWM y un modo de administrador para configuración.

Este proyecto demuestra la integración de múltiples periféricos de hardware y módulos de software para crear un producto funcional y robusto.

## Características Principales

*   **Doble Modo de Operación:**
    *   **Modo Normal:** El usuario puede introducir una contraseña para desbloquear la cerradura. El sistema controla un motor (simulando el cerrojo) mediante PWM, permitiendo un control de velocidad.
    *   **Modo Administrador:** Se accede con una contraseña secundaria y permite configurar parámetros del sistema.
*   **Reloj en Tiempo Real (RTC):** Muestra continuamente la hora (HH:MM:SS) en la pantalla LCD, funcionando en segundo plano gracias a interrupciones por temporizador.
*   **Interfaz de Usuario Clara:** Una pantalla LCD 16x2 proporciona feedback constante al usuario, mostrando la hora, menús, prompts de contraseña y mensajes de estado.
*   **Entrada por Teclado Matricial:** Un teclado 4x4 permite al usuario introducir contraseñas y navegar por los menús.
*   **Control de Motor DC:** Utiliza PWM (Pulse-Width Modulation) para controlar la velocidad y operación de un motor DC, que simula el mecanismo de la cerradura.
*   **Manejo de Interrupciones:**
    *   **Interrupciones Externas (INT1, INT2):** Se usan para acciones inmediatas como reiniciar el sistema o entrar al menú de administrador.
    *   **Interrupción de Timer (TIMER1_COMPA_vect):** Se ejecuta periódicamente para actualizar el reloj sin bloquear el procesador.

## Arquitectura del Software

El sistema está organizado en varios módulos de software, cada uno con una responsabilidad específica:

*   **`main.c` - Orquestador Principal:**
    *   Contiene el bucle principal de la aplicación que gestiona el estado general del sistema (bloqueado, desbloqueado, modo admin).
    *   Implementa la lógica de la máquina de estados que transita entre los diferentes modos de operación basándose en la entrada del usuario y las contraseñas.

*   **`lcd.c / lcd.h` - Módulo de Pantalla:**
    *   Librería de un tercero (Peter Fleury) para la gestión de bajo nivel de la pantalla LCD HD44780 en modo de 4 bits. Se encarga de la inicialización, envío de comandos y datos.

*   **`KeyPadScan.c` y `mat_kbrd.c` - Módulos de Teclado:**
    *   Proveen las funciones para escanear el teclado matricial 4x4 y devolver la tecla presionada. Implementan el algoritmo de barrido de filas y columnas.

*   **`T1EINT.c / T1EINT.h` - Módulo de Timers e Interrupciones:**
    *   **Configuración:** Inicializa el Timer1 para el reloj y las interrupciones externas INT1 e INT2.
    *   **ISR (Interrupt Service Routines):** Contiene las rutinas de atención a interrupciones. La ISR del Timer1 actualiza las variables del reloj, mientras que las ISR de las interrupciones externas establecen flags para cambiar el modo del sistema.

*   **`tc0_pwm.c / tc0_pwm.h` - Módulo de Control PWM:**
    *   Configura el Timer0 en modo Fast PWM para generar una señal que controla un motor DC. La velocidad del motor se puede ajustar modificando el registro `OCR0`.

## Hardware Requerido
*   **Microcontrolador:** ATmega32A
*   **Pantalla:** LCD 16x2 (controlador HD44780)
*   **Entrada:** Teclado Matricial 4x4 y dos botones para interrupciones externas.
*   **Actuador:** Un motor DC con su correspondiente driver (ej. L293D o un transistor MOSFET).
*   **Componentes Adicionales:** Protoboard, cables, etc.



`[Ver el video de demostración completo en YouTube](https://youtu.be/ENLACE_A_TU_VIDEO)`