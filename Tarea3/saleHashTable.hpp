struct Sale {
    int code = -1;
    int discount_qty;
    int discount;
    int equivalent_prod[10];
};


class SaleHash {
  private:
    unsigned int M;
    
    Sale *HT;

    unsigned int p(int k, int i);

    unsigned int h(int k);

    unsigned int h2(int k);

    unsigned int get_relative_prime(unsigned int X);

  public:

    SaleHash(unsigned int N);

    ~SaleHash();

    bool insert(Sale sale);

    Sale search(int k);

    void printear();

};
