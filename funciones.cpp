#include "funciones.h"
#include <vector>
#include <string>

#include <fstream>
#include <iostream>

using namespace std;

/*
 * Toma el nombre de un archivo que contiene una palabra por 
 * línea y devuelve un vector de strings con todas las palabras tal 
 * como están en el archivo.
 */
vector<string> cargar_listado(const string & nombre_archivo){
    ifstream archivo (nombre_archivo);

    if (archivo.good() == false) {
        cout << "Ups! No se pudo abrir el archivo '" << nombre_archivo << "'" << endl;
        exit(1); //sale si el archivo no se pudo abrir
    }

    vector<string> palabras = {};
    string linea;
    while (!archivo.eof()){ //itera hasta llegar al final del archivo
        getline(archivo, linea);
        if (!linea.empty()) //saltea las lineas vacias del archivo
            palabras.push_back(linea); 
    }
    
    return palabras;
}


/*
 * Toma un intento, una palabra secreta y un listado de palabras e indica si 
 * el intento es legal o no. Un intento es legal si tiene la misma longitud que la 
 * palabra secreta y si es una palabra reconocida en el listado de palabras.
 */
bool intento_valido(const string & intento, const string & palabra_secreta, const vector<string> &listado){
    if (intento.size() == palabra_secreta.size()) { //si tienen la misma cantidad de caracteres(5)
        for (string palabra : listado) {
            if (intento == palabra) //si la palabra se encuentra en el listado
                return true;
        }
    }

    return false;
}

/*
 * Toma un intento y una palabra secreta, y devuelve un vector con la 
 * respuesta para cada una de las letras del intento. Una letra del intento puede 
 * estar en el LugarCorrect si la palabra secreta tiene esa misma letra en esa 
 * posición, puede estar en un LugarIncorrecto si la palabra secreta contiene esa 
 * letra pero en otra posición, o puede estar NoPresente si la palabra secreta no 
 * contiene esa letra. 
 * Por ejemplo: si la palabra secreta es "bolsa" y el intento es "aviso", se espera 
 * que esta función devuelva el vector {LugarIncorrecto, NoPresente, NoPresente, 
 * LugarCorrecto, LugarIncorrecto}.
 */
vector<EstadoLetra> evaluar_intento(const string & intento, const string & palabra_secreta){
    vector<EstadoLetra> estado;
    
    for (char letra : intento) {

        //utilizo la funcion .find() de <string> para buscar la posicion de cada letra  
        //de la palabra intento en la palabra secreta y ver si coinciden las posiciones, 
        //sabiendo que devuelve -1 en la caso de que no se encuentre la letra en dicha palabra.
        if (palabra_secreta.find(letra) == intento.find(letra)) //coincide posicion
            estado.push_back(EstadoLetra::LugarCorrecto);
        else if (palabra_secreta.find(letra) != -1) //contiene la letra pero en otra posicion
            estado.push_back(EstadoLetra::LugarIncorrecto);
        else if (palabra_secreta.find(letra) == -1) //no contiene la letra
            estado.push_back(EstadoLetra::NoPresente);
    }

    return estado;
}

/**
 * Toma el vector de EstadoLetra que devuelve evaluar_intento 
 * y devuelve un string que se puede imprimir por pantalla para indicar 
 * esa respuesta al usuario. Se espera que LugarCorrecto se indique con 
 * el caracter "+", LugarIncorrecto con el caracter "-", y NoPresente con 
 * el caracter "X". 
 * Por ejemplo: si el vector en entrada es {LugarIncorrecto, NoPresente, 
 * NoPresente, LugarCorrecto, LugarIncorrecto} se espera que el string de 
 * salida sea "-XX+-".
 */
string respuesta_en_string(const vector<EstadoLetra> & respuesta){
    string resultado = "";
    
    //utilizo la funcion .append() de <string> para concatenar al string resultado
    //el caracter que representa cada estado de cada letra de la palabra intento.
    for (EstadoLetra estado : respuesta) { 
        if (estado == EstadoLetra::LugarCorrecto)
            resultado.append("+");
        else if (estado == EstadoLetra::LugarIncorrecto)
            resultado.append("-");
        else resultado.append("X");
    }

    return resultado;
}