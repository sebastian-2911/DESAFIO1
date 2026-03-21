#include "figuras.h"

int* generar_pieza_O(int columnas_tablero, int estado_rotacion)
{// Genera la pieza tipo "O" (cuadrado) centrada en el tablero.
    //
    // Procedimiento:
    // 1. Calcula el centro del tablero según el número de columnas.
    // 2. Crea dinámicamente un arreglo de 4 filas inicializadas en 0.
    // 3. Genera una máscara binaria de 2x2 (dos bits en 1) usando desplazamiento.
    // 4. Asigna esta máscara a las dos primeras filas para formar el cuadrado.
    //
    // Parámetros:
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: estado de rotación (no afecta esta pieza).
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // La pieza "O" no cambia con la rotación, por lo que siempre tiene la misma forma.
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    int cuadrado = (3 << (centro - 1));

    filas[0] = cuadrado;
    filas[1] = cuadrado;

    return filas;
}

int* generar_pieza_T(int columnas_tablero, int estado_rotacion)
{// Genera la pieza tipo "T" centrada en el tablero según su estado de rotación.
    //
    // Procedimiento:
    // 1. Calcula el centro del tablero.
    // 2. Crea dinámicamente un arreglo de 4 filas inicializadas en 0.
    // 3. Según el estado de rotación (1 a 4), define la forma de la pieza
    //    usando máscaras binarias y desplazamientos:
    //
    //    - Cada número (1, 3, 7) representa bits en 1:
    //      * 1  -> 001
    //      * 3  -> 011
    //      * 7  -> 111
    //
    //    - Se desplazan hacia el centro para ubicar la pieza correctamente.
    //
    // Parámetros:
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: orientación actual de la pieza (1 a 4).
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // Cada caso del switch corresponde a una orientación distinta de la pieza "T".
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    switch(estado_rotacion)
    {
    case 1:
        filas[0] = (7 << (centro - 1));
        filas[1] = (1 << centro);
        break;

    case 2:
        filas[0] = (1 << centro);
        filas[1] = (3 << (centro - 1));
        filas[2] = (1 << centro);
        break;

    case 3:
        filas[0] = (1 << centro);
        filas[1] = (7 << (centro - 1));
        break;

    case 4:
        filas[0] = (1 << (centro - 1));
        filas[1] = (3 << (centro - 1));
        filas[2] = (1 << (centro - 1));
        break;
    }

    return filas;
}

int* generar_pieza_S(int columnas_tablero, int estado_rotacion)
{// Genera la pieza tipo "S" centrada en el tablero según su rotación.
    //
    // Procedimiento:
    // 1. Calcula el centro del tablero.
    // 2. Crea dinámicamente un arreglo de 4 filas inicializadas en 0.
    // 3. Según el estado de rotación:
    //
    //    - Rotaciones 1 y 3:
    //      * Genera la forma horizontal de la "S" usando dos filas.
    //
    //    - Rotaciones 2 y 4:
    //      * Genera la forma vertical usando tres filas.
    //
    // 4. Utiliza desplazamientos de bits para posicionar la pieza en el centro.
    //
    // Parámetros:
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: orientación de la pieza.
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // La pieza "S" tiene dos formas únicas que se repiten en sus rotaciones.
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    if(estado_rotacion == 1 || estado_rotacion == 3)
    {
        filas[0] = (3 << centro);
        filas[1] = (6 << (centro - 2));
    }
    else
    {
        filas[0] = (1 << (centro - 1));
        filas[1] = (3 << (centro - 1));
        filas[2] = (1 << centro);
    }

    return filas;
}

