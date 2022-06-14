struct Product {
    int code = -1;
    char name[31];
    int price;
};


class ProductHash {
    private:
        unsigned int M;

        Product *HT;

        unsigned int p(int k, int i);

        unsigned int h(int k);

        unsigned int h2(int k);

        unsigned int get_relative_prime(unsigned int X);

    public:

        ProductHash(unsigned int N);

        ~ProductHash();

        bool insert(Product obj);

        Product search(int k);
};
