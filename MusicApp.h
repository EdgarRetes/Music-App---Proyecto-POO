#ifndef MUSICAPP_H
#define MUSICAPP_H

// Se incluye el archivo Usuario para tener sus clases disponibles así como los archivos que incluye este archivo
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
        // cout << "get 0: " << usuarios[0] << endl;
        // cout << "get 1: " << usuarios[1] << endl;
        // cout << "get *users: " << typeid(&usuarios).name() << endl;
        //  cout << usuarios[2] << endl;

        // Imprimi el tipo de dato para saber cual es mi tipo de variable de retorno
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
};

// Constructor si no hay base de datos de usuarios
MusicApp::MusicApp() { id = 0; }

// Constructor si hay base de datos de usuario
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
            // cout << id << endl;
            // cout << "i: " << i << " dir: " << usuarios[i] << endl;
        }
    }

    // cout << usuarios[0] << endl;
    // cout << usuarios[1] << endl;
}

// Método para registrar usuarios
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

    // Dependiendo del tipo de usuario se crea ese objeto en el array dinámico y se añade el id para añadir el siguiente usuario en la siguiente posición
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
        // cout << "Contenido antes: " << &usuarios[id] << endl;
        usuarios[id] = new VIP(nombre, contrasena);
        // cout << "Contenido despues: " << &usuarios[id] << endl;
        // cout << "Se guardo en el id: " << id << endl;
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

// Acceso al usuario dependiendo de su nombre y contraseña
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
