#include <iostream>
#include <fstream>

#include "productCounter.cpp"

using namespace std;

int main() {

    ifstream sales, products, purchases;
    ofstream bill;
    unsigned int amountOfSales, amountOfProducts, clients, amountOfPurchases, code;
    Sale sale;
    Product product;
    int total;

    //read sales file and insert in sales hash table
    sales.open("CasoPruebaT3/ofertas.dat", ios::binary);

    if (!sales.is_open()){
        cerr << "El archivo 'ofertas.dat' no se puede abrir" << endl;
        exit(1); 
    }

    sales.read((char*)&amountOfSales, sizeof(amountOfSales));
    SaleHash saleHashTable(amountOfSales);

    while(sales.read((char*)&sale, sizeof(Sale))){
        saleHashTable.insert(sale);
    }
    sales.close();

    //read product file and insert in product hash table
    products.open("CasoPruebaT3/productos.dat", ios::binary);

    if (!products.is_open()){
        cerr << "El archivo 'productos.dat' no se puede abrir" << endl;
        exit(1); 
    }

    products.read((char*)&amountOfProducts, sizeof(amountOfProducts));
    ProductHash productHashTable(amountOfProducts);

    while(products.read((char*)&product, sizeof(product))){
        productHashTable.insert(product);
    }
    products.close();
    purchases.open("CasoPruebaT3/compras.txt");
    bill.open("boletas.txt");
    if (!purchases.is_open()){
        cerr << "El archivo 'compras.txt' no se puede abrir" << endl;
        exit(1); 
    }

    purchases >> clients;
    bill << clients << endl;
    //begin read of purchases file
    for(unsigned int i = 0; i < clients; i++){
        purchases >> amountOfPurchases;
        total = 0;
        CounterHash counterHashTable(amountOfSales);
        for(unsigned int j = 0; j < amountOfPurchases; j++){
            purchases >> code;
            //asign each code to a prouduct sruct, by searching in the product hash table
            product = productHashTable.search(code);
            //check if product has sale, if it doesn't, the code will be -1 
            Sale productSale = saleHashTable.search(code);
            if(productSale.code != -1)
                counterHashTable.insert(productSale);
            total += product.price;
        }
        //subtract discount from total price, to then write it in the final bill
        total -= counterHashTable.calculateDiscount(saleHashTable, productHashTable);
        bill << total << endl;
    }
    purchases.close();
    bill.close();
    return 0;
}
