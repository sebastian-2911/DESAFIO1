#include <iostream>
#include "tablero.h"

using namespace std;

int** crear_tablero(int filas, int columnas)
{// Crea e inicializa dinámicamente un tablero de juego.
    //
    // Procedimiento:
    // 1. Reserva memoria para un arreglo de punteros (filas).
    // 2. Para cada fila, reserva memoria para las columnas.
    // 3. Inicializa todas las posiciones del tablero en 0.
    //
    // Parámetros:
    // - filas: número de filas del tablero.
    // - columnas: número de columnas del tablero.
    //
    // Retorna:
    // - Un puntero doble (int**) que representa la matriz del tablero.
    //
    // Nota:
    // Cada posición se inicializa en 0, indicando que está vacía.
    // La memoria debe liberarse posteriormente para evitar fugas.
    int** matriz = new int*[filas];

    for(int i = 0; i < filas; i++)
    {
        matriz[i] = new int[columnas];
    }

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

void dibujar_tablero(int** tablero, int filas, int columnas)
{// Muestra el tablero en consola representando su contenido binario.
    //
    // Recorre cada fila del tablero y, para cada una, evalúa sus bits
    // desde el más significativo (izquierda) hasta el menos significativo (derecha).
    //
    // Para cada bit:
    // - Si es 1, imprime "x" (celda ocupada).
    // - Si es 0, imprime "." (celda vacía).
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero.
    // - filas: número de filas.
    // - columnas: número de columnas (bits por fila).
    //
    // Nota:
    // Cada fila del tablero se interpreta como un número binario almacenado
    // en tablero[i][0], donde cada bit representa una celda.
    for(int i = 0; i < filas; i++)
    {
        for(int j = columnas - 1; j >= 0; j--)
        {
            int bit = (tablero[i][0] >> j) & 1;

            if(bit == 1) cout << "x ";
            else cout << ". ";
        }
        cout << endl;
    }
}

void comprobacion_de_medidas_del_tablero(int &filas, int &columnas)
{// Valida y ajusta las dimensiones del tablero ingresadas por el usuario.
    //
    // Procedimiento:
    // 1. Verifica que el número de filas sea al menos 8.
    //    - Si no cumple, solicita un nuevo valor hasta que sea válido.
    // 2. Verifica que el número de columnas:
    //    - Sea al menos 8.
    //    - Sea menor o igual a 32.
    //    - Sea múltiplo de 8.
    //    - Si no cumple, solicita un nuevo valor hasta que sea válido.
    //
    // Parámetros:
    // - filas: número de filas del tablero (se modifica por referencia).
    // - columnas: número de columnas del tablero (se modifica por referencia).
    //
    // Nota:
    // Se utilizan referencias para actualizar directamente los valores ingresados.
    while(filas < 8)
    {
        cout << "El numero de filas debe ser al menos 8: ";
        cin >> filas;
    }

    while(columnas < 8 || columnas > 32 || columnas % 8 != 0)
    {
        cout << "Las columnas deben ser multiplo de 8 y menor o igual a 32: ";
        cin >> columnas;
    }
}
