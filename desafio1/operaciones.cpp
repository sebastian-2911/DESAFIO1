#include "operaciones.h"
#include "figuras.h"

void liberar_fila_del_tablero(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila >= 0 && fila < filas)
        {
            tablero[fila][0] &= ~pieza[alto_pieza - 1 - i];
        }
    }
}

void dibujar_pieza(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila >= 0 && fila < filas)
        {
            tablero[fila][0] |= pieza[alto_pieza - 1 - i];
        }
    }
}

bool frontera_izquierda(int* pieza, int alto_pieza, int columnas)
{
    int mascara = 1 << (columnas - 1);

    for(int i = 0; i < alto_pieza; i++)
    {
        if(pieza[i] & mascara)
            return true;
    }

    return false;
}

bool frontera_derecha(int* pieza, int alto_pieza)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        if(pieza[i] & 1)
            return true;
    }

    return false;
}

int** bajar_pieza(int** tablero, int filas, int* pieza, int alto_pieza, int &fila_actual)
{
    if(fila_actual + 1 >= filas)
        return tablero;

    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);
    fila_actual++;
    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);

    return tablero;
}

void mover_izquierda(int** tablero, int filas, int* pieza, int alto_pieza,
                     int fila_actual, int &desplazamiento)
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    for(int i = 0; i < alto_pieza; i++)
    {
        pieza[i] <<= 1;
    }

    desplazamiento++;
    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}

void mover_derecha(int** tablero, int filas, int* pieza, int alto_pieza,
                   int fila_actual, int &desplazamiento)
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    for(int i = 0; i < alto_pieza; i++)
    {
        pieza[i] >>= 1;
    }

    desplazamiento--;
    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}

bool colision_abajo(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila_tablero = fila_actual - i;
        int fila_siguiente = fila_tablero + 1;

        if(fila_siguiente >= filas)
            return true;

        if(fila_tablero < 0)
            continue;

        if((tablero[fila_siguiente][0] & pieza[alto_pieza - 1 - i]) != 0)
            return true;
    }

    return false;
}

bool colision_izquierda(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila < 0 || fila >= filas)
            continue;

        int pieza_movida = pieza[alto_pieza - 1 - i] << 1;

        if((tablero[fila][0] & pieza_movida) != 0)
            return true;
    }

    return false;
}

bool colision_derecha(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila < 0 || fila >= filas)
            continue;

        int pieza_movida = pieza[alto_pieza - 1 - i] >> 1;

        if((tablero[fila][0] & pieza_movida) != 0)
            return true;
    }

    return false;
}

bool colision_inicial(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila_tablero = fila_actual - i;

        if(fila_tablero < 0 || fila_tablero >= filas)
            continue;

        if((tablero[fila_tablero][0] & pieza[alto_pieza - 1 - i]) != 0)
            return true;
    }

    return false;
}

void intentar_mover_izquierda(int** tablero, int filas, int columnas,
                              int* pieza, int alto_pieza, int fila_actual, int &desplazamiento)
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    if(!colision_izquierda(tablero, filas, pieza, alto_pieza, fila_actual))
        mover_izquierda(tablero, filas, pieza, alto_pieza, fila_actual, desplazamiento);
    else
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}

void intentar_mover_derecha(int** tablero, int filas, int* pieza, int alto_pieza,
                            int fila_actual, int &desplazamiento)
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    if(!colision_derecha(tablero, filas, pieza, alto_pieza, fila_actual))
        mover_derecha(tablero, filas, pieza, alto_pieza, fila_actual, desplazamiento);
    else
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}

void limpiar_filas(int** tablero, int filas, int columnas)
{
    int mascara_llena = (1 << columnas) - 1;

    for(int i = 0; i < filas; i++)
    {
        if(tablero[i][0] == mascara_llena)
        {
            for(int j = i; j > 0; j--)
            {
                tablero[j][0] = tablero[j - 1][0];
            }

            tablero[0][0] = 0;
        }
    }
}

bool colision_rotacion(int** tablero, int filas, int* pieza_rotada, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila_tablero = fila_actual - i;

        if(fila_tablero < 0 || fila_tablero >= filas)
            return true;

        int mascara_pieza = pieza_rotada[alto_pieza - 1 - i];

        if((tablero[fila_tablero][0] & mascara_pieza) != 0)
            return true;
    }

    return false;
}

bool rotar_pieza(int** tablero, int filas, int columnas, int* &pieza, int &alto_pieza,
                 int fila_actual, int &estado_rotacion, int tipo, int desplazamiento)
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    int estado_anterior = estado_rotacion;
    estado_rotacion = (estado_rotacion % maximo_rotaciones_por_tipo(tipo)) + 1;

    int* pieza_rotada = generar_pieza_por_tipo(tipo, columnas, estado_rotacion);

    for(int i = 0; i < 4; i++)
    {
        if(desplazamiento > 0)
            pieza_rotada[i] <<= desplazamiento;

        if(desplazamiento < 0)
            pieza_rotada[i] >>= (-desplazamiento);
    }

    int alto_rotado = calcular_alto_pieza(pieza_rotada);

    if(!colision_rotacion(tablero, filas, pieza_rotada, alto_rotado, fila_actual))
    {
        delete[] pieza;
        pieza = pieza_rotada;
        alto_pieza = alto_rotado;
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
        return true;
    }
    else
    {
        delete[] pieza_rotada;
        estado_rotacion = estado_anterior;
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
        return false;
    }
}

bool puede_rotar(int tipo, int rotaciones_usadas)
{
    return rotaciones_usadas < maximo_rotaciones_por_tipo(tipo);
}

void calcular_movimientos_disponibles(int** tablero, int filas, int columnas,
                                      int* pieza, int alto_pieza, int fila_actual,
                                      int tipo, int estado_rotacion, int rotaciones_usadas,
                                      int desplazamiento,
                                      bool bloqueo_izquierda, bool bloqueo_derecha,
                                      bool &puede_izquierda,
                                      bool &puede_derecha,
                                      bool &puede_rotar_mov,
                                      bool &puede_bajar)
{
    puede_izquierda = false;
    puede_derecha = false;
    puede_rotar_mov = false;
    puede_bajar = false;

    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    if(!bloqueo_izquierda &&
        !frontera_izquierda(pieza, alto_pieza, columnas) &&
        !colision_izquierda(tablero, filas, pieza, alto_pieza, fila_actual))
    {
        puede_izquierda = true;
    }

    if(!bloqueo_derecha &&
        !frontera_derecha(pieza, alto_pieza) &&
        !colision_derecha(tablero, filas, pieza, alto_pieza, fila_actual))
    {
        puede_derecha = true;
    }

    if(!colision_abajo(tablero, filas, pieza, alto_pieza, fila_actual))
    {
        puede_bajar = true;
    }

    if(puede_rotar(tipo, rotaciones_usadas))
    {
        int siguiente_rotacion = (estado_rotacion % maximo_rotaciones_por_tipo(tipo)) + 1;
        int* pieza_rotada = generar_pieza_por_tipo(tipo, columnas, siguiente_rotacion);

        for(int i = 0; i < 4; i++)
        {
            if(desplazamiento > 0)
                pieza_rotada[i] <<= desplazamiento;

            if(desplazamiento < 0)
                pieza_rotada[i] >>= (-desplazamiento);
        }

        int alto_rotado = calcular_alto_pieza(pieza_rotada);

        if(!colision_rotacion(tablero, filas, pieza_rotada, alto_rotado, fila_actual))
        {
            puede_rotar_mov = true;
        }

        delete[] pieza_rotada;
    }

    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}
