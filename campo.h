#ifndef CAMPO_H
#define CAMPO_H
#include <string>
using std::string;
class Campo
{
    int campo;
    string nombre;
    string tipo;
    int longitud;
    bool llave;
public:
    Campo(int campo,string nombre,string tipo,int longitud,bool llave);
    Campo(string datos);
    int getCampo() const;
    void setCampo(int value);
    string getNombre() const;
    void setNombre(const string &value);
    string getTipo() const;
    void setTipo(const string &value);
    int getLongitud() const;
    void setLongitud(int value);
    bool getLlave() const;
    void setLlave(bool value);
    string toString()const;
};

#endif // CAMPO_H
