#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct flujoNeto{
    int hora;
    int minuto;
    int personas;
};


int cantidadPersonas(string hora){
    /*****
    *   int cantidadPersonas
    ******
    *   A partir de una hora dada, retorna la cantidad de personas
        al interior de un local, contemplando tanto a empleados
        como a publico general.
    ******
    *   Input:
    *       string hora : string en formato hh:mm
    ******
    *   Returns:
    *       int, Cantidad de gente al interior del local en la hora ingresada.
    *****/

    flujoNeto flujo;

    fstream flujo_publico, asistencia;

    bool esta = false;
    char evento, evento_dentro;
    string hora_evento, RUT, persona_dentro;

    int inthora_h = stoi(hora.substr(0,2)); 
    int inthora_min = stoi(hora.substr(3,4));
    int cant_publico = 0;

    // Lectura de flujo-publico.dat

    flujo_publico.open("data/flujo-publico.dat", ios::in | ios::binary);
    if(!flujo_publico.is_open()){
        cerr << "Error: no se puede abrir el archivo 'flujo-publico.dat'" << endl;
        exit(1);
    }

    while(flujo_publico.read((char*)&flujo, sizeof(flujo))){
        if(flujo.hora < inthora_h)
            cant_publico += flujo.personas;
    
        else if(flujo.hora == inthora_h){
            if(flujo.minuto <= inthora_min)
                cant_publico += flujo.personas;
        }
    }

    flujo_publico.close();
    

    // Lectura de asistencia.txt
    fstream dentro;

    // Vaciar el archivo dentro.txt o crearlo
    dentro.open("data/dentro.txt", ios::out);
    if(!dentro.is_open()){
        cerr << "Error: no se puede abrir el archivo 'dentro.txt'" << endl;
        exit(1);
    }
    dentro.close();

    dentro.open("data/dentro.txt", ios::in | ios::out);
    if(!dentro.is_open()){
        cerr << "Error: no se puede abrir el archivo 'dentro.txt'" << endl;
        exit(1);
    }

    streampos inicio = dentro.tellg();
    dentro.write((char*)("           \n"),12);  // Agregar una linea vacía al inicio.

    asistencia.open("data/asistencia.txt", ios::in);
    if(!asistencia.is_open()){
        cerr << "Error: no se puede abrir el archivo 'asistencia.txt'" << endl;
        exit(1);
    }

    while(asistencia >> evento >> RUT >> hora_evento){
        esta = false;
        if (hora_evento <= hora){
            // Mover el cursor en la penúltima del archivo para recorrerlo desde el final al inicio
            // De esta manera podemos ver cual fue la ultima acción realizada por la persona
            dentro.seekg(-12,ios::end);
            if(RUT.length() == 9) // Estandarizar el largo del RUT a 10
                RUT += ' ';
            
            
            // Formato de dentro.txt:
            // <char E/S (entró, salió)><Rut>
            while(dentro.tellg() != inicio){
                evento_dentro = dentro.get(); // Saber si entró o salió
                getline(dentro, persona_dentro); // Saber quien realizó esa acción
                dentro.seekg(-24, ios::cur); // Ver el anterior ingreso/salida
                if (RUT == persona_dentro){
                    if (evento_dentro == 'E')
                        esta = true;
                    break;
                }
            }


            if (evento == 'E'){
                if (!esta){
                    if(!dentro.seekg(0, ios::end)) { // Mover el cursor al final del archivo
                        cerr  << "Error: no se pudo ir al final  del  archivo" << endl;
                        exit (1);
                    }
                    dentro << "E" << RUT << endl; // Indicar que esa persona se encuentra dentro
                    cant_publico++; 
                }
            } else if (evento == 'S') {
                if (esta) {
                    cant_publico--;
                    dentro << "S" << RUT << endl; // Indicar que esa persona salió
                }
            }
        }
    }

    asistencia.close();
    dentro.close();

    return cant_publico;
}


int main(){

    string hora;

    // Hay 18 casos de prueba en test_cases.txt
    // Se probará cada uno de ellos acá
    for(int i = 0; i < 18; i++){

        cin >> hora;

        int cantidad = cantidadPersonas(hora);

        if (cantidad == 1)
            cout << "A las " << hora << " hay " << cantidad << " persona." << endl;

        else
            cout << "A las " << hora << " hay " << cantidad << " personas." << endl;
    }

    return 0;

}
