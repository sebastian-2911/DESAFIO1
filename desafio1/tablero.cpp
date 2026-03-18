#include <iostream>
#include "tablero.h"

using namespace std;

int** crear_tablero(int filas, int columnas)
{
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
{
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
{
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
