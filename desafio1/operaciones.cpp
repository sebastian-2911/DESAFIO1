#include "operaciones.h"
#include "figuras.h"

void liberar_fila_del_tablero(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{   // Esta función elimina (limpia) del tablero la representación de una pieza
    // previamente colocada, utilizando operaciones a nivel de bits.
    //
    // Recorre cada fila de la pieza desde su posición actual (fila_actual)
    // y, mediante una máscara binaria, apaga (pone en 0) los bits correspondientes
    // en el tablero.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero de juego.
    // - filas: número total de filas del tablero.
    // - pieza: arreglo que contiene la forma de la pieza en formato binario.
    // - alto_pieza: altura de la pieza (número de filas que ocupa).
    // - fila_actual: posición actual (fila superior) de la pieza en el tablero.
    //
    // La operación '&= ~máscara' permite eliminar únicamente los bits de la pieza
    // sin afectar el resto del contenido del tablero.
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
{ // Esta función dibuja (coloca) una pieza en el tablero utilizando
    // operaciones a nivel de bits.
    //
    // Recorre cada fila de la pieza desde su posición actual (fila_actual)
    // y aplica una máscara binaria sobre el tablero usando la operación OR (|).
    // Esto permite "encender" los bits correspondientes a la pieza sin borrar
    // la información existente en el tablero.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero de juego.
    // - filas: número total de filas del tablero.
    // - pieza: arreglo que contiene la forma de la pieza en formato binario.
    // - alto_pieza: altura de la pieza (número de filas que ocupa).
    // - fila_actual: posición actual (fila superior) de la pieza en el tablero.
    //
    // La operación '|=' combina los bits de la pieza con los del tablero,
    // logrando que la pieza quede dibujada en la posición indicada.
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
{// Esta función verifica si una pieza está tocando el borde izquierdo del tablero.
    //
    // Se crea una máscara binaria desplazando un 1 hacia la izquierda hasta la
    // posición más significativa (columna izquierda del tablero).
    //
    // Luego, se recorre cada fila de la pieza y se usa una operación AND (&)
    // para comprobar si algún bit de la pieza ocupa esa posición.
    //
    // Si el resultado es distinto de cero en alguna fila, significa que la pieza
    // ya alcanzó el límite izquierdo.
    //
    // Retorna true si toca la frontera izquierda, false en caso contrario.
    int mascara = 1 << (columnas - 1);

    for(int i = 0; i < alto_pieza; i++)
    {
        if(pieza[i] & mascara)
            return true;
    }

    return false;
}

bool frontera_derecha(int* pieza, int alto_pieza)
{// Esta función verifica si una pieza está tocando el borde derecho del tablero.
    //
    // Recorre cada fila de la pieza y utiliza una operación AND (&) con 1,
    // lo que permite comprobar el bit menos significativo (columna derecha).
    //
    // Si en alguna fila ese bit es 1, significa que la pieza ya está ocupando
    // la última columna y no puede moverse más hacia la derecha.
    //
    // Parámetros:
    // - pieza: arreglo que representa la pieza en formato binario.
    // - alto_pieza: número de filas de la pieza.
    //
    // Retorna:
    // - true: si la pieza toca la frontera derecha.
    // - false: si aún puede moverse hacia la derecha.
    for(int i = 0; i < alto_pieza; i++)
    {
        if(pieza[i] & 1)
            return true;
    }

    return false;
}

int** bajar_pieza(int** tablero, int filas, int* pieza, int alto_pieza, int &fila_actual)
{// Esta función mueve la pieza una fila hacia abajo dentro del tablero.
    //
    // Primero verifica si la pieza ya está en el límite inferior del tablero.
    // Si no puede bajar más, simplemente retorna el tablero sin cambios.
    //
    // Si aún puede moverse:
    // 1. Elimina la pieza de su posición actual en el tablero.
    // 2. Incrementa la posición (fila_actual) para bajarla una fila.
    // 3. Vuelve a dibujar la pieza en la nueva posición.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero de juego.
    // - filas: número total de filas del tablero.
    // - pieza: arreglo con la forma de la pieza en formato binario.
    // - alto_pieza: altura de la pieza.
    // - fila_actual: referencia a la fila actual de la pieza (se actualiza).
    //
    // Retorna:
    // - El tablero con la pieza en su nueva posición.
    //
    // Nota: la función modifica directamente el tablero y la posición de la pieza.
    if(fila_actual + 1 >= filas)
        return tablero;

    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);
    fila_actual++;
    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);

    return tablero;
}

void mover_izquierda(int** tablero, int filas, int* pieza, int alto_pieza,
                     int fila_actual, int &desplazamiento)
{// Esta función desplaza la pieza una posición hacia la izquierda dentro del tablero.
    //
    // Procedimiento:
    // 1. Se elimina la pieza de su posición actual en el tablero.
    // 2. Se desplaza cada fila de la pieza un bit hacia la izquierda (<<= 1),
    //    lo que equivale a moverla una columna a la izquierda.
    // 3. Se actualiza la variable 'desplazamiento' para llevar el control del movimiento.
    // 4. Se vuelve a dibujar la pieza en la misma fila pero en su nueva posición.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero de juego.
    // - filas: número total de filas del tablero.
    // - pieza: arreglo que representa la pieza en formato binario.
    // - alto_pieza: número de filas de la pieza.
    // - fila_actual: posición vertical actual de la pieza.
    // - desplazamiento: referencia que indica cuánto se ha movido horizontalmente.
    //
    // Nota:
    // Esta función asume que ya se validó que la pieza no está en la frontera izquierda.
    // El desplazamiento se logra mediante corrimiento de bits, lo que hace la operación eficiente.
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
{// Esta función desplaza la pieza una posición hacia la derecha dentro del tablero.
    //
    // Procedimiento:
    // 1. Se elimina la pieza de su posición actual en el tablero.
    // 2. Se desplaza cada fila de la pieza un bit hacia la derecha (>>= 1),
    //    lo que equivale a moverla una columna a la derecha.
    // 3. Se actualiza la variable 'desplazamiento' para llevar el control del movimiento.
    // 4. Se vuelve a dibujar la pieza en la misma fila pero en su nueva posición.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero de juego.
    // - filas: número total de filas del tablero.
    // - pieza: arreglo que representa la pieza en formato binario.
    // - alto_pieza: número de filas de la pieza.
    // - fila_actual: posición vertical actual de la pieza.
    // - desplazamiento: referencia que indica cuánto se ha movido horizontalmente.
    //
    // Nota:
    // Esta función asume que ya se validó que la pieza no está en la frontera derecha.
    // El movimiento se realiza mediante corrimiento de bits, lo que hace la operación eficiente.
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    for(int i = 0; i < alto_pieza; i++)
    {
        pieza[i] >>= 1;
    }

    desplazamiento--;
    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}

bool colision_abajo(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{// Verifica si la pieza colisiona al moverse hacia abajo.
    //
    // Para cada fila de la pieza:
    // - Calcula la posición actual y la fila inferior.
    // - Si se sale del tablero, hay colisión.
    // - Si hay superposición de bits con el tablero (AND != 0), hay colisión.
    //
    // Retorna true si la pieza no puede bajar más, false en caso contrario.
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila_tablero = fila_actual - i;
        int fila_siguiente = fila_tablero + 1;

        if(fila_siguiente >= filas)
            return true;

        if(fila_tablero < 0)
            continue;

        if((tablero[fila_siguiente][0] & pieza[alto_pieza - 1 - i]) != 0)
            return true;
    }

    return false;
}

bool colision_izquierda(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{// Verifica si la pieza colisiona al intentar moverse hacia la izquierda.
    //
    // Recorre cada fila de la pieza y calcula su posición en el tablero.
    // Solo evalúa las filas que están dentro de los límites del tablero.
    //
    // Para cada fila válida:
    // - Desplaza la representación binaria de la pieza un bit a la izquierda (<< 1),
    //   simulando el movimiento hacia la izquierda.
    // - Realiza una operación AND (&) con el tablero para detectar si ya existe
    //   un bloque en esa nueva posición.
    //
    // Si en alguna fila hay superposición de bits, se detecta colisión.
    //
    // Retorna:
    // - true: si la pieza no puede moverse a la izquierda.
    // - false: si el movimiento es válido.
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila < 0 || fila >= filas)
            continue;

        int pieza_movida = pieza[alto_pieza - 1 - i] << 1;

        if((tablero[fila][0] & pieza_movida) != 0)
            return true;
    }

    return false;
}

bool colision_derecha(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{// Verifica si la pieza colisiona al intentar moverse hacia la derecha.
    //
    // Recorre cada fila de la pieza y calcula su posición en el tablero.
    // Solo evalúa las filas que están dentro de los límites.
    //
    // Para cada fila válida:
    // - Desplaza la pieza un bit hacia la derecha (>> 1),
    //   simulando el movimiento.
    // - Compara con el tablero usando AND (&) para detectar superposición.
    //
    // Si algún bit coincide, hay colisión.
    //
    // Retorna:
    // - true: si la pieza no puede moverse a la derecha.
    // - false: si el movimiento es válido.
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila = fila_actual - i;

        if(fila < 0 || fila >= filas)
            continue;

        int pieza_movida = pieza[alto_pieza - 1 - i] >> 1;

        if((tablero[fila][0] & pieza_movida) != 0)
            return true;
    }

    return false;
}

bool colision_inicial(int** tablero, int filas, int* pieza, int alto_pieza, int fila_actual)
{// Verifica si hay colisión al colocar inicialmente la pieza en el tablero.
    //
    // Recorre cada fila de la pieza y calcula su posición correspondiente
    // en el tablero. Solo evalúa las filas que están dentro de los límites.
    //
    // Para cada fila válida:
    // - Compara la pieza con el tablero usando AND (&).
    // - Si hay superposición de bits, significa que ya existe un bloque
    //   en esa posición.
    //
    // Retorna:
    // - true: si la pieza colisiona al aparecer.
    // - false: si puede colocarse sin problema.
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila_tablero = fila_actual - i;

        if(fila_tablero < 0 || fila_tablero >= filas)
            continue;

        if((tablero[fila_tablero][0] & pieza[alto_pieza - 1 - i]) != 0)
            return true;
    }

    return false;
}

