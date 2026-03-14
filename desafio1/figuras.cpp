#include "figuras.h"

int* generar_pieza_O(int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    int centro = columnas_tablero / 2;

    alto_pieza = 2;
    int* pieza = new int[alto_pieza];

    int cuadrado = (3 << (centro - 1));

    pieza[0] = cuadrado;
    pieza[1] = cuadrado;

    return pieza;
}

int* generar_pieza_T(int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* pieza;

    if(estado_rotacion == 1)
    {
        alto_pieza = 2;
        pieza = new int[alto_pieza];

        pieza[0] = (7 << (centro - 1));
        pieza[1] = (1 << centro);
    }
    else
    {
        alto_pieza = 3;
        pieza = new int[alto_pieza];

        pieza[0] = (1 << centro);
        pieza[1] = (3 << centro);
        pieza[2] = (1 << centro);
    }

    return pieza;
}

int* generar_pieza_S(int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* pieza;

    if(estado_rotacion == 1)
    {
        alto_pieza = 2;
        pieza = new int[alto_pieza];

        pieza[0] = (6 << (centro - 3));
        pieza[1] = (3 << (centro - 1));
    }
    else
    {
        alto_pieza = 3;
        pieza = new int[alto_pieza];

        pieza[0] = (1 << (centro - 1));
        pieza[1] = (3 << (centro - 1));
        pieza[2] = (1 << centro);
    }

    return pieza;
}

int* generar_pieza_Z(int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* pieza;

    if(estado_rotacion == 1)
    {
        alto_pieza = 2;
        pieza = new int[alto_pieza];

        pieza[0] = (3 << centro);
        pieza[1] = (3 << (centro - 1));
    }
    else
    {
        alto_pieza = 3;
        pieza = new int[alto_pieza];

        pieza[0] = (1 << centro);
        pieza[1] = (3 << (centro - 1));
        pieza[2] = (1 << (centro - 1));
    }

    return pieza;
}

int* generar_pieza_L(int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* pieza;

    if(estado_rotacion == 1)
    {
        alto_pieza = 3;
        pieza = new int[alto_pieza];

        pieza[0] = (1 << centro);
        pieza[1] = (1 << centro);
        pieza[2] = (3 << (centro - 1));
    }
    else
    {
        alto_pieza = 2;
        pieza = new int[alto_pieza];

        pieza[0] = (7 << (centro - 1));
        pieza[1] = (1 << (centro + 1));
    }

    return pieza;
}

int* generar_pieza_J(int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* pieza;

    if(estado_rotacion == 1)
    {
        alto_pieza = 3;
        pieza = new int[alto_pieza];

        pieza[0] = (1 << centro);
        pieza[1] = (1 << centro);
        pieza[2] = (3 << centro);
    }
    else
    {
        alto_pieza = 2;
        pieza = new int[alto_pieza];

        pieza[0] = (7 << (centro - 1));
        pieza[1] = (1 << (centro - 1));
    }

    return pieza;
}

int* generar_pieza_I(int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* pieza;

    if(estado_rotacion == 2)
    {
        alto_pieza = 1;
        pieza = new int[alto_pieza];

        pieza[0] = (15 << (centro - 2));
    }
    else
    {
        alto_pieza = 4;
        pieza = new int[alto_pieza];

        pieza[0] = (1 << centro);
        pieza[1] = (1 << centro);
        pieza[2] = (1 << centro);
        pieza[3] = (1 << centro);
    }

    return pieza;
}

int* generar_pieza_por_tipo(int tipo, int columnas_tablero, int &alto_pieza, int estado_rotacion)
{
    if(tipo == 0) return generar_pieza_O(columnas_tablero, alto_pieza, estado_rotacion);
    if(tipo == 1) return generar_pieza_T(columnas_tablero, alto_pieza, estado_rotacion);
    if(tipo == 2) return generar_pieza_S(columnas_tablero, alto_pieza, estado_rotacion);
    if(tipo == 3) return generar_pieza_Z(columnas_tablero, alto_pieza, estado_rotacion);
    if(tipo == 4) return generar_pieza_L(columnas_tablero, alto_pieza, estado_rotacion);
    if(tipo == 5) return generar_pieza_J(columnas_tablero, alto_pieza, estado_rotacion);

    return generar_pieza_I(columnas_tablero, alto_pieza, estado_rotacion);
}
