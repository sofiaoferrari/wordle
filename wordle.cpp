#include "funciones.h"

#include <iostream>
#include <ctime>

using namespace std;

int main(){

    cout << "W O R D L E" << endl << endl;

    int intentos = 6;
    bool won = false;
    string nombre_archivo = "../vacion.txt";
    vector<string> lista = cargar_listado(nombre_archivo);

    if (lista.empty()) { //salida si listado vacio
        cout << "Ups! Hubo un error con el archivo." << endl;
        return -1; //error
    }

    srand(time(nullptr));
    int nro_random = 1 + rand()/((RAND_MAX + 1u)/lista.size());
    string palabra_random = lista.at(nro_random);

    cout << "El juego esta por comenzar! Tienes 6 intentos :)" << endl;
    cout << "Recuerda que la palabra debe ser de 5 caracteres. " << endl;

    while(intentos > 0) {

        cout << endl << "Ingrese un intento de palabra: ";
        string intento_usuario;
        getline(cin, intento_usuario); //utilizo getline para el input del usuario para no obtener errores por espacios
        cout << endl;

        if (intento_valido(intento_usuario, palabra_random, lista)){
            vector<EstadoLetra> evaluacion = evaluar_intento(intento_usuario, palabra_random);
            string resultado = respuesta_en_string(evaluacion);
            if (resultado == "+++++") {
                cout << "La palabra '" << intento_usuario << "' es la correcta." << endl;
                cout << "Ganaste!!" << endl;
                intentos = 0;
                won = true;
            } else {
                cout << resultado << endl;
                intentos--;
                cout << "Intentos restantes: " << intentos << endl; 
            }
            
        } else {
            cout << "Intento invalido" << endl;
            cout << "Intentos restantes: " << intentos << endl; 
        }

        if (intentos ==  0 && !won) 
            cout << "Ups! Te quedaste sin intentos. Vuelve a jugar." << endl;
    }

    return 0;
}