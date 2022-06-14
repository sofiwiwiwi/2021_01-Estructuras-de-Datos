#include <iostream>
#include <fstream>

using namespace std;

struct producto{
    int cod_producto;
    char nombre_producto[31];
    int precio;
};

struct oferta{
    int cod_producto;
    int cantidad_descuento;
    int descuento;
    int productos_equivalentes[10];
};

int main(){
    ofstream productos, ofertas;
    ifstream lectura, lectura2;
    int cantidadProductos = 7;
    int cantidadOfertas = 4;

    producto arregloProductos[] = {
        {1,"a", 10}, 
        {10,"b",200},
        {252,"c",150},
        {10532,"d",171},
        {5,"e",450},
        {17,"f",572},
        {1532,"g",324}
    };



    oferta arregloOfertas[] = {
        {252, 2, 50, {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}},
        {5, 3, 500, {17,1532,-1,-1,-1,-1,-1,-1,-1,-1}},
        {17, 3, 500, {5,1532,-1,-1,-1,-1,-1,-1,-1,-1}},
        {1532, 3, 500, {5,17,-1,-1,-1,-1,-1,-1,-1,-1}},
    };

    productos.open("productos.dat", ios::binary);
    productos.write((char*)&cantidadProductos, sizeof(int));
    productos.write((char*)&arregloProductos, 7*sizeof(producto));
    productos.close();

    ofertas.open("ofertas.dat", ios::binary);
    ofertas.write((char*)&cantidadOfertas, sizeof(int));
    ofertas.write((char*)&arregloOfertas, 4*sizeof(oferta));
    ofertas.close();




    return 0;
}