void intentar_mover_izquierda(int** tablero, int filas, int columnas,
                              int* pieza, int alto_pieza, int fila_actual, int &desplazamiento)
{// Intenta mover la pieza una posición hacia la izquierda de forma segura.
    //
    // Procedimiento:
    // 1. Elimina la pieza de su posición actual en el tablero.
    // 2. Verifica si al moverse a la izquierda habría colisión.
    // 3. Si no hay colisión, realiza el movimiento.
    // 4. Si hay colisión, vuelve a dibujar la pieza en su posición original.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero.
    // - filas, columnas: dimensiones del tablero.
    // - pieza: arreglo binario que representa la pieza.
    // - alto_pieza: altura de la pieza.
    // - fila_actual: posición vertical actual.
    // - desplazamiento: controla el movimiento horizontal.
    //
    // Nota:
    // Esta función evita que la pieza atraviese otras o salga del tablero,
    // asegurando un movimiento válido hacia la izquierda.
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    if(!colision_izquierda(tablero, filas, pieza, alto_pieza, fila_actual))
        mover_izquierda(tablero, filas, pieza, alto_pieza, fila_actual, desplazamiento);
    else
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}

void intentar_mover_derecha(int** tablero, int filas, int* pieza, int alto_pieza,
                            int fila_actual, int &desplazamiento)
{// Intenta mover la pieza una posición hacia la derecha de forma segura.
    //
    // Procedimiento:
    // 1. Elimina la pieza de su posición actual en el tablero.
    // 2. Verifica si al moverse a la derecha habría colisión.
    // 3. Si no hay colisión, realiza el movimiento.
    // 4. Si hay colisión, vuelve a dibujar la pieza en su posición original.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero.
    // - filas: número de filas del tablero.
    // - pieza: arreglo binario que representa la pieza.
    // - alto_pieza: altura de la pieza.
    // - fila_actual: posición vertical actual.
    // - desplazamiento: controla el movimiento horizontal.
    //
    // Nota:
    // Esta función asegura que la pieza no atraviese otras piezas ni salga
    // del tablero al moverse hacia la derecha.
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    if(!colision_derecha(tablero, filas, pieza, alto_pieza, fila_actual))
        mover_derecha(tablero, filas, pieza, alto_pieza, fila_actual, desplazamiento);
    else
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}

