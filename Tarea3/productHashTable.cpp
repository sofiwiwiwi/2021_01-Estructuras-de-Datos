#include <iostream>
#include <string>

#include "productHashTable.hpp"

using namespace std;

/*****
*   bool ProductHash::insert
******
*   Inserta un Product en el arreglo HT, mediante las funciones h y p.
******
*   Input: 
*       Product obj, el producto a insertar
*
******
*   Returns:
*       bool, boleano que indica si la inserción fue exitosa o no.
*****/
bool ProductHash::insert(Product obj){
    int k = obj.code;
    int start, i;
    int pos = start = h(k);
    for (i = 1; HT[pos].code != -1 && HT[pos].code != k; i++){
        pos = (start + p(k, i)) % M;
    }
    if (HT[pos].code == k)
        return 0;
    else {
        HT[pos] = obj;
        return 1;
    }
}

/*****
*   Product ProductHash::search
******
*   Busca un elemento segun un codigo de producto y lo retorna si lo encuentra,
*   de lo contrario, retorna un Producto con codigo -1.
******
*   Input: 
*       int k, llave.
*
******
*   Returns:
*       Product, el producto encontrado.
*****/
Product ProductHash::search(int k) {
    int start, i;
    int pos = start = h(k);
    for (i = 1; HT[pos].code != -1 && HT[pos].code != k; i++)
        pos = (start + p(k, i)) % M;

    if (HT[pos].code == k)
        return HT[pos];
    else {
        Product N;
        return N; 
    }
}

/*****
*   unsigned int ProductHash::h
******
*   Funcion de Hashing, a través del Metodo del Cuadrado Medio indica 
*   en qué posición debería estar un Product como primera instancia.
******
*   Input: 
*       int k, llave
*
******
*   Returns:
*       unsigned int, posición donde debería estar el Product
*****/
unsigned int ProductHash::h(int k){
    if(k == 0) return 0;
    
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

    return (stoi(mid_value) % M);
}

/*****
*   unsigned int ProductHash::p
******
*   Resuelve colisiones mediante el metodo de Doble Hashing
******
*   Input: 
*       int k, llave
*       int i, numero de la iteración actual
*
******
*   Returns:
*       unsigned int, posición nueva en la cual debería estar la llave.
*****/
unsigned int ProductHash::p(int k, int i){
    return i*h2(k);
}

/*****
*   unsigned int h2
******
*   Funcion h2 necesaria para el Doble Hashing, el valor que retornará se realiza con una
*   ecuación donde participa un numero primo lo suficientemente grande para entregar 
*   valores hasta el orden de 10^3.
******
*   Input: 
*       int k, llave.
*
******
*   Returns:
*       unsigned int, multiplicador para el Doble Hashing.
*****/
unsigned int ProductHash::h2(int k){
    return get_relative_prime(k);
}

/*****
*   unsigned int ProductHash::get_relative_prime
******
*   Obtiene el menor primo relativo entre el número ingresado y M (el tamaño de la tabla)
******
*   Input:
*       unsigned int X : número para el cual se busca un primo relativo con M
******
*   Returns:
*       unsigned int, retorna el menor primo relativo entre el número ingresado y M
*****/
unsigned int ProductHash::get_relative_prime(unsigned int X) {
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
*   ProductHash
******
*   Constructor de la clase ProductHash.
*****/
ProductHash::ProductHash(unsigned int N){
    M = ceil(N/0.7);
    HT = new Product[M];
}

/*****
*   ~ProductHash
******
*   Destructor de la clase ProductHash.
*****/
ProductHash::~ProductHash(){
    delete [] HT;
}
