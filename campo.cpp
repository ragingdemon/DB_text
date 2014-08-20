#include "campo.h"
#include <sstream>
#include <vector>
#include <stdexcept>

using std::stringstream;
using std::string;
using std::vector;
using std::invalid_argument;

vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

Campo::Campo(int campo, string nombre, string tipo, int longitud, bool llave)
    : campo(campo),nombre(nombre),tipo(tipo),longitud(longitud),llave(llave)
{

}

Campo::Campo(string datos)
{
    vector<string> tokens = split(datos,',');
    if(tokens.size() < 5)
        throw invalid_argument("datos insuficientes");
    campo = std::stoi(tokens.at(0));
    nombre = tokens.at(1);
    tipo = tokens.at(2);
    longitud = std::stoi(tokens.at(3));
    llave = std::stoi(tokens.at(4));
}

int Campo::getCampo() const
{
    return campo;
}

void Campo::setCampo(int value)
{
    campo = value;
}

string Campo::getNombre() const
{
    return nombre;
}

void Campo::setNombre(const string &value)
{
    nombre = value;
}

string Campo::getTipo() const
{
    return tipo;
}

void Campo::setTipo(const string &value)
{
    tipo = value;
}

int Campo::getLongitud() const
{
    return longitud;
}

void Campo::setLongitud(int value)
{
    longitud = value;
}

bool Campo::getLlave() const
{
    return llave;
}

void Campo::setLlave(bool value)
{
    llave = value;
}

string Campo::toString() const
{
    stringstream ss;
    ss<<campo<<','<<nombre<<','<<tipo<<','<<longitud<<','<<llave;
    return ss.str();
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
