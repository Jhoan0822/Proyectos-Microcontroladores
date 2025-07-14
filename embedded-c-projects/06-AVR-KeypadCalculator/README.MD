# Proyecto 06: Calculadora Aritmética con Teclado y LCD

Este proyecto implementa una calculadora de cuatro funciones básicas (+, -, *, /) en un microcontrolador ATmega32A. La interacción con el usuario se realiza a través de un teclado matricial 4x4 y los resultados se visualizan en una pantalla LCD de 16x2.

El proyecto es un excelente ejemplo de cómo construir una aplicación completa en un sistema embebido, combinando drivers de hardware de bajo nivel con una lógica de aplicación de alto nivel que incluye parseo de entrada y procesamiento de datos.

## Características Principales
*   **Operaciones Aritméticas Básicas:** Soporta suma, resta, multiplicación y división.
*   **Soporte de Punto Flotante:** La calculadora puede manejar números decimales, utilizando las funciones `atof()` y `dtostrf()` de la librería estándar de C para las conversiones.
*   **Parser de Entrada Secuencial:** El sistema no se limita a `A [op] B`; puede parsear una cadena de entrada continua (ej. "12.5*2=") leída desde el teclado.
*   **Interfaz de Usuario Intuitiva:** La pantalla LCD muestra la expresión matemática a medida que se introduce y presenta el resultado final en una línea separada.
*   **Diseño Modular:** El código está bien estructurado, separando la lógica principal de la calculadora (`main.c`) de los drivers reutilizables para el teclado (`mat_kbrd.c`) y la pantalla LCD (`lcd.c`).

## Lógica de Funcionamiento
El núcleo del programa es una máquina de estados implícita que gestiona la entrada del usuario:
1.  **Estado de Entrada del Primer Operando:** El sistema recolecta los dígitos y el punto decimal para el primer número hasta que se presiona una tecla de operador.
2.  **Estado de Entrada del Operador:** Al recibir un operador válido (+, -, x, /), el sistema lo almacena y pasa al siguiente estado.
3.  **Estado de Entrada del Segundo Operando:** Se recolectan los dígitos y el punto decimal para el segundo número.
4.  **Estado de Cálculo:** Al presionar la tecla de igual (`=`), la aplicación convierte las cadenas de caracteres de los operandos a números de punto flotante (`float`) usando `atof()`.
5.  **Realización de la Operación:** Se realiza la operación aritmética correspondiente. Se incluye un chequeo para la división por cero.
6.  **Visualización del Resultado:** El resultado `float` se convierte de nuevo a una cadena de caracteres usando `dtostrf()` y se muestra en la pantalla LCD.
7.  **Reinicio:** Una tecla designada permite limpiar el estado actual y comenzar un nuevo cálculo.

## Hardware Requerido
*   **Microcontrolador:** ATmega32A
*   **Entrada:** Teclado Matricial 4x4
*   **Pantalla:** LCD 16x2
*   **Componentes Adicionales:** Protoboard, cables, resistencias.
