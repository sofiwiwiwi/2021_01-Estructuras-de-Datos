/*
File to create the Polynomial TDA (just declaration)
*/

#include<bits/stdc++.h>

using namespace std;

struct Monomium {
    int coefficient;
    unsigned int degree;
    Monomium *next = NULL;
};

class Polynomial {
  private:
    unsigned int length;
    Monomium *head, *current;

    void moveToStart();

    bool forward();

    void help_free(Monomium *node);

  public:
    Polynomial();
    
    ~Polynomial();

    bool insert(unsigned int E, int C);

    float evaluate(float x);

    int getCoefficient(unsigned int E);

    void print();
};
