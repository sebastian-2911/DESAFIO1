#include <iostream>

using namespace std;

void dibujo_del_tablero(int filas, int columnas){
    char** matriz;

    matriz = new char*[filas];

    for(int i = 0; i < filas; i++)
    {
        matriz[i] = new char[columnas];
    }

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            matriz[i][j] = '.';
        }
    }

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

}
void comprobacion_de_medidas_del_tablero(int &filas, int &columnas){//como c++ no retorna 2 cosas modifico el contenido de las direciones de memoria
    while (filas<8) {
        cout<<"lo lamento pero el tamaño de filas del tablero es mu pequeno intente con un numero igual o mayoa 8 "<<endl;
        cin>>filas;
    }
    while(columnas % 8 != 0)
    {
        cout << "el numero de columnas No es multiplo de 8. Intente otra vez: ";
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
int main()
{
    int filas, columnas;

    cout << "Ingrese el tamano de filas en el tablero: " << endl;
    cin >> filas;

    cout << "Ingrese el tamano de columnas del tablero: " << endl;
    cin >> columnas;
    comprobacion_de_medidas_del_tablero(filas,columnas);

    dibujo_del_tablero(filas, columnas);

    return 0;
}
