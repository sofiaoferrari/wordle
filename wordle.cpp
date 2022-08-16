#include "funciones.h"

#include <iostream>

using namespace std;

int main(){

    string nombre_archivo = "../listado.txt";
    vector<string> lista = cargar_listado(nombre_archivo);

    int nro_random = 1 + rand()/((RAND_MAX + 1u)/36);
    string palabra_random = lista.at(nro_random);

    cout << "Ingrese un intento de palabra: ";
    string intento_usuario;
    cin >> intento_usuario;
    cout << endl;

    if (intento_valido(intento_usuario, palabra_random, lista)){
        vector<EstadoLetra> evaluacion = evaluar_intento(intento_usuario, palabra_random);
        string resultado = respuesta_en_string(evaluacion);
        cout << resultado << endl;
    } else cout << "Intento invalido" << endl;
}