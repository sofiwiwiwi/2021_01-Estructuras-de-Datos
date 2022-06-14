#include <bits/stdc++.h>
#include "problema_2.hpp"
using namespace std;

unsigned long b_value(unsigned long n){
    /*****
    *   unsigned long b_value
    ******
    *   Retorna el valor de 2^k para que se cumpla que
        2^(k-1) < n <= 2^k, para el menor k posible.
    ******
    *   Input:
    *       unsigned long n : Valor de n con el que se buscará k
    ******
    *   Returns:
    *       int, Valor de 2^k
    *****/

    unsigned long a = 1;
    
    while(a < n)
        a *= 2;

    return a;
}

ArrExtensible::ArrExtensible(unsigned long n) {
    length_A = n;
    length_B = b_value(n);
    head = new int[length_B];
}

ArrExtensible::ArrExtensible(unsigned long n, int v) {
    length_A = n;

    length_B = b_value(n);
    head = new int[length_B];

    while(n--)
        *(head + n) = v;
}

ArrExtensible::~ArrExtensible(){
    delete [] head;
}


bool ArrExtensible::setValue(unsigned long i, int v){
    /*****
    *   bool setValue
    ******
    *   Asigna el valor entero v a A[i] (A un objeto), para 0 ≤ i < length_A, y retorna true.
        Si i ≥ length_A, la operación no tiene ningún efecto sobre el arreglo, y retorna false.
    ******
    *   Input:
    *       unsigned long i : Posición del valor a asignar.
    *       int v : Valor a asignar.
    ******
    *   Returns:
    *       bool, Retorna si el valor fue asignado correctamente.
    *****/

    if (i >= 0 && i < length_A){
        *(head + i) = v;
        return true;
    }
    return false;
}

int ArrExtensible::getValue(unsigned long i){
    /*****
    *   int getValue
    ******
    *   Retorna A[i], para 0 ≤ i < length_A.
        Si i ≥ length_A, solamente imprime el mensaje "Error de acceso al arreglo".
    ******
    *   Input:
    *       unsigned long i : Posición a retornar.
    ******
    *   Returns:
    *       int, Valor de A[i]
    *****/

    if (i < 0 || i >= length_A){
        cerr  << "\nError de acceso al arreglo" << endl;
        exit (1);
    }

    return *(head + i);
}

void ArrExtensible::append(int v){
    /*****
    *   void append
    ******
    *   Agrega una nueva componente A[length_A] con valor entero v, haciendo crecer el arreglo.
    ******
    *   Input:
    *       int v : Valor de la nueva componente a agregar
    ******
    *   Returns:
    *       No tiene return (funcion tipo void)
    *****/

    length_A++;

    if (length_B < length_A){
        length_B *= 2;

        if (length_B == 0)
            length_B++;

        int *p;
        p = head;

        head = new int[length_B];

        for (unsigned int i = 0; i < length_A-1; i++){
            *(head + i) = *(p + i);
        }
        delete [] p;
    }

    *(head + length_A - 1) = v;
}

void ArrExtensible::remove(){
    /*****
    *   void remove
    ******
    *   Elimina el ultimo elemento del arreglo, haciendo que éste decrezca en una componente.
    *****/

    length_A--;

    if (length_B/2 >= length_A){

        length_B /= 2;

        int *p;
        p = head;

        head = new int[length_B];

        for (unsigned int i = 0; i < length_A-1; i++){
            *(head + i) = *(p + i);
        }
        delete [] p;
    }
}

unsigned long ArrExtensible::size() { 
    /*****
    *   unsigned long size
    ******
    *   Retorna el largo del arreglo A
    ******
    *   Returns:
    *       unsigned long, Largo del arreglo A
    *****/

    return length_A;
}


int main(){

    ArrExtensible A(4,1);

    cout << "\nInitial State:\n\n";
    for(unsigned long i = 0; i < A.size(); i++){
        cout << A.getValue(i) << " ";
    }
    cout << "\n";
    cout << "----------------------------------------\n\n";

    // setValue Test Cases:
    cout << "\nsetValue Test Cases:\n\n";
    A.setValue(0,1);
    A.setValue(1,2);
    A.setValue(2,3);
    A.setValue(3,4);
    for(unsigned long i = 0; i < A.size(); i++){
        cout << A.getValue(i) << " ";
    }
    cout << "\n";
    cout << "----------------------------------------\n\n";
    
    // Expected:
    // 1 1 1 1
    // 1 2 3 4

    // getValue Test Cases are in each print of the Array

    cout << "\nappend Test Cases:\n\n";
    A.append(5);
    A.append(6);
    A.append(7);
    A.append(8);
    A.append(9);
    A.append(10);
    A.append(11);
    A.append(12);
    A.append(13);
    A.append(14);
    A.append(15);
    for(unsigned long i = 0; i < A.size(); i++){
        cout << A.getValue(i) << " ";
    }
    cout << "\n";
    cout << "----------------------------------------\n\n";

    // Expected:
    // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

    cout << "\nremove Test Cases:\n\n";
    A.remove();
    A.remove();
    A.remove();
    A.remove();
    A.remove();
    for(unsigned long i = 0; i < A.size(); i++){
        cout << A.getValue(i) << " ";
    }
    cout << "\n";
    cout << "----------------------------------------\n\n";

    // Expected:
    // 1 2 3 4 5 6 7 8 9 10

    // size Test Cases are in each print of the Array

    return 0;
}