void limpiar_filas(int** tablero, int filas, int columnas)
{// Elimina las filas completas del tablero y hace que las superiores bajen.
    //
    // Primero crea una máscara con todos los bits en 1, que representa una fila llena.
    // Luego recorre cada fila del tablero:
    //
    // - Si una fila está completamente llena:
    //   1. Desplaza todas las filas superiores una posición hacia abajo.
    //   2. Limpia la fila superior (la pone en 0).
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero.
    // - filas: número total de filas.
    // - columnas: número de columnas (bits por fila).
    //
    // Nota:
    // Una fila se considera llena cuando todos sus bits están en 1.
    // El corrimiento simula el efecto clásico de Tetris al eliminar filas.
    int mascara_llena = (1 << columnas) - 1;

    for(int i = 0; i < filas; i++)
    {
        if(tablero[i][0] == mascara_llena)
        {
            for(int j = i; j > 0; j--)
            {
                tablero[j][0] = tablero[j - 1][0];
            }

            tablero[0][0] = 0;
        }
    }
}

bool colision_rotacion(int** tablero, int filas, int* pieza_rotada, int alto_pieza, int fila_actual)
{// Verifica si una pieza rotada colisiona al intentar colocarse en el tablero.
    //
    // Recorre cada fila de la pieza rotada y calcula su posición en el tablero.
    //
    // Para cada fila:
    // - Si la posición está fuera de los límites del tablero, hay colisión.
    // - Compara la pieza rotada con el tablero usando AND (&).
    // - Si hay superposición de bits, existe colisión.
    //
    // Parámetros:
    // - tablero: matriz que representa el tablero.
    // - filas: número total de filas.
    // - pieza_rotada: arreglo binario de la pieza ya rotada.
    // - alto_pieza: altura de la pieza.
    // - fila_actual: posición vertical donde se intenta colocar.
    //
    // Retorna:
    // - true: si la rotación genera colisión.
    // - false: si la rotación es válida.
    for(int i = 0; i < alto_pieza; i++)
    {
        int fila_tablero = fila_actual - i;

        if(fila_tablero < 0 || fila_tablero >= filas)
            return true;

        int mascara_pieza = pieza_rotada[alto_pieza - 1 - i];

        if((tablero[fila_tablero][0] & mascara_pieza) != 0)
            return true;
    }

    return false;
}

