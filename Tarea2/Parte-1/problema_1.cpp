#include <bits/stdc++.h>
#include "polynomialList.hpp"

using namespace std;

Polynomial::Polynomial() {
    // Empty monomium just to make things easier
    current = head = new Monomium;
}

Polynomial::~Polynomial() {
    help_free(head);
}

/*****
* void Polynomial::help_free
******
* Libera memoria del polinomio de forma recursiva.
******
* Input:
*   Monomium *node : será un monomio del polinomio.
*****/
void Polynomial::help_free(Monomium *node) {
    if (node->next == NULL){
        delete node;
        return;
    }
    help_free(node->next);
    delete node;
}

/*****
* bool Polynomial::forward
******
* Mover el puntero de current hacia el nodo que sigue si es posible.
******
* Returns:
*   bool, true si avanzó, false si no avanzó.
*****/
bool Polynomial::forward() {
    if (current->next != NULL) {
        current = current->next;
        return true;
    }
    return false;
}

/*****
* void Polynomial::moveToStart
******
* Mueve el puntero current hacia el inicio del polinomio.
*****/
void Polynomial::moveToStart() {
    current = head;
}

/*****
* bool insert
******
* inserta un monomio en el polinomio, quedando ordenado de mayor a menor por exponente
******
* Input:
*   unsigned int E : Exponente del monomio
*   int C : Coeficiente del monomio
******
* Returns:
*   bool, true si se insertó, false si no se insertó.
*****/
bool Polynomial::insert(unsigned int E, int C) {
    moveToStart();

    Monomium *nextMonomial, *newMonomial = new Monomium;
    newMonomial->degree = E;
    newMonomial->coefficient = C;

    do {
        nextMonomial = current->next;
        if (nextMonomial == NULL || E > nextMonomial->degree) {
            newMonomial->next = nextMonomial;
            current->next = newMonomial;
            return true;
        }
    } while (forward());

    return false;
}

/*****
* void Polynomial::print
******
* Imprime el polinomio por consola.
*****/
void Polynomial::print() {
    moveToStart();
    cout << "\n";

    while (forward())
        cout << "| "<< current->degree << " | " << current->coefficient << " | -->";
    
    moveToStart();
    cout << "\n";

    while(forward())
        cout << current->coefficient << "x^" << current->degree << " ";

    cout << "\n\n";
}

/*****
* float Polynomial::evaluate
******
* Evalúa el polinomio con un valor x
******
* Input:
*   float x : valor con el cual se evaluará el polinomio
******
* Returns:
*   float, valor del polinomio al reemplazar x
*****/
float Polynomial::evaluate(float x) {
    moveToStart();
    if (!forward())
        return 0;

    float total_value = 0;
    unsigned int i, max_degree = current->degree;

    if (max_degree == 0) return current->coefficient;

    for (i = max_degree; i > 0; i--) {
        if (i == current->degree) {
            total_value += current->coefficient;
            total_value *= x;
            forward();
        } else {
            total_value *= x;
        }
    }
    if (i == 0 && current->degree == 0)
        total_value += current->coefficient;

    return total_value;
}

/*****
* int Polynomial::getCoefficient
******
* Retorna el coeficiente a^E, como un valor de tipo int.
* En caso de no existir el monomio a^E x^E en el polinomio, se produce 0 como resultado.
******
* Input:
*   unsigned int E : el exponente j para el cual buscaremos su coeficiente.
******
* Returns:
*   int, Coeficiente a si existe, 0 si no existe.
*****/
int Polynomial::getCoefficient(unsigned int E) {
    moveToStart();

    while (forward() && current->degree >= E)
        if (current->degree == E)
            return current->coefficient;
    return 0;
}

PolynomialList::PolynomialList(int size) {
    // Create Array of Polynomials
    head = new Polynomial[size];
}

PolynomialList::~PolynomialList() {
    delete[] head;
}

/*****
* bool PolynomialList::insert
******
* Llama al insert del polinomio ubicado en la posicion i para que inserte un monomio
* con exponente E y coeficiente C
******
* Input:
*   unsigned int i : Polinomio en el cual se insertará el monomio
*   unsigned int E : Exponente del monomio a insertar
*   int C : Coeficiente del monomio a insertar
******
* Returns:
*   bool, Retorna si se insertó (true) o no (false)
*****/
bool PolynomialList::insert(unsigned int i, unsigned int E, int C) {
    return head[i].insert(E, C);
}

/*****
* float PolynomialList::evaluate
******
* Evalua el polinomio i con el valor x
******
* Input:
*   unsigned int i : Polinomio a evaluar
*   unsigned int x : valor con el cual se evaluará el polinomio
******
* Returns:
*   float, resultado de evaluar el polinomio
*****/
float PolynomialList::evaluate(unsigned int i, float x) {
    //head[i].print();  // Descomentar para ver representacion de polinomio
    return head[i].evaluate(x);
}

/*****
* int PolynomialList::getCoefficient
******
* Busca el coeficiente a^E para el polinomio i
******
* Input:
*   unsigned int i : Polinomio en el cual se buscará el coeficiente
*   unsigned int E : Exponente del monomio para buscar el coeficiente
******
* Returns:
*   int, Valor de a si existe, 0 si no existe.
*****/
int PolynomialList::getCoefficient(unsigned int i, unsigned int E) {
    //head[i].print();  // Descomentar para ver representacion de polinomio
    return head[i].getCoefficient(E);
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
    PolynomialList polynomials(amount_of_polynomials);

    for(int i = 0; i < amount_of_polynomials; i++) {
        file >> size_of_polynomial;
        for(unsigned int j = 0; j < size_of_polynomial; j++) {
            file >> E >> C;
            polynomials.insert(i, E, C);
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
            answer << polynomials.getCoefficient(number_of_polynomial, degree) << endl;
        } else if (action == "EVALUAR") {
            file >> X;
            answer << polynomials.evaluate(number_of_polynomial, X) << endl;
        }
    }

    file.close();
    answer.close();

    return 0;
}
