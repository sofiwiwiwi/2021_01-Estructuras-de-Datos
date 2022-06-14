#include <bits/stdc++.h>
#include "polynomial.hpp"


class PolynomialList {
  private:
    Polynomial *head;

    Polynomial * getPolynomial();

  public:
    PolynomialList(int size);

    ~PolynomialList();

    bool insert(unsigned int i, unsigned int E, int C);

    float evaluate(unsigned int i, float x);

    int getCoefficient(unsigned int i, unsigned int E);

};
