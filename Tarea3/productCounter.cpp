#include <iostream>
#include <string>

#include "productCounter.hpp"

using namespace std;


/*****
*   bool CounterHash::helpInsert
******
*   Incrementa la cantidad del "grupo" de oferta en el primer producto que encuentre de la oferta correspondiente
*   Si ninguno de los productos equivalentes (o el producto) están en la tabla, agrega un nuevo "grupo" donde la
*   cantidad de productos en el es de 1 (el recién insertado)
******
*   Input:
*       int k : Código del producto a agregar
******
*   Returns:
*       bool, 1 si se agregó el producto, 0 si no se agregó
*****/
bool CounterHash::helpInsert(int k) {
    int start, i;
    int pos = start = h(k);
    for (i = 1; HT[pos].code != -1 && HT[pos].code != k; i++)
        pos = (start + p(k, i)) % M;
    if (HT[pos].code == k){
        HT[pos].quantity++;
        return 1;
    } else {
        HT[pos].code = k;
        HT[pos].quantity = 1;
        return 1;
    }
    return 0;
}

/*****
*   bool CounterHash::insert
******
*   Si se encuentra un producto perteneciente a esa oferta, se le suma una unidad al
*   "grupo", si no lo encuentra se crea un nuevo grupo en la tabla, donde la cantidad
*   inicial es 0
******
*   Input:
*       Sale S : Oferta correspondiente al producto a agregar
******
*   Returns:
*       bool, si la inserción fue existosa retorna 1, en caso contrario retorna 0
*****/
bool CounterHash::insert(Sale S){
    unsigned int pos = internalSearch(S);
    if(pos != (unsigned int)-1) {
        HT[pos].quantity++;
        return 1;
    } else {
        return helpInsert(S.code);
    }
}

/*****
*   unsigned int CounterHash::h
******
*   Función de hashing que retorna un numero dependiendo de la llave ingresada
******
*   Input:
*       int k : Llave ingresada
******
*   Returns:
*       unsigned int, Retorna un número menor a M para ubicar la llave
*****/
unsigned int CounterHash::h(int k){
    if(k == 0){
        return 0;
    }
    //constants that generate more intermidiate values
    const int ORDER = 6812; 
    string mid_value;
    string squared = to_string((k*ORDER)*(k*ORDER)); 
    int len = squared.length();
    for(int i = 0; i < len; i++){
        if(i >= (len / 2) - 3 && i <= (len / 2) + 4){
            mid_value += squared[i];
        }
    }

    return  (unsigned int)(stoi(mid_value) % M);
}

/*****
*   unsigned int CounterHash::p
******
*   Método de resolución de colisiones a través de Doble Hashing
******
*   Input:
*       int k : Llave ingresada
*       int i : Cantidad de colisiones actuales
******
*   Returns:
*       unsigned int, retorna una nueva casilla para buscar si hay colisiones
*****/
unsigned int CounterHash::p(int k, int i){
    return i*h2(k);
}

/*****
*   unsigned int CounterHash::h2
******
*   Segunda Función de hashing que retorna un numero dependiendo de la llave ingresada
******
*   Input:
*       int k : Llave ingresada
******
*   Returns:
*       unsigned int, Retorna un número menor a M para ubicar la llave
*****/
unsigned int CounterHash::h2(int k){
    return get_relative_prime(k);
}

/*****
*   unsigned int CounterHash::get_relative_prime
******
*   Obtiene el menor primo relativo entre el número ingresado y M (el tamaño de la tabla)
******
*   Input:
*       unsigned int X : número para el cual se busca un primo relativo con M
******
*   Returns:
*       unsigned int, retorna el menor primo relativo entre el número ingresado y M
*****/
unsigned int CounterHash::get_relative_prime(unsigned int X) {
    unsigned int i = X%M,j = 1;

    while (++i < M) {
        if (i < 2) continue;

        while (++j < M)
            if (i % j == 0 && M % j == 0) break;

        if (j == M)
            return i;

        j = 1;
    }
    return X;
}


/*****
*   Counter CounterHash::search
******
*   Busca un código y retorna el struct Counter al cual pertenece
******
*   Input:
*       int k : Código a buscar
******
*   Returns:
*       Counter, struct al cual pertenece el código a buscar,
*           si no se encuentra el primer campo (código) es -1.
*****/
Counter CounterHash::search(int k) {
    int start, i;
    Counter N = {-1,0};
    int pos = start = h(k);
    for (i = 1; HT[pos].code != -1 && HT[pos].code != k; i++)
        pos = (start + p(k, i)) % M;
    if (HT[pos].code == k)
        return HT[pos];
    return N;
}

/*****
*   unsigned int CounterHash::internalSearch
******
*   Busca el código de la oferta que le ingresan y retorna la posición
*   en la que se encuentra el grupo al cual pertenece el producto
******
*   Input:
*       Sale S : Oferta del producto a buscar
******
*   Returns:
*       unsigned int, posición en la cual se encuentra el contador del grupo, -1 si no se encuentra
*****/
unsigned int CounterHash::internalSearch(Sale S) {
    unsigned int product_counter = helpSearch(S.code);
    if (product_counter != (unsigned int)-1) {
        // Found the product
        return product_counter;
    } else {
        // Didn't find the product, search the equivalent products
        for (int i = 0; i < 10; i++) {
            if (S.equivalent_prod[i] == -1) break;

            product_counter = helpSearch(S.equivalent_prod[i]);
            if (product_counter != (unsigned int)-1) {
                // Found the equivalent product
                return product_counter;
            }
        }
    }
    return -1;
}

/*****
*   unsigned int CounterHash::helpSearch
******
*   Busca un código y retorna su posición si lo encuentra en la tabla, -1 si no está
******
*   Input:
*       int k : código a buscar
******
*   Returns:
*       unsigned int, posición del código a buscar, -1 si no está
*****/
unsigned int CounterHash::helpSearch(int k) {
    int start, i;
    int pos = start = h(k);
    for (i = 1; HT[pos].code != -1 && HT[pos].code != k; i++)
        pos = (start + p(k, i)) % M;
    if (HT[pos].code == k)
        return pos;
    return -1;
}

/*****
*   CounterHash::CounterHash
******
*   Constructor de la clase CounterHash.
******
*   Input: 
*       unsigned int N, cantidad de datos que se ingresarán en la tabla.
*****/
CounterHash::CounterHash(unsigned int N) {
    M = ceil(N/0.7);
    HT = new Counter[M];
}

/*****
*   CounterHash::~CounterHash
******
*   Destructor de la clase CounterHash.
*****/
CounterHash::~CounterHash() {
    delete [] HT;
}

/*****
*   unsigned int CounterHash::calculateDiscount
******
*   Calcula el total de descuento según los grupos equivalentes que hay en la tabla
******
*   Input:
*       SaleHash &saleTable : Tabla de hash de ofertas
*       ProductHash &productTable : Tabla de hash de productos
******
*   Returns:
*       unsigned int, Cantidad de descuento
*****/
unsigned int CounterHash::calculateDiscount(SaleHash &saleTable, ProductHash &productTable) {
    Sale sale;
    Product product;
    unsigned int discount=0;

    for (unsigned int i = 0; i < M; i ++) {
        if (HT[i].code == -1) continue;

        sale = saleTable.search(HT[i].code);
        product = productTable.search(HT[i].code);
        discount = (HT[i].quantity / sale.discount_qty) * sale.discount;
    }
    return discount;
}
