#include <iostream>
#include <cstdlib>
#include <ctime>



using namespace std;

int** crear_tablero(int filas, int columnas)
{//crea el tablero de juego primero filas luego colucnas
    int** matriz = new int*[filas];
    //creo las filas
    for(int i = 0; i < filas; i++)
    {
        matriz[i] = new int[columnas];
    }
    //creo las colucnas
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

void dibujar_tablero(int** tablero, int filas, int columnas) {
    for(int i = 0; i < filas; i++) {
        for(int j = columnas - 1; j >= 0; j--) {

            int bit = (tablero[i][0] >> j) & 1;

            if (bit == 1) cout << "x ";
            else cout << ". ";
        }
        cout << endl;
    }
}

void comprobacion_de_medidas_del_tablero(int &filas, int &columnas)
{// comprueba q el usuario no utilize datos no validos
    while (filas < 8) {
        cout << "El numero de filas debe ser al menos 8: ";
        cin >> filas;
    }

    while (columnas > 32 || columnas % 8 != 0) {
        cout << "Las columnas deben ser multiplo de 8 y menor o igual a 32: ";
        cin >> columnas;
    }
}

int* generar_pieza_O(int columnas_tablero)
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
    int centro_tablero = columnas_tablero / 2;
    int* filas_pieza = new int[4]{0};

    switch (estado_rotacion) {
    case 1:
        filas_pieza[0] = (7 << (centro_tablero - 1));
        filas_pieza[1] = (1 << centro_tablero);
        break;

    case 2:
        filas_pieza[0] = (1 << centro_tablero);
        filas_pieza[1] = (3 << (centro_tablero - 1));
        filas_pieza[2] = (1 << centro_tablero);
        break;

    case 3:
        filas_pieza[0] = (7 << (centro_tablero - 1));
        filas_pieza[1] = (1 << centro_tablero);
        break;

    case 4:
        filas_pieza[0] = (1 << centro_tablero);
        filas_pieza[1] = (3 << centro_tablero);
        filas_pieza[2] = (1 << centro_tablero);
        break;
    }

    return filas_pieza;
}

