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
