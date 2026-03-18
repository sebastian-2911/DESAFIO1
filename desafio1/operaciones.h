#ifndef OPERACIONES_H
#define OPERACIONES_H

void liberar_fila_del_tablero(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual);
void dibujar_pieza(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual);

bool frontera_izquierda(int* pieza, int alto_pieza, int columnas);
bool frontera_derecha(int* pieza, int alto_pieza);

int** bajar_pieza(int** tablero, int filas, int* pieza, int alto_pieza, int &fila_actual);

void mover_izquierda(int** tablero, int filas, int* pieza, int alto_pieza,
                     int fila_actual, int &desplazamiento);

void mover_derecha(int** tablero, int filas, int* pieza, int alto_pieza,
                   int fila_actual, int &desplazamiento);

bool colision_abajo(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual);
bool colision_izquierda(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual);
bool colision_derecha(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual);
bool colision_inicial(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual);

void intentar_mover_izquierda(int** tablero, int filas, int columnas,
                              int* pieza, int alto_pieza, int fila_actual, int &desplazamiento);

void intentar_mover_derecha(int** tablero, int filas, int* pieza, int alto_pieza,
                            int fila_actual, int &desplazamiento);

void limpiar_filas(int** tablero, int filas, int columnas);

bool colision_rotacion(int** tablero, int filas, int* pieza_rotada, int alto_pieza, int fila_actual);

bool rotar_pieza(int** tablero, int filas, int columnas, int* &pieza, int &alto_pieza,
                 int fila_actual, int &estado_rotacion, int tipo, int desplazamiento);

bool puede_rotar(int tipo, int rotaciones_usadas);

void calcular_movimientos_disponibles(int** tablero, int filas, int columnas,
                                      int* pieza, int alto_pieza, int fila_actual,
                                      int tipo, int estado_rotacion, int rotaciones_usadas,
                                      int desplazamiento,
                                      bool bloqueo_izquierda, bool bloqueo_derecha,
                                      bool &puede_izquierda,
                                      bool &puede_derecha,
                                      bool &puede_rotar_mov,
                                      bool &puede_bajar);

#endif
