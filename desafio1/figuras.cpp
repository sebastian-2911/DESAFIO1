#include "figuras.h"

int* generar_pieza_O(int columnas_tablero, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    int cuadrado = (3 << (centro - 1));

    filas[0] = cuadrado;
    filas[1] = cuadrado;

    return filas;
}

int* generar_pieza_T(int columnas_tablero, int estado_rotacion)
{
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
{
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
{
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
{
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
{
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
{
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
{
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
{
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
{
    if(tipo == 0)
        return 1;

    if(tipo == 2 || tipo == 3 || tipo == 6)
        return 2;

    return 4;
}