bool rotar_pieza(int** tablero, int filas, int columnas, int* &pieza, int &alto_pieza,
                 int fila_actual, int &estado_rotacion, int tipo, int desplazamiento)
{// Intenta rotar la pieza actual y verifica si la nueva orientación es válida.
    //
    // Procedimiento:
    // 1. Elimina la pieza actual del tablero.
    // 2. Guarda el estado de rotación anterior.
    // 3. Calcula el siguiente estado de rotación según el tipo de pieza.
    // 4. Genera la nueva pieza rotada.
    // 5. Ajusta su posición horizontal según el desplazamiento.
    // 6. Calcula la nueva altura de la pieza rotada.
    // 7. Verifica si la rotación produce colisión:
    //
    //    - Si NO hay colisión:
    //      * Reemplaza la pieza actual por la rotada.
    //      * Actualiza su altura.
    //      * Dibuja la nueva pieza en el tablero.
    //      * Retorna true.
    //
    //    - Si hay colisión:
    //      * Libera la memoria de la pieza rotada.
    //      * Restaura el estado de rotación anterior.
    //      * Redibuja la pieza original.
    //      * Retorna false.
    //
    // Parámetros:
    // - tablero: matriz del juego.
    // - filas, columnas: dimensiones del tablero.
    // - pieza: referencia al arreglo de la pieza actual.
    // - alto_pieza: altura actual de la pieza.
    // - fila_actual: posición vertical.
    // - estado_rotacion: estado actual de rotación (se actualiza).
    // - tipo: tipo de pieza (define sus rotaciones).
    // - desplazamiento: posición horizontal actual.
    //
    // Nota:
    // La función maneja memoria dinámica y asegura que la rotación solo se aplique
    // si es válida, evitando solapamientos o salidas del tablero.
    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    int estado_anterior = estado_rotacion;
    estado_rotacion = (estado_rotacion % maximo_rotaciones_por_tipo(tipo)) + 1;

    int* pieza_rotada = generar_pieza_por_tipo(tipo, columnas, estado_rotacion);

    for(int i = 0; i < 4; i++)
    {
        if(desplazamiento > 0)
            pieza_rotada[i] <<= desplazamiento;

        if(desplazamiento < 0)
            pieza_rotada[i] >>= (-desplazamiento);
    }

    int alto_rotado = calcular_alto_pieza(pieza_rotada);

    if(!colision_rotacion(tablero, filas, pieza_rotada, alto_rotado, fila_actual))
    {
        delete[] pieza;
        pieza = pieza_rotada;
        alto_pieza = alto_rotado;
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
        return true;
    }
    else
    {
        delete[] pieza_rotada;
        estado_rotacion = estado_anterior;
        dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
        return false;
    }
}

