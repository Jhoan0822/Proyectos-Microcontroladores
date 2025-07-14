# Proyecto 05: Medidor de Distancia Ultrasónico con Captura de Entrada

Este proyecto implementa un medidor de distancia de alta precisión utilizando un sensor ultrasónico **HC-SR04** y un microcontrolador ATmega32A. La medición de la distancia se realiza mediante la **Unidad de Captura de Entrada (Input Capture Unit - ICP)** del Timer1, que es el método más preciso y eficiente a nivel de hardware para esta tarea.

La distancia medida se muestra en una pantalla LCD 16x2, y un LED se enciende si el objeto detectado se encuentra dentro de un rango predefinido.

## Características Técnicas
*   **Medición de Tiempo por Hardware:** El núcleo del proyecto es el uso del pin **ICP1 (PD6)** del ATmega32A. Este hardware especializado permite registrar el valor exacto del contador del Timer1 en el momento en que ocurre un flanco (ascendente o descendente) en el pin, todo ello sin intervención de la CPU.
*   **Alta Precisión:** Al usar el temporizador sin prescaler, cada "tick" del contador representa 125 nanosegundos (con un cristal de 8MHz), lo que permite una medición muy precisa del ancho del pulso del sensor.
*   **Manejo de Desbordamiento (Overflow):** El sistema utiliza la interrupción de desbordamiento del Timer1 para contar cuántas veces el contador de 16 bits se ha reiniciado. Esto permite medir con precisión pulsos largos (y por lo tanto, distancias mayores) que exceden la capacidad de un solo ciclo del temporizador.
*   **Feedback Visual:** La distancia calculada se muestra en una pantalla LCD y un LED de estado indica si un objeto está dentro de un rango de interés (5-10 cm).

## Cómo Funciona el Protocolo HC-SR04 y la Medición
1.  **Trigger:** El microcontrolador envía un pulso de 10µs al pin `Trigger` del sensor HC-SR04.
2.  **Transmisión:** El sensor emite un tren de 8 pulsos ultrasónicos a 40 kHz.
3.  **Eco (Echo):** El pin `Echo` del sensor se pone en alto. El pin permanecerá en alto hasta que los pulsos ultrasónicos regresen después de rebotar en un objeto.
4.  **Captura del Flanco Ascendente:** El microcontrolador, configurado para detectar un flanco ascendente en su pin ICP1, captura el momento exacto en que el pin `Echo` se pone en alto y reinicia el Timer1.
5.  **Captura del Flanco Descendente:** La configuración de captura se cambia para detectar el flanco descendente. Cuando los pulsos de eco regresan, el pin `Echo` del sensor se pone en bajo. El microcontrolador captura este momento, y el valor del Timer1 (más los desbordamientos contados) representa la duración del viaje de ida y vuelta del sonido.
6.  **Cálculo de la Distancia:** La distancia se calcula con la fórmula:
    `Distancia = (Duración del Pulso * Velocidad del Sonido) / 2`
    El código convierte los "ticks" del temporizador a segundos y usa la velocidad del sonido (~343 m/s) para obtener la distancia final en centímetros.

## Hardware Requerido
*   **Microcontrolador:** ATmega32A
*   **Sensor:** Sensor Ultrasónico HC-SR04
*   **Pantalla:** LCD 16x2
*   **Indicador:** 1x LED
*   **Componentes Adicionales:** Protoboard, cables.
