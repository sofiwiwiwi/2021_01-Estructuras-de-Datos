#include<bits/stdc++.h>
using namespace std;


class ArrExtensible {
  private:
    unsigned long length_A = 0, length_B = 0;
    int *head;

  public:
    ArrExtensible(){};

    ArrExtensible(unsigned long n);

    ArrExtensible(unsigned long n, int v);

    ~ArrExtensible();

    bool setValue(unsigned long i, int v);

    int getValue(unsigned long i);

    void append(int v);

    void remove();

    unsigned long size();

};
