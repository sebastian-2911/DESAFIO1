#ifndef FIGURAS_H
#define FIGURAS_H

int* generar_pieza_O(int columnas_tablero, int estado_rotacion);
int* generar_pieza_T(int columnas_tablero, int estado_rotacion);
int* generar_pieza_S(int columnas_tablero, int estado_rotacion);
int* generar_pieza_Z(int columnas_tablero, int estado_rotacion);
int* generar_pieza_L(int columnas_tablero, int estado_rotacion);
int* generar_pieza_J(int columnas_tablero, int estado_rotacion);
int* generar_pieza_I(int columnas_tablero, int estado_rotacion);

int* generar_pieza_por_tipo(int tipo, int columnas_tablero, int estado_rotacion);

int calcular_alto_pieza(int* pieza);
int maximo_rotaciones_por_tipo(int tipo);

#endif
