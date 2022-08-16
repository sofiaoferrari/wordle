#include "funciones.h"
#include <vector>
#include <string>

#include <fstream>
#include <iostream>

using namespace std;

/**
 * @brief toma el nombre de un archivo que contiene una palabra por 
 * línea y devuelve un vector de strings con todas las palabras tal 
 * como están en el archivo.
 * 
 * @param nombre_archivo 
 * @return vector<string> 
 */
vector<string> cargar_listado(const string & nombre_archivo){
    ifstream archivo (nombre_archivo);

    if (archivo.good() == false) {
        cout << "No se pudo abrir el archivo " << nombre_archivo << endl;
        exit(1);
    }

    vector<string> palabras = {};
    string linea;
    while (!archivo.eof()){
        getline(archivo, linea);
        if (!linea.empty())
            palabras.push_back(linea);
    }
    
    return palabras;
}


/**
 * @brief toma un intento, una palabra secreta y un listado de palabras e indica si 
 * el intento es legal o no. Un intento es legal si tiene la misma longitud que la 
 * palabra secreta y si es una palabra reconocida en el listado de palabras.
 * 
 * @param intento 
 * @param palabra_secreta 
 * @param listado 
 * @return true 
 * @return false 
 */
bool intento_valido(const string & intento, const string & palabra_secreta, const vector<string> &listado){
    if (intento.size() != palabra_secreta.size())
        return false;

    for (string palabra : listado) {
        if (intento == palabra) return true;
    }

    return false;
}

/**
 * @brief toma un intento y una palabra secreta, y devuelve un vector con la 
 * respuesta para cada una de las letras del intento. Una letra del intento puede 
 * estar en el LugarCorrect si la palabra secreta tiene esa misma letra en esa 
 * posición, puede estar en un LugarIncorrecto si la palabra secreta contiene esa 
 * letra pero en otra posición, o puede estar NoPresente si la palabra secreta no 
 * contiene esa letra. 
 * Por ejemplo: si la palabra secreta es "bolsa" y el intento es "aviso", se espera 
 * que esta función devuelva el vector {LugarIncorrecto, NoPresente, NoPresente, 
 * LugarCorrecto, LugarIncorrecto}.
 * 
 * @param intento 
 * @param palabra_secreta 
 * @return vector<EstadoLetra> 
 */
vector<EstadoLetra> evaluar_intento(const string & intento, const string & palabra_secreta){
    vector<EstadoLetra> estado;
    
    for (char letra : intento) {
        if (palabra_secreta.find(letra) == intento.find(letra)) 
            estado.push_back(EstadoLetra::LugarCorrecto);
        else if (palabra_secreta.find(letra) != -1) 
            estado.push_back(EstadoLetra::LugarIncorrecto);
        else if (palabra_secreta.find(letra) == -1) 
            estado.push_back(EstadoLetra::NoPresente);
    }

    return estado;
}

/**
 * @brief toma el vector de EstadoLetra que devuelve evaluar_intento 
 * y devuelve un string que se puede imprimir por pantalla para indicar 
 * esa respuesta al usuario. Se espera que LugarCorrecto se indique con 
 * el caracter "+", LugarIncorrecto con el caracter "-", y NoPresente con 
 * el caracter "X". 
 * Por ejemplo: si el vector en entrada es {LugarIncorrecto, NoPresente, 
 * NoPresente, LugarCorrecto, LugarIncorrecto} se espera que el string de 
 * salida sea "-XX+-".
 * 
 * @param respuesta 
 * @return string 
 */
string respuesta_en_string(const vector<EstadoLetra> & respuesta){
    string resultado = "";
    
    for (EstadoLetra estado : respuesta) {
        if (estado == EstadoLetra::LugarCorrecto)
            resultado.append("+");
        else if (estado == EstadoLetra::LugarIncorrecto)
            resultado.append("-");
        else resultado.append("X");
    }

    return resultado;
}