#ifndef TABLERO_H
#define TABLERO_H

int** crear_tablero(int filas, int columnas);
void dibujar_tablero(int** tablero, int filas, int columnas);
void comprobacion_de_medidas_del_tablero(int &filas, int &columnas);

#endif
