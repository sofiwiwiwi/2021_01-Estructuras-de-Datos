#include <bits/stdc++.h>
#include "polynomialTree.hpp"

using namespace std;

polynomialTree::polynomialTree() {
    root = NULL;
}

polynomialTree::~polynomialTree() {
    helpDestructor(root);
}

/*****
* void polynomialTree::helpDestructor
******
* Destructor recursivo de un arbol (postorden)
******
* Input:
*   Monomial* node : Puntero a un monomio, el cual será borrado en algun punto.
*****/
void polynomialTree::helpDestructor(Monomial *node) {
    if (node == NULL) return;
    helpDestructor(node->left);
    helpDestructor(node->right);
    delete node;
}

/*****
* Monomial* polynomialTree::insert
******
* en el caso de un árbol vacío crea una raíz con el nodo a insertar,
* en caso contrario llama a insertHelp usando como parámetro la raíz
* del árbol y el exponente y coeficiente del monomio a insertar 
*.
******
* Input:
* unsigned int E : exponente del monomio a insertar
* int C : coeficiente del monomio a insertar
* .......
******
* Returns:
* node, retorna el nodo insertado en el arbol
*****/
void polynomialTree::insert(unsigned int E, int C) {
    if (root == NULL) {
        Monomial *newNode = new Monomial;
        newNode->degree = E;
        newNode->coefficient = C;
        root = newNode;
    } else {
        insertHelp(root, E, C);
    }
}

/*****
* Monomial* polynomialTree::insertHelp
******
* función auxiliar a insert si no hay raíz en el árbol, crea una y la retorna
* en otro caso la función funciona de manera recursiva hasta encontrar un nodo hoja.
******
* Input:
* Monomial* node : raiz del arbol
* unsigned int E : exponente del monomio a insertar
* int C : coeficiente del monomio a insertar
* .......
******
* Returns:
* node, retorna el nodo insertado en el arbol
*****/

Monomial* polynomialTree::insertHelp(Monomial *node, unsigned int E, int C) {
    if (node == NULL) {
        Monomial *newMonomial = new Monomial;
        newMonomial->degree = E;
        newMonomial->coefficient = C;
        return newMonomial;
    }
    if (E < node->degree) {
        node->left = insertHelp(node->left, E, C);
    } else {
        node->right = insertHelp(node->right, E, C);
    }
    return node;
}

/*****
* int polynomialTree::getCoefficientHelp
******
* función auxiliar a getCoefficient, recibe un nodo como raíz y realiza una 
búsqueda binaria para encontrar el coeficiente correspondiente al exponente
de manera recursiva
******
* Input:
* Monomial* node : puntero a un nodo del árbol
* unsigned int E : exponente de un monomio del polinomio al que le buscamos el coeficiente.
* .......
******
* Returns:
* int: coeficiente correspondiente al monomio que contiene el exponente E del polinomio.
*****/

int polynomialTree::getCoefficientHelp(Monomial* node, unsigned int E){
    if (node == NULL)  return 0;
    if(E == node->degree){
        return node->coefficient;
    }
    else if(E >node->degree){
        return getCoefficientHelp(node->right, E);
    }
    else{
        return getCoefficientHelp(node->left, E);
    }
}


/*****
* int polynomialTree::getCoefficient
******
* llama a getCoefficientHelp con parámetro la raíz del árbol
******
* Input:
* unsigned int  E : exponente de un monomio del polinomio al que le buscamos el coeficiente.
* .......
******
* Returns:
* int, coeficiente correspondiente al monomio que contiene el exponente E del polinomio.
*****/

int polynomialTree::getCoefficient(unsigned int E){
    return getCoefficientHelp(root, E);
}

/*****
* unsigned int polynomialTree::maxDegree
******
*llama a maxDegreeHelp
******
* Returns:
* unsigned int, retorna el grado más alto del polinomio
*****/

unsigned int polynomialTree::maxDegree(){
    return maxDegreeHelp(root);
}


/*****
* unsigned int polynomialTree::maxDegreeHelp
******
*función auxiliar a maxDegree 
*recorre el árbol siempre yendo al hijo derecho para encontrar el máximo exponente
******
* Input:
* monomial* node : puntero a la raíz del árbol a recorrer
* .......
******
* Returns:
* unsigned int, retorna el grado más alto del polinomio
*****/

unsigned int polynomialTree::maxDegreeHelp(Monomial* node){
    if(node == NULL){
        return 0;
    }
    while (node->right != NULL) { 
        node = node->right; 
    } 
    return node->degree;
}

/*****
* float polynomialTree::evaluate
******
* Función que consigue el valor del polinomio evaluado en "X" con el algoritmo de Horner
******
* Input:
*   float x : Valor de "X", el cual debe ser reemplazado en el polinomio
******
* Returns:
*   float, el valor del polinomio evaluado en "X" 
*****/
float polynomialTree::evaluate(float x){
    return evaluateHelp(x, root);
}

/*****
* float polynomialTree::evaluateHelp
******
* Resumen Función
******
* Input:
*   tipoParámetro NombreParámetro : Descripción Parámetro
******
* Returns:
*   TipoRetorno, Descripción retorno
*****/

float polynomialTree::evaluateHelp(float x, Monomial* node){
    float total_value = 0;
    if(node == NULL){
        return 0;
    }

    unsigned int Max = maxDegree();
    for(unsigned int i = Max; i > 0; i--){
        int coef = getCoefficient(i);
        if(coef != 0){
            total_value += coef;
            total_value *= x;
        } else {
            total_value *= x;
        }
        if (i == 1) {
            coef = getCoefficient(0);
            if (coef != 0){
                total_value += coef;
            }
        }
    }
    return total_value;
}


int main() {

    ifstream file;
    ofstream answer;
    int C, amount_of_polynomials, number_of_polynomial;
    unsigned int E, degree, size_of_polynomial;
    float X;
    string action;

    file.open("entradaPolinomio.txt");
    if (!file.is_open()) {
        cerr << "El archivo entradaPolinomio.txt no está disponible o no se puede abrir.\n";
        exit(1);
    }

    file >> amount_of_polynomials;
    polynomialTree *polynomials = new polynomialTree[amount_of_polynomials];

    for(int i = 0; i < amount_of_polynomials; i++) {
        file >> size_of_polynomial;
        for(unsigned int j = 0; j < size_of_polynomial; j++) {
            file >> E >> C;
            polynomials[i].insert(E, C);
        }
    }

    answer.open("salidaPolinomio.txt");

    if (!answer.is_open()) {
        cerr << "El archivo salidaPolinomio.txt no está disponible o no se puede abrir.\n";
        exit(1);
    }

    while(file >> action >> number_of_polynomial) {
        if (action == "COEFICIENTE") {
            file >> degree;
            answer << polynomials[number_of_polynomial].getCoefficient(degree) << endl;
        } else if (action == "EVALUAR") {
            file >> X;
            answer << polynomials[number_of_polynomial].evaluate(X) << endl;
        }
    }

    file.close();
    answer.close();

    delete [] polynomials;

    return 0;
}