bool puede_rotar(int tipo, int rotaciones_usadas)
{// Verifica si una pieza aún puede rotar según su tipo.
    //
    // Compara el número de rotaciones realizadas con el máximo permitido
    // para ese tipo de pieza.
    //
    // Parámetros:
    // - tipo: tipo de pieza.
    // - rotaciones_usadas: cantidad de rotaciones realizadas.
    //
    // Retorna:
    // - true: si aún puede rotar.
    // - false: si ya alcanzó su límite de rotaciones.
    return rotaciones_usadas < maximo_rotaciones_por_tipo(tipo);
}

void calcular_movimientos_disponibles(int** tablero, int filas, int columnas,
                                      int* pieza, int alto_pieza, int fila_actual,
                                      int tipo, int estado_rotacion, int rotaciones_usadas,
                                      int desplazamiento,
                                      bool bloqueo_izquierda, bool bloqueo_derecha,
                                      bool &puede_izquierda,
                                      bool &puede_derecha,
                                      bool &puede_rotar_mov,
                                      bool &puede_bajar)
{
    puede_izquierda = false;
    puede_derecha = false;
    puede_rotar_mov = false;
    puede_bajar = false;

    liberar_fila_del_tablero(tablero, filas, pieza, alto_pieza, fila_actual);

    if(!bloqueo_izquierda &&
        !frontera_izquierda(pieza, alto_pieza, columnas) &&
        !colision_izquierda(tablero, filas, pieza, alto_pieza, fila_actual))
    {
        puede_izquierda = true;
    }

    if(!bloqueo_derecha &&
        !frontera_derecha(pieza, alto_pieza) &&
        !colision_derecha(tablero, filas, pieza, alto_pieza, fila_actual))
    {
        puede_derecha = true;
    }

    if(!colision_abajo(tablero, filas, pieza, alto_pieza, fila_actual))
    {
        puede_bajar = true;
    }

    if(puede_rotar(tipo, rotaciones_usadas))
    {
        int siguiente_rotacion = (estado_rotacion % maximo_rotaciones_por_tipo(tipo)) + 1;
        int* pieza_rotada = generar_pieza_por_tipo(tipo, columnas, siguiente_rotacion);

        for(int i = 0; i < 4; i++)
        {
            if(desplazamiento > 0)
                pieza_rotada[i] <<= desplazamiento;

            if(desplazamiento < 0)
                pieza_rotada[i] >>= (-desplazamiento);
        }

        int alto_rotado = calcular_alto_pieza(pieza_rotada);

        if(!colision_rotacion(tablero, filas, pieza_rotada, alto_rotado, fila_actual))
        {
            puede_rotar_mov = true;
        }

        delete[] pieza_rotada;
    }

    dibujar_pieza(tablero, filas, pieza, alto_pieza, fila_actual);
}
