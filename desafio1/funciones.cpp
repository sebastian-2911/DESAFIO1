#include <iostream>
#include "funciones.h"

using namespace std;

int** crear_tablero(int filas, int columnas)
{
    int** matriz = new int*[filas];

    for(int i = 0; i < filas; i++)
        matriz[i] = new int[columnas];

    for(int i = 0; i < filas; i++)
        for(int j = 0; j < columnas; j++)
            matriz[i][j] = 0;

    return matriz;
}

void liberar_tablero(int** tablero, int filas)
{
    for(int i = 0; i < filas; i++)
        delete[] tablero[i];

    delete[] tablero;
}

void comprobacion_de_medidas_del_tablero(int &filas, int &columnas)
{
    while(filas < 8)
    {
        cout << "Filas minimas: 8\n";
        cin >> filas;
    }

    while(columnas < 8 || columnas % 8 != 0)
    {
        cout << "Columnas multiplo de 8\n";
        cin >> columnas;
    }
}

void dibujar_tablero(int** tablero, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = columnas-1; j >= 0; j--)
        {
            if(tablero[i][j] == 1)
                cout << "# ";
            else
                cout << ". ";
        }

        cout << endl;
    }
}

void dibujar_pieza(int** tablero,int filas,int columnas,int* pieza,int alto_pieza,int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila >= 0 && fila < filas)
        {
            for(int j = 0; j < columnas; j++)
            {
                if((pieza[alto_pieza-1-i] >> j) & 1)
                    tablero[fila][j] = 1;
            }
        }
    }
}

void limpiar_filas_de_pieza(int** tablero,int filas,int columnas,int alto_pieza,int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila >= 0 && fila < filas)
        {
            for(int j = 0; j < columnas; j++)
                tablero[fila][j] = 0;
        }
    }
}

bool frontera_izquierda(int* pieza,int alto_pieza,int columnas)
{
    int mascara = 1 << (columnas-1);

    for(int i = 0; i < alto_pieza; i++)
        if(pieza[i] & mascara)
            return true;

    return false;
}

bool frontera_derecha(int* pieza,int alto_pieza)
{
    for(int i = 0; i < alto_pieza; i++)
        if(pieza[i] & 1)
            return true;

    return false;
}

void mover_izquierda(int** tablero,int filas,int columnas,int* pieza,int alto_pieza,int fila_actual)
{
    limpiar_filas_de_pieza(tablero,filas,columnas,alto_pieza,fila_actual);

    for(int i = 0; i < alto_pieza; i++)
        pieza[i] <<= 1;

    dibujar_pieza(tablero,filas,columnas,pieza,alto_pieza,fila_actual);
}

void mover_derecha(int** tablero,int filas,int columnas,int* pieza,int alto_pieza,int fila_actual)
{
    limpiar_filas_de_pieza(tablero,filas,columnas,alto_pieza,fila_actual);

    for(int i = 0; i < alto_pieza; i++)
        pieza[i] >>= 1;

    dibujar_pieza(tablero,filas,columnas,pieza,alto_pieza,fila_actual);
}

void bajar_pieza(int** tablero,int filas,int columnas,int* pieza,int alto_pieza,int &fila_actual)
{
    limpiar_filas_de_pieza(tablero,filas,columnas,alto_pieza,fila_actual);

    fila_actual++;

    dibujar_pieza(tablero,filas,columnas,pieza,alto_pieza,fila_actual);
}
