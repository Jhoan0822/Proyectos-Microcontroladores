# Proyecto 02: Reproductor de Melodías con Timer e Interrupciones

Este proyecto para un microcontrolador ATmega32A demuestra cómo generar tonos musicales en un buzzer piezoeléctrico. Utiliza el **Timer1 del AVR en modo CTC** y una **interrupción de comparación (ISR)** para crear ondas cuadradas de frecuencias precisas, reproduciendo una melodía.

La canción implementada es un fragmento del verso de **"Rosas"** del grupo español La Oreja de Van Gogh.

## Características Técnicas
*   **Generación de Tono Precisa:** Uso del Timer1 para generar frecuencias, evitando los `_delay_us()` imprecisos y bloqueantes.
*   **Manejo de Duración por Interrupción:** La duración de cada nota es controlada por un contador dentro de la ISR, liberando al procesador.
*   **Código Data-Driven:** La melodía no está "quemada" en el código, sino que se define como un arreglo de estructuras `Note`, lo que facilita enormemente la modificación o adición de nuevas canciones.
*   **Hardware Abstraction Mínima:** Los pines del hardware están definidos con `#define` para facilitar su reconfiguración.

## Hardware Requerido
*   **Microcontrolador:** ATmega32A (o un AVR similar con Timer1).
*   **Salida de Audio:** Un buzzer piezoeléctrico.
*   **Componentes Adicionales:** Protoboard, cables de conexión.

## Esquema de Conexión
El buzzer se conecta directamente entre el pin de salida y GND.

*   **Pin Positivo (+) del Buzzer:** `PD5` del ATmega32A
*   **Pin Negativo (-) del Buzzer:** `GND`

## Cómo Funciona: Deep Dive Técnico
El núcleo del proyecto es la función `tone()`.
1.  **Cálculo de Frecuencia:** Para una frecuencia `f` dada, el valor de comparación `OCR1A` se calcula con la fórmula `OCR1A = (F_CPU / (2 * N * f)) - 1`, donde `N` es el valor del prescaler. El código elige el prescaler más pequeño posible para mantener la máxima resolución.
2.  **Modo CTC (Clear Timer on Compare Match):** El Timer1 se configura en modo CTC. Esto significa que el contador del timer (`TCNT1`) cuenta hacia arriba. Cuando `TCNT1` iguala a `OCR1A`, se dispara la interrupción `TIMER1_COMPA_vect` y el contador se resetea a 0, comenzando el ciclo de nuevo.
3.  **La Interrupción (ISR):** Cada vez que la ISR se ejecuta (dos veces por cada ciclo de onda), conmuta (`toggle`) el pin del buzzer. Esto genera una onda cuadrada con una frecuencia de `f`.
4.  **Control de Duración:** La variable `timer1_toggle_count` se inicializa con el número total de conmutaciones necesarias para una duración dada. La ISR decrementa este contador en cada ejecución. Cuando llega a cero, la interrupción se deshabilita, deteniendo el tono.
