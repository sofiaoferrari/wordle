#include "funciones.h"

#include <iostream>
#include <ctime>

using namespace std;

int main(){

    cout << "W O R D L E" << endl << endl;

    int intentos = 6;
    bool gano = false; //utilizo una bandera para cuando gana el usuario
    string nombre_archivo = "../listado.txt";
    vector<string> listado = cargar_listado(nombre_archivo);

    if (listado.empty()) { //si el listado se encuentra vacio sale
        cout << "Ups! Hubo un error con el archivo." << endl;
        return -1; //error
    }
    int nro_random;

    //tomo un numero al azar utilizando .rand() 
    srand(time(nullptr));
    nro_random = rand()/((RAND_MAX + 1u)/listado.size()); //lo divido por la cantidad de elementos del listado para que me de un numero entre 0 y la cantidad de palabras contenidas en el vector
    
    string palabra_random = listado.at(nro_random); //uso la funcion .at(posicion) de <string> para obtener la palabra del vector en la posicion random obtenida anteriormente
    cout << "El juego esta por comenzar! Tienes 6 intentos :)" << endl;
    cout << "Recuerda que la palabra es de 5 letras. " << endl;

    while(intentos > 0 && !gano) { //itera mientras el usuario tenga intentos y no haya ganado

        cout << endl << "Ingrese un intento de palabra: ";
        string intento_usuario;
        getline(cin, intento_usuario); //utilizo getline para el input del usuario para no obtener errores por espacios ' '
        cout << endl;

        if (intento_valido(intento_usuario, palabra_random, listado)){
            vector<EstadoLetra> evaluacion = evaluar_intento(intento_usuario, palabra_random);
            string resultado = respuesta_en_string(evaluacion);
            if (resultado == "+++++") { //si todas las letras estan bien ubicadas
                cout << "La palabra '" << intento_usuario << "' es la correcta." << endl;
                cout << "Ganaste!!" << endl;
                gano = true; //adivino -> bandera true
            } else {
                cout << intento_usuario << endl;
                cout << resultado << endl;
                intentos--;
                cout << "Intentos restantes: " << intentos << endl; 
            }
            
        } else {
            cout << "Intento invalido" << endl;
            cout << "Intentos restantes: " << intentos << endl; 
        }

        if (intentos ==  0 ) { //si el usuario se quedo sin intentos
            cout << endl;
            cout << "Ups! Te quedaste sin intentos. Vuelve a jugar." << endl;
        }
    }

    return 0;
}