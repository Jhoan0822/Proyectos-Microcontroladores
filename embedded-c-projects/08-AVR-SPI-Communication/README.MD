# Proyecto 8: Sistema de Adquisición y Monitoreo de Datos vía SPI

Este proyecto implementa un sistema distribuido completo utilizando el protocolo **SPI (Serial Peripheral Interface)** para comunicar dos microcontroladores ATmega32A. El sistema simula una aplicación real de **adquisición y monitoreo de datos (DAQ)**.

## Arquitectura y Funcionalidad del Sistema

El sistema se divide en dos nodos inteligentes, cada uno con un rol específico:

*   **Nodo Maestro (`master/`) - Estación de Adquisición de Sensores:**
    1.  **Lectura Analógica:** Lee continuamente tres sensores analógicos (simulados por potenciómetros) utilizando el Convertidor Analógico-Digital (ADC) del microcontrolador.
    2.  **Procesamiento de Datos:** Convierte las lecturas crudas del ADC a valores de voltaje y calcula el promedio de las tres lecturas.
    3.  **Visualización Local:** Muestra los voltajes individuales y el promedio calculado en una pantalla LCD 16x2, proporcionando un diagnóstico local del estado de los sensores.
    4.  **Transmisión de Datos:** Actúa como el maestro del bus SPI y transmite periódicamente el valor del promedio (formateado como una cadena de texto) al nodo esclavo.

*   **Nodo Esclavo (`slave/`) - Estación de Monitoreo y Actuación:**
    1.  **Recepción de Datos:** Se configura como esclavo SPI y espera pasivamente a recibir datos del maestro.
    2.  **Visualización Remota:** Muestra el valor promedio recibido en su propia pantalla LCD.
    3.  **Lógica de Alarma:** Compara el valor promedio recibido con un umbral predefinido (`3.0V`). Si el valor excede el umbral, enciende un LED de alarma.
    4.  **Persistencia de Datos:** Utiliza la **memoria EEPROM** interna del AVR para guardar el último valor promedio recibido. Esto demuestra la capacidad de retener datos importantes incluso si el sistema se reinicia.

## Características Técnicas Destacadas
*   **Comunicación SPI Full-Duplex:** Implementación robusta del protocolo SPI para la transferencia de datos de alta velocidad.
*   **Adquisición de Datos Multicanal (ADC):** Demuestra el uso del multiplexor del ADC para leer múltiples fuentes analógicas.
*   **Procesamiento de Punto Flotante:** Manejo de conversiones entre valores ADC, voltajes (`float`) y cadenas de texto (`string`) para procesamiento y transmisión.
*   **Memoria No Volátil (EEPROM):** Uso de la EEPROM para la persistencia de datos, una habilidad crucial en sistemas embebidos que deben resistir fallos de alimentación.
*   **Sistema Distribuido:** El proyecto es un ejemplo claro de un sistema embebido distribuido, donde las tareas de sensado y actuación están separadas físicamente pero conectadas por un bus de comunicación.

## Hardware Requerido
*   **2x Microcontroladores ATmega32A**.
*   **2x Pantallas LCD 16x2**.
*   **3x Potenciómetros** (para simular los sensores analógicos en el maestro).
*   **1x LED** (para la alarma en el esclavo).
*   Protoboards, cables de conexión.

## Esquema de Conexión
La comunicación SPI requiere 4 hilos principales:

*   **MOSI (Master Out, Slave In):** Conectar `PB5` del maestro a `PB5` del esclavo.
*   **MISO (Master In, Slave Out):** Conectar `PB6` del maestro a `PB6` del esclavo.
*   **SCK (Serial Clock):** Conectar `PB7` del maestro a `PB7` del esclavo.
*   **SS (Slave Select):** Conectar un pin de salida del maestro (ej. `PB4`) al pin `SS` (PB4) del esclavo.
*   **Maestro:** Conectar los tres potenciómetros a los pines del ADC: `PA0`, `PA1`, `PA2`.
*   **Esclavo:** Conectar el LED de alarma al pin `PD3`.
*   **GND Común:** Es fundamental que ambos microcontroladores compartan una conexión a tierra (GND) común.
