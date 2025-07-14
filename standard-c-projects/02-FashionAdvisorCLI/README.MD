# Proyecto 02: Asesor de Moda por Línea de Comandos

Este proyecto es un sistema experto simple implementado en C que funciona como un asesor de moda. El programa solicita al usuario que ingrese dos características de vestimenta o personales (color de ojos, color de pantalones o color de camiseta) y, basándose en una tabla de combinaciones lógicas, recomienda el valor de la tercera característica.

## Características Principales
*   **Interfaz Interactiva por Consola:** Guía al usuario a través de menús numéricos para seleccionar las características y sus respectivos colores.
*   **Validación de Entradas:** Verifica que el usuario no seleccione la misma característica dos veces y que las opciones de color elegidas sean válidas.
*   **Lógica de Decisión Basada en Reglas:** Utiliza un sistema de lógica anidada para determinar la recomendación correcta basándose en las dos entradas del usuario.
*   **Bucle Continuo:** El programa se ejecuta en un ciclo infinito, permitiendo al usuario probar nuevas combinaciones sin necesidad de reiniciar la aplicación.

## Lógica de Funcionamiento
El núcleo del programa reside en su estructura de control de flujo, que procesa las entradas del usuario en varias etapas:

1.  **Recolección de Datos:**
    *   Un bucle `for` se ejecuta dos veces para solicitar al usuario que elija dos características distintas (de las tres disponibles: Ojos, Pantalones, Camiseta).
    *   Dentro de este bucle, un `switch` dirige al usuario a un submenú específico para seleccionar el color correspondiente a la característica elegida.
    *   Las selecciones del usuario (tanto el tipo de característica como el color) se almacenan en arreglos.

2.  **Procesamiento de Reglas:**
    *   Para determinar qué característica debe recomendarse, el programa multiplica los identificadores numéricos de las dos características seleccionadas. Este producto (`mult_Carac`) sirve como clave principal para una sentencia `switch` externa.
    *   Por ejemplo, si el usuario elige Ojos (1) y Pantalones (2), el producto es 2. Si elige Ojos (1) y Camiseta (3), el producto es 3.
    *   Dentro de cada `case` de este `switch` principal, se anidan más sentencias `switch` e `if` para desglosar la combinación exacta de colores que el usuario ingresó.

3.  **Generación de la Recomendación:**
    *   Navegando a través de esta estructura lógica anidada, el programa finalmente llega a una sentencia `printf` que muestra la recomendación apropiada.
    *   Si una combinación específica no está contemplada en la tabla de reglas, se le notifica al usuario que "Esta combinacion no se encuentra en la tabla".

## Cómo Compilar y Ejecutar
El proyecto está configurado para ser compilado con CMake.

1.  **Navega a la carpeta del proyecto:**
    ```bash
    cd standard-c-projects/02-FashionAdvisorCLI
    ```

2.  **Crea una carpeta de build y entra en ella:**
    ```bash
    mkdir build && cd build
    ```

3.  **Genera los archivos de compilación y compila el proyecto:**
    ```bash
    cmake ..
    make
    ```

## Cómo Compilar y Ejecutar
El proyecto está configurado para ser compilado con CMake.

1.  **Navega a la carpeta del proyecto:**
    ```bash
    cd standard-c-projects/02-FashionAdvisorCLI
    ```

2.  **Crea una carpeta de build y entra en ella:**
    ```bash
    mkdir build && cd build
    ```

3.  **Genera los archivos de compilación y compila el proyecto:**
    ```bash
    cmake ..
    make
    ```

4.  **Ejecuta el programa:**
    ```bash
    # En Linux/macOS
    ./FashionAdvisorCLI

    # En Windows Command Prompt
    FashionAdvisorCLI.exe
    ```
## Ejemplo de Flujo de Usuario
1.  El programa pide la primera característica. El usuario elige `(1) Color de ojos`.
2.  El programa pide el color. El usuario elige `(2) Brown`.
3.  El programa pide la segunda característica. El usuario elige `(2) Color de pantalones`.
4.  El programa pide el color. El usuario elige `(1) Blue`.
5.  El programa procesa la combinación (Ojos Marrones + Pantalones Azules) y muestra la recomendación: `Su color de Camiseta debe ser Pink`.