int* generar_pieza_Z(int columnas_tablero, int estado_rotacion)
{// Genera la pieza tipo "Z" centrada en el tablero según su rotación.
    //
    // Procedimiento:
    // 1. Calcula el centro del tablero.
    // 2. Crea dinámicamente un arreglo de 4 filas inicializadas en 0.
    // 3. Según el estado de rotación:
    //
    //    - Rotaciones 1 y 3:
    //      * Genera la forma horizontal de la "Z" usando dos filas.
    //
    //    - Rotaciones 2 y 4:
    //      * Genera la forma vertical usando tres filas.
    //
    // 4. Utiliza desplazamientos de bits para posicionar la pieza en el centro.
    //
    // Parámetros:
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: orientación de la pieza.
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // La pieza "Z" es la inversa de la "S" y también tiene dos formas únicas
    // que se repiten en sus rotaciones.
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    if(estado_rotacion == 1 || estado_rotacion == 3)
    {
        filas[0] = (6 << (centro - 2));
        filas[1] = (3 << (centro - 1));
    }
    else
    {
        filas[0] = (1 << centro);
        filas[1] = (3 << (centro - 1));
        filas[2] = (1 << (centro - 1));
    }

    return filas;
}

int* generar_pieza_L(int columnas_tablero, int estado_rotacion)
{// Genera la pieza tipo "L" centrada en el tablero según su rotación.
    //
    // Procedimiento:
    // 1. Calcula el centro del tablero.
    // 2. Crea dinámicamente un arreglo de 4 filas inicializadas en 0.
    // 3. Según el estado de rotación (1 a 4), define la forma de la pieza:
    //
    //    - Cada caso representa una orientación distinta de la "L".
    //    - Se utilizan máscaras binarias (1, 3, 7) para formar la figura.
    //    - Los desplazamientos posicionan la pieza en el centro.
    //
    // Parámetros:
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: orientación actual de la pieza.
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // La pieza "L" tiene cuatro orientaciones diferentes, controladas
    // mediante la estructura switch.
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    switch(estado_rotacion)
    {
    case 1:
        filas[0] = (1 << centro);
        filas[1] = (1 << centro);
        filas[2] = (3 << centro);
        break;

    case 2:
        filas[0] = (7 << (centro - 1));
        filas[1] = (1 << (centro + 1));
        break;

    case 3:
        filas[0] = (3 << (centro - 1));
        filas[1] = (1 << centro);
        filas[2] = (1 << centro);
        break;

    case 4:
        filas[0] = (1 << (centro - 1));
        filas[1] = (7 << (centro - 1));
        break;
    }

    return filas;
}

int* generar_pieza_J(int columnas_tablero, int estado_rotacion)
{// Genera la pieza tipo "J" centrada en el tablero según su rotación.
    //
    // Procedimiento:
    // 1. Calcula el centro del tablero.
    // 2. Crea dinámicamente un arreglo de 4 filas inicializadas en 0.
    // 3. Según el estado de rotación (1 a 4), define la forma de la pieza:
    //
    //    - Cada caso representa una orientación distinta de la "J".
    //    - Se utilizan máscaras binarias (1, 3, 7) para formar la figura.
    //    - Los desplazamientos posicionan la pieza en el centro.
    //
    // Parámetros:
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: orientación actual de la pieza.
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // La pieza "J" es la inversa de la "L" y también tiene cuatro orientaciones,
    // controladas mediante la estructura switch.
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    switch(estado_rotacion)
    {
    case 1:
        filas[0] = (1 << centro);
        filas[1] = (1 << centro);
        filas[2] = (3 << (centro - 1));
        break;

    case 2:
        filas[0] = (1 << (centro + 1));
        filas[1] = (7 << (centro - 1));
        break;

    case 3:
        filas[0] = (3 << (centro - 1));
        filas[1] = (1 << (centro - 1));
        filas[2] = (1 << (centro - 1));
        break;

    case 4:
        filas[0] = (7 << (centro - 1));
        filas[1] = (1 << (centro - 1));
        break;
    }

    return filas;
}