int* generar_pieza_S(int columnas_tablero, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    if (estado_rotacion == 1) {
        filas[0] = (6 << (centro - 3));
        filas[1] = (3 << (centro - 1));
    }
    else {
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

    if (estado_rotacion == 1) {
        filas[0] = (3 << centro);
        filas[1] = (3 << (centro - 1));
    }
    else {
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

    if (estado_rotacion == 1) {
        filas[0] = (1 << centro);
        filas[1] = (1 << centro);
        filas[2] = (3 << (centro - 1));
    }
    else {
        filas[0] = (7 << (centro - 1));
        filas[1] = (1 << (centro + 1));
    }

    return filas;
}
int* generar_pieza_J(int columnas_tablero, int estado_rotacion) {
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    if (estado_rotacion == 1) {

        filas[0] = (1 << centro);
        filas[1] = (1 << centro);
        filas[2] = (3 << (centro - 1));
        return filas;
    }
    else {

        filas[0] = (7 << (centro - 1));
        filas[1] = (1 << (centro - 1));
        return filas;
    }
}
int* generar_pieza_I(int columnas_tablero, int estado_rotacion)
{
    int centro = columnas_tablero / 2;
    int* filas = new int[4]{0};

    if (estado_rotacion == 2) {
        filas[0] = (15 << (centro - 2));
    }
    else {
        filas[0] = (1 << centro);
        filas[1] = (1 << centro);
        filas[2] = (1 << centro);
        filas[3] = (1 << centro);
    }

    return filas;
}

int* generar_pieza_random(int columnas_tablero, int &tipo)
{
    tipo = rand() % 7;
    int rotacion = 1;


    if (tipo == 0)
        return generar_pieza_O(columnas_tablero);

    if (tipo == 1)
        return generar_pieza_T(columnas_tablero, rotacion);

    if (tipo == 2)
        return generar_pieza_S(columnas_tablero, rotacion);

    if (tipo == 3)
        return generar_pieza_Z(columnas_tablero, rotacion);

    if (tipo == 4)
        return generar_pieza_L(columnas_tablero, rotacion);

    if (tipo == 5)
        return generar_pieza_J(columnas_tablero, rotacion);

    return generar_pieza_I(columnas_tablero, rotacion);
}

int calcular_alto_pieza(int* pieza)
{
    int alto = 0;

    for(int i = 0; i < 4; i++)
    {//verifica si hay algo en esa pieza
        if(pieza[i] != 0)
        {
            alto++;
        }
    }

    return alto;
}
void liberar_fila_del_tablero(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{//libero la fila del tablero como si no estubiera la mascara actual
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
{// pegua la mascara al tablero usando el operador or
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila >= 0 && fila < filas)//filas es las filas q metio el ususario
        {
            tablero[fila][0] |= pieza[alto_pieza - 1 - i];
        }
    }
}
bool frontera_izquierda(int* pieza, int alto_pieza, int columnas)
{// hace un boll con la condicion a nivel de bits and para comparar filas
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

        if((tablero[fila_siguiente][0] & pieza[alto_pieza-1-i]) != 0)
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

        int pieza_movida = pieza[alto_pieza-1-i] << 1;

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

        int pieza_movida = pieza[alto_pieza-1-i] >> 1;

        if((tablero[fila][0] & pieza_movida) != 0)
            return true;
    }

    return false;
}
void intentar_mover_izquierda(int** tablero, int filas, int columnas,
                              int* pieza, int alto_pieza, int fila_actual, int &desplazamiento)
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);// libera la mascara para q no se leea a ella misma

    if(!colision_izquierda(tablero, filas, pieza, alto_pieza, fila_actual))
        mover_izquierda(tablero, filas, pieza, alto_pieza, fila_actual, desplazamiento);
    else
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}
void intentar_mover_derecha(int** tablero, int filas,int* pieza, int alto_pieza, int fila_actual, int &desplazamiento)
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    if(!colision_derecha(tablero, filas, pieza, alto_pieza, fila_actual))// si no hay
        mover_derecha(tablero, filas, pieza, alto_pieza, fila_actual, desplazamiento);
    else
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}
void limpiar_filas(int** tablero, int filas, int columnas)
{// se encarga de limipiar las filas llenas de unos
    int mascara_llena = (1 << columnas) - 1;

    for(int i = 0; i < filas; i++)
    {
        if(tablero[i][0] == mascara_llena)
        {
            tablero[i][0] = ~tablero[i][0];
            tablero[i][0] &= mascara_llena;

            for(int j = i; j > 0; j--)
            {
                tablero[j][0] = tablero[j-1][0];
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

        // Si la rotación queda fuera del tablero por arriba o abajo
        if(fila_tablero < 0 || fila_tablero >= filas)
            return true;

        // Obtenemos la máscara de la fila de la pieza rotada
        int mascara_pieza = pieza_rotada[alto_pieza - 1 - i];

        // COMPARACIÓN CLAVE: Si el AND con el tablero es != 0, hay choque
        // Reutilizamos la lógica de bits que usaste en colision_izquierda/derecha
        if((tablero[fila_tablero][0] & mascara_pieza) != 0)
            return true;
    }
    return false;
}
void rotar_pieza(int** tablero, int filas, int columnas, int* &pieza, int &alto_pieza,
                 int fila_actual, int &estado_rotacion, int tipo, int desplazamiento)//tomo la direcion de memoria del puntero de la pieza
{
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    int estado_anterior = estado_rotacion;// guardo el estado de rotacion q es un int
    estado_rotacion = (estado_rotacion % 4) + 1;

    int* pieza_rotada;//creo un puntero nuevo

    switch (tipo) {
    case 0: pieza_rotada = generar_pieza_O(columnas); break;
    case 1: pieza_rotada = generar_pieza_T(columnas, estado_rotacion); break;
    case 2: pieza_rotada = generar_pieza_S(columnas, estado_rotacion); break;
    case 3: pieza_rotada = generar_pieza_Z(columnas, estado_rotacion); break;
    case 4: pieza_rotada = generar_pieza_L(columnas, estado_rotacion); break;
    case 5: pieza_rotada = generar_pieza_J(columnas, estado_rotacion); break;
    case 6: pieza_rotada = generar_pieza_I(columnas, estado_rotacion); break;
    }
    // desplaso la mascara nueva las mismas posiciones de la mascara anterior
    for(int i = 0; i < 4; i++)
    {
        if (desplazamiento > 0)
            pieza_rotada[i] <<= desplazamiento;

        if (desplazamiento < 0)
            pieza_rotada[i] >>= (-desplazamiento);
    }

    int alto_rotado = calcular_alto_pieza(pieza_rotada);

    if(!colision_rotacion(tablero, filas, pieza_rotada, alto_rotado, fila_actual))
    {
        delete[] pieza;//libero el puntero
        pieza = pieza_rotada;//hago q apunte a la nueva pieza
        alto_pieza = alto_rotado;
    }
    else
    {
        delete[] pieza_rotada;// libero el puntero de la nueva pieza
        estado_rotacion = estado_anterior;// dejo el estado como antes
    }

    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}
int main()
{


    int filas, columnas, tipo;
    cout << "Ingrese el tamano de filas en el tablero: ";
    cin >> filas;
    cout << "Ingrese el tamano de columnas del tablero: ";
    cin >> columnas;

    comprobacion_de_medidas_del_tablero(filas, columnas);

    int** tablero = crear_tablero(filas, columnas);
    int* pieza_actual = generar_pieza_random(columnas, tipo);
    int alto_de_pieza = calcular_alto_pieza(pieza_actual);
    int fila_actual = -1;
    int estado_rotacion = 1;

    char accion = ' ';
    int desplazamiento = 0;

    dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);

    while(accion != 'q')
    {
        cout << "-------------------------------------------" << endl;
        dibujar_tablero(tablero, filas, columnas);
        cout << "s: bajar | a: izquierda | d: derecha | w: rotar | q: salir" << endl;
        cout << "Accion: ";
        cin >> accion;

        if(accion == 's')
        {
            liberar_fila_del_tablero(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);

            if(!colision_abajo(tablero, filas, pieza_actual, alto_de_pieza, fila_actual))
            {
                fila_actual++;
                dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);
            }
            else
            {
                dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);

                limpiar_filas(tablero, filas, columnas);

                delete[] pieza_actual;

                pieza_actual = generar_pieza_random(columnas, tipo);
                alto_de_pieza = calcular_alto_pieza(pieza_actual);
                fila_actual = 0;
                desplazamiento = 0;
                estado_rotacion = 1;

                dibujar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);
            }
        }

        if(accion == 'a')
        {
            if(!frontera_izquierda(pieza_actual, alto_de_pieza, columnas))
            {
                intentar_mover_izquierda(tablero, filas, columnas,
                                         pieza_actual, alto_de_pieza,
                                         fila_actual, desplazamiento);
            }
        }

        if(accion == 'd')
        {
            if(!frontera_derecha(pieza_actual, alto_de_pieza))
            {
                intentar_mover_derecha(tablero, filas,
                                       pieza_actual, alto_de_pieza,
                                       fila_actual, desplazamiento);
            }
        }

        if(accion == 'w')
        {
            rotar_pieza(tablero, filas, columnas, pieza_actual,
                        alto_de_pieza, fila_actual,
                        estado_rotacion, tipo, desplazamiento);
        }
    }

    delete[] pieza_actual;

    for(int i = 0; i < filas; i++)
    {
        delete[] tablero[i];
    }

    delete[] tablero;

    cout << "Juego terminado. Gracias por jugar!" << endl;
    return 0;
}
