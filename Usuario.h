#ifndef USUARIO_H
#define USUARIO_H

#include "Playlist.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <thread>
#include <fstream>
#include <sstream>

using namespace std;

class Usuario
{

protected:
    string user;
    string contrasena;
    string plan;
    vector<Playlist> playlists;
    int maxnum_pl;
    int costo_plan;

public:
    Usuario(string usuario, string password);
    Usuario(string usuario, string password, string tipo);

    void add_Playlist(string nombre);
    void remove_Playlist(string nombre);
    void ver_Playlists();

    // Aún falta implementar sobreescritura
    string costo();
    string print_numpl();

    void set_user(string us)
    {
        user = us;
    }
    void set_contrasena(string pasword)
    {
        contrasena = pasword;
    }
    void set_plan(string tipo)
    {
        plan = tipo;
    }
    void set_playlists(vector<Playlist> pl)
    {
        playlists = pl;
    }
    void set_maxnum_pl(int num)
    {
        maxnum_pl = num;
    }
    void set_costo(int costo)
    {
        costo_plan = costo;
    }

    string get_user() { return user; }
    string get_contrasena() { return contrasena; }
    string get_plan() { return plan; }
    vector<Playlist> &get_playlists() { return playlists; }
    int get_maxnum_pl() { return maxnum_pl; }
    int get_costo_plan() { return costo_plan; }
};

Usuario::Usuario(string usuario, string password)
{
    user = usuario;
    contrasena = password;
}

Usuario::Usuario(string usuario, string password, string tipo)
{
    user = usuario;
    contrasena = password;
    plan = tipo;

    if (tipo == "BASICO")
    {
        maxnum_pl = 1;
        costo_plan = 0;
    }
    else if (tipo == "PREMIUM")
    {
        maxnum_pl = 5;
        costo_plan = 150;
    }
    else if (tipo == "VIP")
    {
        maxnum_pl = 12;
        costo_plan = 250;
    }
}

void Usuario::add_Playlist(string nombre)
{
    Playlist playlist(nombre);
    playlists.push_back(playlist);
    fstream leer;
    // Nombre de la variable para el archivo csv
    fstream escribir;

    string archivo = "users/" + user + ".csv";

    leer.open(archivo, ios::in);
    if (!leer.is_open())
    {
        escribir.open("usuarios.csv", ios::out | ios::app);
        escribir << "Playlist" << "," << "Canciones" << "\n";
        leer.close();
    }

    escribir.open(archivo, ios::out | ios::app);
    escribir << nombre << "," << "" << "\n";

    leer.close();
    escribir.close();

    cout << "\nSe anadio la playlist '" << nombre << "' al usuario '" << user << "'" << endl;

    return;
}

void Usuario::remove_Playlist(string nombre)
{
    Playlist playlist(nombre);
    int index;
    bool found = false;
    for (int i = 0; i < playlists.size(); i++)
    {
        if (playlists[i].get_nombre() == nombre)
        {
            index = i;
            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo existe esa playlist" << endl;
        return;
    }
    playlists.erase(playlists.begin() + (index));

    string act_csv = "Playlist, Canciones\n";
    for (int j = 0; j < playlists.size(); j++)
    {
        act_csv += playlists[j].get_nombre();
        for (int k = 0; k < playlists[j].get_canciones().size(); k++)
        {
            act_csv += "," + playlists[j].get_canciones()[k];
        }
        act_csv += "\n";
    }

    fstream escribir;

    string archivo = "users/" + user + ".csv";

    ofstream file(archivo, std::ios::trunc);
    file.close();

    escribir.open(archivo, ios::out | ios::app);
    escribir << act_csv;

    escribir.close();

    cout << "\nSe borro la playlist '" << nombre << "' del usuario '" << user << "'" << endl;

    return;
}

void Usuario::ver_Playlists()
{
    if (playlists.empty())
    {
        cout << "\n El usuario aun no tiene playlists" << endl;
    }
    for (int i = 0; i < playlists.size(); i++)
    {
        Playlist playlist = playlists[i];
        cout << "\n"
             << i + 1 << "> " << playlist.get_nombre() << ": " << endl;
        for (int j = 0; j < playlist.get_canciones().size(); j++)
        {
            cout << "   " << j + 1 << ". " << playlist.get_canciones()[j] << endl;
        }
    }
}

class Basico : public Usuario
{
private:
    int anuncios_por_hora;

public:
    Basico(string usuario, string password, int anuncios) : Usuario(usuario, password)
    {
        anuncios_por_hora = anuncios;
        set_plan("BASICO");
        set_maxnum_pl(1);
        set_costo(0);
    }

    string poner_anuncio();
    string costo();
    string print_numpl();

    void set_anuncios_por_hora(int anuncios)
    {
        anuncios_por_hora = anuncios;
    }

    int get_anuncios_por_hora() { return anuncios_por_hora; }
};

class Premium : public Usuario
{
private:
    string descuentos;

public:
    Premium(string usuario, string password) : Usuario(usuario, password)
    {
        descuentos = "decuentos";
        set_plan("PREMIUM");
        set_maxnum_pl(5);
        set_costo(150);
    }

    string descargar_pl(string nombre);
    string costo();
    string print_numpl();

    void set_descuentos(string desc)
    {
        descuentos = desc;
    }

    string get_descuentos() { return descuentos; }
};

class VIP : public Usuario
{
private:
    string descuentos;
    vector<string> canciones_nuevas;

public:
    VIP(string usuario, string password) : Usuario(usuario, password)
    {
        descuentos = "decuentos";
        canciones_nuevas.push_back("Canciones Nuevas");
        set_plan("VIP");
        set_maxnum_pl(12);
        set_costo(250);
    }

    string descargar_pl(string nombre);
    string hacer_colab(string user, string nombre);
    string escuchar_canciones_nuevas();
    string costo();
    string print_numpl();

    void set_descuentos(string desc)
    {
        descuentos = desc;
    }
    void set_canciones_nuevas(vector<string> newsongs)
    {
        canciones_nuevas = newsongs;
    }

    string get_descuentos() { return descuentos; }
    vector<string> get_canciones_nuevas() { return canciones_nuevas; }
};

#endif