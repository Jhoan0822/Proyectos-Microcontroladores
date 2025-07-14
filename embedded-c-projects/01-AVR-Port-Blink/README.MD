# Proyecto 01: Parpadeo de LEDs en un Puerto (AVR "Hello, World")

Este proyecto es la implementación del "Hola, Mundo" para el mundo de los sistemas embebidos. El programa configura todos los pines de un puerto de E/S (GPIO) de un microcontrolador ATmega32A como salidas y los hace parpadear al unísono.

Es el primer paso fundamental para verificar que el entorno de desarrollo, el compilador y el programador de hardware están funcionando correctamente, y demuestra el control más básico sobre el hardware del microcontrolador.

## Funcionalidad
El programa realiza un ciclo infinito con dos pasos:
1.  **Encender todos los LEDs:** Escribe el valor `0xFF` (binario `11111111`) en `PORTB`, poniendo todos los pines en estado alto.
2.  **Apagar todos los LEDs:** Escribe el valor `0x00` (binario `00000000`) en `PORTB`, poniendo todos los pines en estado bajo.

Entre cada cambio de estado, se utiliza una función de retardo (`_delay_ms`) para crear un intervalo de 1 segundo, haciendo el parpadeo visible al ojo humano.

## Conceptos Demostrados
*   **Configuración de GPIO:** Configuración del Registro de Dirección de Datos (`DDRB`) para establecer los pines como salidas.
*   **Manipulación de Puertos:** Escritura de valores en un puerto de salida (`PORTB`) para controlar el estado de los pines.
*   **Temporización por Software:** Uso de la librería `<util/delay.h>` para crear retardos bloqueantes.
*   **Estructura Básica de un Programa Embebido:** Un bucle infinito (`while(1)`) que ejecuta la lógica principal de la aplicación.

## Hardware Requerido
*   **Microcontrolador:** ATmega32A.
*   **Indicadores:** 8 LEDs.
*   **Componentes Pasivos:** 8 resistencias limitadoras de corriente (ej. 220Ω o 330Ω).
*   Protoboard y cables de conexión.
