#include <iostream>
#include <cstdlib>

#include "tablero.h"
#include "figuras.h"
#include "operaciones.h"

using namespace std;

int main()
{
    int filas, columnas, tipo;
    cout << "Ingrese el tamano de filas en el tablero: ";
    cin >> filas;
    cout << "Ingrese el tamano de columnas del tablero: ";
    cin >> columnas;

    comprobacion_de_medidas_del_tablero(filas, columnas);

    int semilla = (filas * 29) + (columnas * 11) + (filas + columnas);
    srand(semilla);

    int** tablero = crear_tablero(filas, columnas);

    tipo = rand() % 7;
    int estado_rotacion = 1;

    int* pieza_actual = generar_pieza_por_tipo(tipo, columnas, estado_rotacion);
    int alto_de_pieza = calcular_alto_pieza(pieza_actual);
    int fila_actual = -1;

    char accion = ' ';
    int desplazamiento = 0;

    bool bloqueo_izquierda = false;
    bool bloqueo_derecha = false;
    int rotaciones_usadas = 0;
    bool fin_del_juego = false;
    bool fase_terminal = false;

    bool puede_izquierda = false;
    bool puede_derecha = false;
    bool puede_rotar_mov = false;
    bool puede_bajar = false;

    dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);

    while(accion != 'q')
    {
        calcular_movimientos_disponibles(tablero, filas, columnas,
                                         pieza_actual, alto_de_pieza, fila_actual,
                                         tipo, estado_rotacion, rotaciones_usadas,
                                         desplazamiento,
                                         bloqueo_izquierda, bloqueo_derecha,
                                         puede_izquierda, puede_derecha,
                                         puede_rotar_mov, puede_bajar);

        fase_terminal = (!puede_izquierda && !puede_derecha && !puede_rotar_mov && puede_bajar);

        cout << "-------------------------------------------" << endl;
        dibujar_tablero(tablero, filas, columnas);

        cout << "s: bajar | a: izquierda | d: derecha | w: rotar | q: salir"
             << " | rotaciones disponibles: "
             << (maximo_rotaciones_por_tipo(tipo) - rotaciones_usadas);

        if(fase_terminal)
            cout << " | FASE TERMINAL";

        cout << endl;

        cout << "Accion: ";
        cin >> accion;

        if(accion == 's')
        {
            liberar_fila_del_tablero(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);

            if(!colision_abajo(tablero, filas, pieza_actual, alto_de_pieza, fila_actual))
            {
                fila_actual++;
                dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);

                bloqueo_izquierda = false;
                bloqueo_derecha = false;
                rotaciones_usadas = 0;
                fase_terminal = false;
            }
            else
            {
                dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);

                limpiar_filas(tablero, filas, columnas);

                delete[] pieza_actual;

                tipo = rand() % 7;
                estado_rotacion = 1;
                pieza_actual = generar_pieza_por_tipo(tipo, columnas, estado_rotacion);

                alto_de_pieza = calcular_alto_pieza(pieza_actual);
                fila_actual = 0;
                desplazamiento = 0;

                bloqueo_izquierda = false;
                bloqueo_derecha = false;
                rotaciones_usadas = 0;
                fase_terminal = false;

                if(colision_inicial(tablero, filas, pieza_actual, alto_de_pieza, fila_actual))
                {
                    cout << "No caben mas piezas en el tablero. Fin del juego." << endl;
                    fin_del_juego = true;
                    break;
                }

                dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);
            }
        }

        if(accion == 'a')
        {
            if(!fase_terminal && puede_izquierda)
            {
                intentar_mover_izquierda(tablero, filas, columnas,
                                         pieza_actual, alto_de_pieza,
                                         fila_actual, desplazamiento);

                bloqueo_derecha = true;
            }
        }

        if(accion == 'd')
        {
            if(!fase_terminal && puede_derecha)
            {
                intentar_mover_derecha(tablero, filas,
                                       pieza_actual, alto_de_pieza,
                                       fila_actual, desplazamiento);

                bloqueo_izquierda = true;
            }
        }

        if(accion == 'w')
        {
            if(!fase_terminal && puede_rotar_mov)
            {
                bool roto = rotar_pieza(tablero, filas, columnas, pieza_actual,
                                        alto_de_pieza, fila_actual,
                                        estado_rotacion, tipo, desplazamiento);

                if(roto)
                {
                    bloqueo_izquierda = false;
                    bloqueo_derecha = false;
                    rotaciones_usadas++;
                }
            }
        }
    }

    delete[] pieza_actual;

    for(int i = 0; i < filas; i++)
    {
        delete[] tablero[i];
    }

    delete[] tablero;

    if(!fin_del_juego)
        cout << "Juego terminado. Gracias por jugar!" << endl;

    return 0;
}
