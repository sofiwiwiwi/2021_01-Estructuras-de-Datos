#include <bits/stdc++.h>

using namespace std;

struct Monomial {
    unsigned int degree;
    int coefficient;
    Monomial* left=NULL;
    Monomial* right=NULL;
};

class polynomialTree {
  private:
    Monomial *root;

  public:
    polynomialTree();

    ~polynomialTree();

    void helpDestructor(Monomial *node);

    void insert(unsigned int E, int C);

    Monomial* insertHelp(Monomial *node, unsigned int E, int C);
    
    int getCoefficient(unsigned int E);

    int getCoefficientHelp(Monomial* node, unsigned int E);

    unsigned int maxDegreeHelp(Monomial* node);

    unsigned int maxDegree();

    float evaluateHelp(float x, Monomial* node);

    float evaluate(float x);

    void print();
};
