#ifndef FUNCIONES_H
#define FUNCIONES_H

#endif // FUNCIONES_H
#ifndef FUNCIONES_H
#define FUNCIONES_H

int** crear_tablero(int filas, int columnas);
void liberar_tablero(int** tablero, int filas);

void comprobacion_de_medidas_del_tablero(int &filas, int &columnas);

void dibujar_tablero(int** tablero, int filas, int columnas);

void dibujar_pieza(int** tablero,
                   int filas,
                   int columnas,
                   int* pieza,
                   int alto_pieza,
                   int fila_actual);

void limpiar_filas_de_pieza(int** tablero,
                            int filas,
                            int columnas,
                            int alto_pieza,
                            int fila_actual);

bool frontera_izquierda(int* pieza, int alto_pieza, int columnas);
bool frontera_derecha(int* pieza, int alto_pieza);

void mover_izquierda(int** tablero,
                     int filas,
                     int columnas,
                     int* pieza,
                     int alto_pieza,
                     int fila_actual);

void mover_derecha(int** tablero,
                   int filas,
                   int columnas,
                   int* pieza,
                   int alto_pieza,
                   int fila_actual);

void bajar_pieza(int** tablero,
                 int filas,
                 int columnas,
                 int* pieza,
                 int alto_pieza,
                 int &fila_actual);

#endif
