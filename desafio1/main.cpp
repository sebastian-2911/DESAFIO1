#include <iostream>
#include <cstdlib>
#include <ctime>

#include "figuras.h"
#include "funciones.h"

using namespace std;

int main()
{
    srand(time(0));

    int filas;
    int columnas;

    cout << "Filas:\n";
    cin >> filas;

    cout << "Columnas:\n";
    cin >> columnas;

    comprobacion_de_medidas_del_tablero(filas,columnas);

    int** tablero = crear_tablero(filas,columnas);

    int tipo = rand()%7;
    int rotacion = 1;
    int alto_pieza;

    int* pieza = generar_pieza_por_tipo(tipo,columnas,alto_pieza,rotacion);

    int fila_actual = alto_pieza-1;

    dibujar_pieza(tablero,filas,columnas,pieza,alto_pieza,fila_actual);

    char accion;

    while(true)
    {
        cout << "\n";
        dibujar_tablero(tablero,filas,columnas);

        cout << "a izquierda | d derecha | s bajar | q salir\n";
        cin >> accion;

        if(accion=='q')
            break;

        if(accion=='s')
            bajar_pieza(tablero,filas,columnas,pieza,alto_pieza,fila_actual);

        if(accion=='a' && !frontera_izquierda(pieza,alto_pieza,columnas))
            mover_izquierda(tablero,filas,columnas,pieza,alto_pieza,fila_actual);

        if(accion=='d' && !frontera_derecha(pieza,alto_pieza))
            mover_derecha(tablero,filas,columnas,pieza,alto_pieza,fila_actual);
    }

    delete[] pieza;
    liberar_tablero(tablero,filas);

    return 0;
}
