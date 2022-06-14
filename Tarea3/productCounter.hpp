#include "saleHashTable.cpp"
#include "productHashTable.cpp"


struct Counter {
    int code = -1;
    int quantity;
};

class CounterHash {
    private:
        unsigned int M;

        Counter *HT;

        unsigned int p(int k, int i);

        unsigned int h(int k);

        unsigned int h2(int k);

        unsigned int internalSearch(Sale S);

        unsigned int helpSearch(int k);

        bool helpInsert(int k);

        unsigned int get_relative_prime(unsigned int X);


    public:

        CounterHash(unsigned int N);

        ~CounterHash();

        bool insert(Sale S);

        Counter search(int k);

        unsigned int calculateDiscount(SaleHash &saleTable, ProductHash &productTable);

};
