# Proyecto 06: Generador de Frecuencias con Timer0 e Interrupción

Este proyecto es una demostración concisa y eficiente de cómo generar una señal de onda cuadrada utilizando el **Timer0 de 8 bits** de un microcontrolador ATmega32A. A diferencia de un generador basado en Timer1, este enfoque es ideal para cuando el temporizador de 16 bits está ocupado en otra tarea o cuando los requisitos de frecuencia no necesitan la alta resolución de 16 bits.

El programa configura el Timer0 en **modo CTC (Clear Timer on Compare Match)** y utiliza la interrupción asociada para conmutar un pin de salida, resultando en una señal de frecuencia estable y precisa.

## Características Técnicas
*   **Eficiencia de Recursos:** Utiliza el Timer0 de 8 bits, liberando el Timer1 (16 bits) y el Timer2 (8 bits con funciones asíncronas) para otras tareas más complejas como PWM o conteo de eventos externos.
*   **Generación por Interrupción (ISR):** La conmutación del pin de salida se realiza dentro de una Rutina de Servicio de Interrupción (`TIMER0_COMP_vect`). Este método es asíncrono y no bloquea el flujo principal del programa.
*   **Frecuencia Fija:** El código está configurado para generar una frecuencia de **312.5 Hz**, calculada a partir de un reloj de sistema de 8 MHz, un prescaler de 256 y un valor de comparación de 49.
*   **Bajo Consumo de CPU:** Una vez configurado, el temporizador opera de forma autónoma, permitiendo que la CPU se dedique a otras tareas o entre en modos de bajo consumo.

## Cómo Funciona
1.  **Configuración del Timer0:** El registro de control `TCCR0` se configura para operar en modo CTC (`WGM01=1`) y con un prescaler de 256 (`CS02=1`).
2.  **Valor de Comparación:** El registro `OCR0` se carga con el valor `49`.
3.  **Habilitación de Interrupción:** Se habilita la interrupción por coincidencia de comparación del Timer0 (`OCIE0` en el registro `TIMSK`).
4.  **Operación:** El contador del timer (`TCNT0`) se incrementa. Cuando `TCNT0` iguala a `OCR0` (49), ocurren dos cosas simultáneamente:
    *   El hardware dispara la interrupción `TIMER0_COMP_vect`.
    *   El contador `TCNT0` se reinicia a 0.
5.  **ISR en Acción:** La ISR se ejecuta y conmuta el estado del pin de salida `PD7`. Este proceso se repite indefinidamente, generando una onda cuadrada estable.

## Hardware Requerido
*   **Microcontrolador:** ATmega32A.
*   **Herramienta de Medición:** Un **osciloscopio** o **analizador lógico** para visualizar y verificar la señal de salida.
