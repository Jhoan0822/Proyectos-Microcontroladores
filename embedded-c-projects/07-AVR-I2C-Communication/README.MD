# Proyecto 07: Control Remoto de Vehículo por I2C

Este proyecto demuestra una comunicación completa Maestro-Esclavo utilizando el protocolo **I²C (Inter-Integrated Circuit)** para controlar remotamente un vehículo de dos motores. Es una implementación práctica y robusta que muestra cómo un dispositivo (maestro) puede enviar comandos a otro (esclavo) para controlar actuadores.

## Funcionalidad del Sistema
El sistema se compone de dos microcontroladores ATmega32A con roles bien definidos:

*   **Maestro (`master/`) - El Control Remoto:**
    *   Lee el estado de cuatro botones pulsadores para determinar la dirección de movimiento deseada (Adelante, Atrás, Izquierda, Derecha).
    *   Actúa como el iniciador de la comunicación en el bus I2C.
    *   Envía un carácter de comando (`'F'`, `'B'`, `'L'`, `'R'`) al esclavo a través del bus.

*   **Esclavo (`slave/`) - El Controlador del Vehículo:**
    *   Está configurado con la dirección I2C `0x20` y su lógica es completamente **dirigida por interrupciones**.
    *   Al recibir un comando del maestro, la ISR del TWI (Two-Wire Interface) lo interpreta y manipula directamente los pines de salida conectados a un driver de motor (como el L298N) para mover el vehículo en la dirección comandada.

## Características Técnicas
*   **Diseño Asíncrono:** El esclavo utiliza interrupciones para procesar los comandos I2C, lo que significa que la CPU está libre y no está atrapada en un bucle esperando datos.
*   **Protocolo I2C Estándar:** La implementación se basa en el periférico TWI del AVR, configurando los registros para establecer la velocidad y manejar la comunicación.
*   **Control de Motores DC:** El esclavo controla un par de motores DC, implementando la lógica para movimientos complejos como giros (un motor adelante, otro atrás).

## Hardware Requerido
*   **2x Microcontroladores ATmega32A**.
*   **1x Driver de Motor (ej. L298N)** para el esclavo.
*   **1x Chasis de vehículo con 2 motores DC**.
*   **4x Botones Pulsadores** para el maestro.
*   **2x Resistencias de Pull-up (4.7kΩ)** para las líneas I2C (SDA y SCL).
*   Protoboards, cables y una fuente de alimentación para los motores.

## Esquema de Conexión
**La conexión correcta es la clave para este proyecto.**

*   **Bus I2C:**
    *   Conectar el pin `SCL` (PC0) del maestro al pin `SCL` (PC0) del esclavo.
    *   Conectar el pin `SDA` (PC1) del maestro al pin `SDA` (PC1) del esclavo.
    *   Conectar una resistencia de 4.7kΩ desde SCL a VCC y otra desde SDA a VCC.
*   **Maestro:** Conectar los cuatro botones a los pines `PD2`, `PD3`, `PD4`, `PD5` con una configuración de pull-down o usar los pull-ups internos.
*   **Esclavo:** Conectar los pines `PA0`-`PA3` y `PA5`-`PA6` a las entradas del driver de motor L298N.
*   **Alimentación:** Ambos microcontroladores deben compartir una conexión a **GND común**. El driver de motor necesitará su propia fuente de alimentación para los motores.
