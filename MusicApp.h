/*
 *
 * Proyecto Music App clase Music App
 * Edgar Martínez Retes
 * A01706825
 * 14/06/2024
 * version : 67
 * Esta clase define objeto de tipo Music App que contiene el funcionamiento
 * para registrar usuarios y acceder al usuario. Esta clase es utilizada por
 * la función principal del programa y es parte del proyecto Music App.
 */

#ifndef MUSICAPP_H
#define MUSICAPP_H

/*
 * Se incluye el archivo Usuario para tener sus clases disponibles así como
 * los archivos que incluye este archivo
 */
#include "Usuario.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <thread>
#include <fstream>
#include <sstream>

using namespace std;

class MusicApp
{

private:
    // Polimorfismo para tener una array de diferentes tipos de usuario
    Usuario *usuarios[1000];
    int id;

public:
    // Sobrecarga
    MusicApp();
    MusicApp(Usuario *users[1000]);

    void register_(string nombre, string contrasena, string tipo);
    bool login(string nombre, string contrasena);

    // El return tiene que ser un apuntador de la variable
    Usuario **get_usuarios()
    {
        return usuarios;
    }
    // El parámetro tiene que ser un apuntador a otro array de apuntadores del tipo Usuario
    void set_usuarios(Usuario *new_usuarios[1000])
    {
        for (int i = 0; i < 1000; ++i)
        {
            usuarios[i] = new_usuarios[i];
        }
    }
    void set_id(int ids) { id = ids; }
};

/**
 * Constructor MusicApp vacío
 * Asigna el atributo id = 0
 * @param
 * @return
 */
MusicApp::MusicApp() { id = 0; }

/**
 * Constructor MusicApp con array de apuntadores tipo usuario
 * Asigna el atributo id = 0
 * Se asignan los usuarios en el array del atributo con 
 * los del parámetro que recibe
 * @param Usuario * users[1000], debe de ser de objeto: Básico, Premium o VIP
 * @return
 */
MusicApp::MusicApp(Usuario *users[1000])
{
    id = 0;
    // Se llenan todos los elementos cuándo tienen un apuntador hacia un objeto
    for (int i = 0; i < 1000; ++i)
    {
        usuarios[i] = users[i];
        if (users[i] != nullptr)
        {
            id++;
        }
    }

}

/**
 * register_ registra usuarios nuevos en el array de usuarios
 * Se añade al archivo csv el usuario para actualizar la base
 * de datos.
 * Luego se crea el usuario al array dependiendo su tipo,
 * se agrega al array de usuarios y se aumenta el índice.
 * @param string: nombre del usuario, contraseña y tipo (Básico, Premium o VIP)
 * @return
 */
void MusicApp::register_(string nombre, string contrasena, string tipo)
{
    // Registro en la base de datos csv
    fstream leer;
    fstream escribir;

    leer.open("usuarios.csv", ios::in);
    if (!leer.is_open())
    {
        escribir.open("usuarios.csv", ios::out | ios::app);
        escribir << "Usuario" << "," << "Contrasena" << "," << "Tipo\n";
        escribir << nombre << "," << contrasena << "," << tipo << "\n";
    }

    escribir.open("usuarios.csv", ios::out | ios::app);
    escribir << nombre << "," << contrasena << "," << tipo << "\n";

    /*
     * Dependiendo del tipo de usuario se crea ese objeto en el array dinámico
     * y se añade el id para añadir el siguiente usuario en la siguiente posición
    */
    if (tipo == "BASICO")
    {
        usuarios[id] = new Basico(nombre, contrasena, 5);
        id++;
    }
    else if (tipo == "PREMIUM")
    {
        usuarios[id] = new Premium(nombre, contrasena);
        id++;
    }
    else if (tipo == "VIP")
    {
        usuarios[id] = new VIP(nombre, contrasena);
        id++;
    }

    string archivo = "users/" + nombre + ".csv";

    leer.open(archivo, ios::in);
    if (!leer.is_open())
    {
        escribir.open(archivo, ios::out | ios::app);
        escribir << "Playlist" << "," << "Canciones" << "\n";
    }
    cout << "Usuario registrado con exito" << endl;

    escribir.close();
    leer.close();

    return;
}

/**
 * login el usarui accede a su cuenta con su nombre y contraseña
 * Se verifica que exista el usuario, luego se verifica que 
 * coincida con la contraseña y regresa un booleano si se accedio o no
 * @param string: nombre del usuario y contraseña
 * @return bool que indica si se accedio o no
 */
bool MusicApp::login(string nombre, string contrasena)
{
    // Se itera por todos los usuarios del array de usuarios
    for (int i = 0; i < 1000; i++)
    {
        if (usuarios[i]->get_user() == nombre)
        {
            if (usuarios[i]->get_contrasena() == contrasena)
            {
                cout << "Acceso a: " << usuarios[i]->get_user() << endl;
                return true;
            }
            cout << "Contrasena incorrecta" << endl;
            return false;
        }
    }
    cout << "Usuario no encontrado" << endl;
    return false;
}
#endif