int* generar_pieza_I(int columnas_tablero, int estado_rotacion)
{// Genera la pieza tipo "I" centrada en el tablero según su rotación.
    //
    // Procedimiento:
    // 1. Calcula el centro del tablero.
    // 2. Crea dinámicamente un arreglo de 4 filas inicializadas en 0.
    // 3. Según el estado de rotación:
    //
    //    - Rotaciones 2 y 4:
    //      * Genera la forma horizontal usando una sola fila con 4 bits en 1.
    //
    //    - Rotaciones 1 y 3:
    //      * Genera la forma vertical usando 4 filas con un solo bit en 1.
    //
    // 4. Utiliza desplazamientos de bits para centrar la pieza.
    //
    // Parámetros:
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: orientación de la pieza.
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // La pieza "I" tiene solo dos formas únicas (horizontal y vertical)
    // que se repiten en sus rotaciones.
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    if(estado_rotacion == 2 || estado_rotacion == 4)
    {
        filas[0] = (15 << (centro - 2));
    }
    else
    {
        filas[0] = (1 << centro);
        filas[1] = (1 << centro);
        filas[2] = (1 << centro);
        filas[3] = (1 << centro);
    }

    return filas;
}

int* generar_pieza_por_tipo(int tipo, int columnas_tablero, int estado_rotacion)
{// Genera una pieza según su tipo y estado de rotación.
    //
    // Selecciona qué función de generación usar dependiendo del tipo de pieza,
    // y retorna la representación binaria correspondiente.
    //
    // Tipos de pieza:
    // - 0: O
    // - 1: T
    // - 2: S
    // - 3: Z
    // - 4: L
    // - 5: J
    // - Otro: I
    //
    // Parámetros:
    // - tipo: identifica la forma de la pieza.
    // - columnas_tablero: número de columnas del tablero.
    // - estado_rotacion: orientación de la pieza.
    //
    // Retorna:
    // - Un arreglo dinámico que representa la pieza en formato binario.
    //
    // Nota:
    // Esta función actúa como un selector central para generar cualquier tipo
    // de pieza sin necesidad de conocer su implementación interna.
    if(tipo == 0)
        return generar_pieza_O(columnas_tablero, estado_rotacion);

    if(tipo == 1)
        return generar_pieza_T(columnas_tablero, estado_rotacion);

    if(tipo == 2)
        return generar_pieza_S(columnas_tablero, estado_rotacion);

    if(tipo == 3)
        return generar_pieza_Z(columnas_tablero, estado_rotacion);

    if(tipo == 4)
        return generar_pieza_L(columnas_tablero, estado_rotacion);

    if(tipo == 5)
        return generar_pieza_J(columnas_tablero, estado_rotacion);

    return generar_pieza_I(columnas_tablero, estado_rotacion);
}

int calcular_alto_pieza(int* pieza)
{// Calcula la altura efectiva de una pieza.
    //
    // Recorre el arreglo de la pieza y cuenta cuántas filas contienen
    // al menos un bit en 1 (es decir, que no están vacías).
    //
    // Parámetros:
    // - pieza: arreglo que representa la pieza en formato binario.
    //
    // Retorna:
    // - El número de filas ocupadas por la pieza.
    //
    // Nota:
    // Solo se consideran las filas no vacías, ignorando las que están en 0.
    int alto = 0;

    for(int i = 0; i < 4; i++)
    {
        if(pieza[i] != 0)
        {
            alto++;
        }
    }

    return alto;
}

int maximo_rotaciones_por_tipo(int tipo)
{// Determina el número máximo de rotaciones posibles para un tipo de pieza.
    //
    // Según el tipo de pieza:
    // - Tipo 0 (O): solo tiene 1 rotación (no cambia).
    // - Tipos 2, 3 y 6 (S, Z, I): tienen 2 rotaciones únicas.
    // - Los demás tipos (T, L, J): tienen 4 rotaciones.
    //
    // Parámetros:
    // - tipo: identifica la pieza.
    //
    // Retorna:
    // - El número máximo de rotaciones permitidas.
    //
    // Nota:
    // Algunas piezas tienen simetrías, por lo que no todas requieren
    // las 4 rotaciones posibles.
    if(tipo == 0)
        return 1;

    if(tipo == 2 || tipo == 3 || tipo == 6)
        return 2;

    return 4;
}
