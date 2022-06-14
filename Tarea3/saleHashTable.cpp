#include <iostream>
#include <string>
#include <math.h>

#include "saleHashTable.hpp"

using namespace std;

/*****
*   bool insert
******
*   Inserta un Sale en el arreglo HT, mediante las funciones h y p.
******
*   Input: 
*       Sale sale : oferta a inserta
******
*   Returns:
*       bool, boleano que indica si la inserción fue exitosa o no.
*****/
bool SaleHash::insert(Sale sale){
    int k = sale.code;
    int start, i;
    int pos = start = h(k);
    for (i = 1; HT[pos].code != -1 && HT[pos].code != k; i++){
        pos = (start + p(k, i)) % M;
    }
    if (HT[pos].code == k)
        return 0;
    else {
        HT[pos] = sale;
        return 1;
    }
}

/*****
*   Sale search
******
*   Busca un elemento segun un codigo de producto y lo retorna si lo encuentra,
*   de lo contrario, retorna un Sale con codigo -1.
******
*   Input: 
*       int k : llave.
******
*   Returns:
*       Sale, la oferta encontrada.
*****/
Sale SaleHash::search(int k) {
    int start, i;
    int pos = start = h(k);
    for (i = 1; HT[pos].code != -1 && HT[pos].code != k; i++){
        pos = (start + p(k, i)) % M;
    }
    return HT[pos];
}

/*****
*   unsigned int h
******
*   Funcion de Hashing, a través del Metodo del Cuadrado Medio indica 
*   en qué posición debería estar un <TYPE> como primera instancia.
******
*   Input: 
*       int k : llave
******
*   Returns:
*       unsigned int, posición donde debería estar el <TYPE>
*****/
unsigned int SaleHash::h(int k){
    if(k == 0){
        return 0;
    }

    const int ORDER = 6812;
    string mid_value;
    string squared = to_string((k*ORDER)*(k*ORDER)); //Constantes que generan más valores intermedios
    int len = squared.length();
    for(int i = 0; i < len; i++){
        if(i >= (len / 2) - 3 && i <= (len / 2) + 4){
            mid_value += squared[i];
        }
    }

    return  stoi(mid_value) % M;
}

/*****
*   unsigned int p
******
*   Resuelve colisiones mediante el metodo de Doble Hashing
******
*   Input: 
*       int k : llave
*       int i : numero de la iteración actual
*
******
*   Returns:
*       unsigned int, posición nueva en la cual debería estar la llave.
*****/
unsigned int SaleHash::p(int k, int i){
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
*       int k : llave.
******
*   Returns:
*       unsigned int, multiplicador para el Doble Hashing.
*****/
unsigned int SaleHash::h2(int k){
    return get_relative_prime(k);
}

/*****
*   unsigned int SaleHash::get_relative_prime
******
*   Obtiene el menor primo relativo entre el número ingresado y M (el tamaño de la tabla)
******
*   Input:
*       unsigned int X : número para el cual se busca un primo relativo con M
******
*   Returns:
*       unsigned int, retorna el menor primo relativo entre el número ingresado y M
*****/
unsigned int SaleHash::get_relative_prime(unsigned int X) {
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
*   SaleHash
******
*   Constructor de la clase SaleHash.
*****/
SaleHash::SaleHash(unsigned int N){  
    M = ceil(N/0.7);
    HT = new Sale[M];
}

/*****
*   ~SaleHash
******
*   Destructor de la clase SaleHash.
*****/
SaleHash::~SaleHash(){
    delete [] HT;
}
