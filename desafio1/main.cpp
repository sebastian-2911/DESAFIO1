#include <iostream>

using namespace std;

int** crear_tablero(int filas, int columnas)
{
    int** matriz = new int*[filas];

    for(int i = 0; i < filas; i++)
    {
        matriz[i] = new int[columnas];
    }

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}
void dibujar_tablero(int** tablero, int filas, int columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = columnas - 1; j >= 0; j--)
        {
            cout << ((tablero[i][0] >> j) & 1) << ".";// va moviendo ala deerecha los bits de un numero
        }                                             //y los compara con & y 1 y si los 2 estan encendidos
        //pondra un 1 si solo esta encendido el comaparador pondra un 0
        cout << endl;
    }
}
void comprobacion_de_medidas_del_tablero(int &filas, int &columnas)
{
    while (filas < 8) {
        cout << "El numero de filas debe ser al menos 8: ";
        cin >> filas;
    }

    while (columnas > 32 || columnas % 8 != 0) {
        cout << "Las columnas deben ser multiplo de 8 y menor o igual a 32: ";
        cin >> columnas;
    }
}
int* generar_pieza_O(int columnas_tablero) {
    int centro = columnas_tablero / 2;
    int* filas = new int[2]; // El cuadrado siempre mide 2 de alto


    int cuadrado = (3 << (centro - 1));

    filas[0] = cuadrado; // Fila de arriba: ##
    filas[1] = cuadrado; // Fila de abajo:  ##

    return filas;
}
int* generar_pieza_T(int columnas_tablero, int estado_rotacion) {

    int centro_tablero = columnas_tablero / 2;
    int* filas_pieza;

    if (estado_rotacion == 1) { // T normal
        filas_pieza = new int[2];//2 filas

        filas_pieza[1] = (1 << centro_tablero);// crea el cuerpo de la t
        filas_pieza[0] = (7 << (centro_tablero - 1));//7 en binario es:111 representa la cara de la t

    } else { // T de lado
        filas_pieza = new int[3];//3 filas

        filas_pieza[0] = (1 << centro_tablero);//1
        filas_pieza[1] = (3 << centro_tablero);// el 3 en binario es 11
        filas_pieza[2] = (1 << centro_tablero);//1
    }

    return filas_pieza;
}
int* generar_pieza_S(int columnas_tablero, int estado_rotacion) {
    int centro = columnas_tablero / 2;
    int* filas;

    if (estado_rotacion == 1) { // S acostada
        filas = new int[2];             //no uso 3 para q todo este en el centro
        filas[0] = (6 << (centro - 3)); // Fila de arriba: . # # 6 en binario 110
        filas[1] = (3 << (centro - 1)); // Fila de abajo:  # # .- 2 para q se detenga antes q la fila de arriba
        return filas;
    }
    else { // S parada//90grados
        filas = new int[3];
        filas[0] = (1 << (centro - 1)); // # .
        filas[1] = (3 << (centro - 1)); // # #
        filas[2] = (1 << centro);       // . #
        return filas;
    }
}
int* generar_pieza_Z(int columnas_tablero, int estado_rotacion) {
    int centro = columnas_tablero / 2;
    int* filas;

    if (estado_rotacion == 1) { // Z acostada (Alto: 2)
        filas = new int[2];
        // 3 en binario es 11
        filas[0] = (3 << centro);       // Arriba: ##. (desplazado al centro)
        filas[1] = (3 << (centro - 1)); // Abajo:  .## (un espacio a la derecha del anterior)
        return filas;
    }
    else { // Z parada (Alto: 3)
        filas = new int[3];
        // Usamos el 1 (un bit) y el 3 (dos bits)
        filas[0] = (1 << centro);       // .#
        filas[1] = (3 << (centro - 1)); // ##
        filas[2] = (1 << (centro - 1)); // #.
        return filas;
    }
}
int* generar_pieza_L(int columnas_tablero, int estado_rotacion) {
    int centro = columnas_tablero / 2;
    int* filas;

    if (estado_rotacion == 1) {
        // POSICIÓN 1: VERTICAL (Alto: 3 filas)
        filas = new int[3];

        filas[0] = (1 << centro);       //   # .
        filas[1] = (1 << centro);       //   # .
        filas[2] = (3 << (centro - 1)); //   # # (El 3 es '11', alineado con el de arriba)
        return filas;
    }
    else {
        // POSICIÓN 2: ACOSTADA (Alto: 2 filas)
        filas = new int[2];

        // El 7 es '111' en binario
        filas[0] = (7 << (centro - 1)); // # # #
        // El 1 es '#' en binario. Lo movemos al extremo izquierdo del 7
        filas[1] = (1 << (centro + 1)); // # . .
        return filas;
    }
}
int* generar_pieza_J(int columnas_tablero, int estado_rotacion) {
    int centro = columnas_tablero / 2;
    int* filas;

    if (estado_rotacion == 1) {
        // POSICIÓN 1: VERTICAL (Alto: 3 filas)
        filas = new int[3];

        filas[0] = (1 << centro);       // . #
        filas[1] = (1 << centro);       // . #
        filas[2] = (3 << centro);       // # # (El gancho hacia el otro lado)
        return filas;
    }
    else {
        // POSICIÓN 2: ACOSTADA
        filas = new int[2];

        // El 7 es '111'
        filas[0] = (7 << (centro - 1)); // # # #
        // El 1 ahora va al extremo derecho de la barra
        filas[1] = (1 << (centro - 1)); // . . #
        return filas;
    }
}
int* generar_pieza_I(int columnas_tablero, int estado_rotacion) {
    int centro = columnas_tablero / 2;
    int* filas;

    if (estado_rotacion == 2) { // I acostada (Alto: 1)
        filas = new int[1];
        // 15 en binario es 1111
        filas[0] = (15 << (centro - 2)); // Una sola fila con 4 bits centrados
        return filas;
    }
    else { // I parada (Alto: 4)
        filas = new int[4];
        // Un solo bit (1) repetido en 4 filas para hacer la línea vertical
        filas[0] = (1 << centro);
        filas[1] = (1 << centro);
        filas[2] = (1 << centro);
        filas[3] = (1 << centro);
        return filas;
    }
}
int* generar_pieza_random(int columnas_tablero)
{
    int tipo = rand() % 7;
    int rotacion =1;

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

    // Consideramos máximo 4 filas
    while(alto < 4 && pieza[alto] != 0)
    {
        alto++;
    }

    return alto;
}
void liberar_fila_del_tablero(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        // Nos aseguramos de no salirnos del tablero
        if(fila >= 0 && fila < filas)
        {
            // Paso 1: OR entre la fila del tablero y la pieza
            int fila_con_mascara = tablero[fila][0] | pieza[alto_pieza - 1 - i];

            // Paso 2: AND con la máscara negada de la pieza
            int resultado = fila_con_mascara & ~pieza[alto_pieza - 1 - i];

            // Guardamos el resultado en el tablero
            tablero[fila][0] = resultado;
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
    // verificar frontera inferior
    if(fila_actual + 1 >= filas)
        return tablero;

    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    // bajar pieza
    fila_actual++;

    // dibujar pieza nueva
    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);

    return tablero;
}
void mover_izquierda(int** tablero, int filas, int* pieza, int alto_pieza,
                     int fila_actual, int &desplazamiento)
{
    // 1 borrar pieza actual
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    // 2 mover la máscara
    for(int i = 0; i < alto_pieza; i++)
    {
        pieza[i] <<= 1;
    }

    desplazamiento++;

    // 3 dibujar la pieza otra vez
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
int main()
{

    int filas, columnas;

    cout << "Ingrese el tamano de filas en el tablero: " << endl;
    cin >> filas;

    cout << "Ingrese el tamano de columnas del tablero: " << endl;
    cin >> columnas;
    comprobacion_de_medidas_del_tablero(filas, columnas);

    int** tablero = crear_tablero(filas,columnas);

    int* pieza_actual = generar_pieza_random(columnas);
    int alto_de_pieza = calcular_alto_pieza(pieza_actual);
    int fila_actual = -1;
    dibujar_tablero(tablero, filas, columnas);
    char accion = ' ';
    int desplazamiento=0;
    while(accion != 'q')
    {
        cout << "-------------------------------------------" << endl;
        dibujar_tablero(tablero, filas, columnas);

        cout << "s: bajar | a: izquierda | d: derecha | q: salir\n";
        cin >> accion;

        if(accion == 's')
        {
            tablero = bajar_pieza(tablero, filas, pieza_actual, alto_de_pieza, fila_actual);
        }

        if(accion == 'a')
        {
            if(!frontera_izquierda(pieza_actual, alto_de_pieza, columnas))
            {
                mover_izquierda(tablero, filas, pieza_actual, alto_de_pieza, fila_actual, desplazamiento);
            }
        }

        if(accion == 'd')
        {
            if(!frontera_derecha(pieza_actual, alto_de_pieza))
            {
                mover_derecha(tablero, filas, pieza_actual, alto_de_pieza, fila_actual, desplazamiento);
            }
        }
    }


}
