#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <bits/stdc++.h>
using namespace std;

class Playlist
{
private:
    string nombre;
    vector<string> canciones;

public:
    // Sobrecarga en los constructores para cuando se cree una playlist con o sin base de datos.
    Playlist(string name);
    Playlist(string name, vector<string> songs);

    void play(string user, int &prints);
    string add_song(string name, string user);
    string remove_song(int song, string user);

    void set_name(string n)
    {
        nombre = n;
    }
    void set_canciones(vector<string> songs)
    {
        canciones = songs;
    }

    string get_nombre() { return nombre; }
    vector<string> get_canciones() { return canciones; }
};

Playlist::Playlist(string name)
{
    nombre = name;
}
Playlist::Playlist(string name, vector<string> songs)
{
    nombre = name;
    canciones = songs;
}

string Playlist::add_song(string name, string user)
{

    // Se crea un nuevo string sin espacios ni caracteres especiales para el buscador a partir de la cancion del usuario
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    string new_name;
    for (char c : name)
    {
        if (isalnum(c))
        {
            new_name += c;
        }
    }

    fstream leer;

    leer.open("songsdb.csv", ios::in);
    if (!leer.is_open())
    {
        return "\nError al abrir el archivo\n";
    }

    vector<string> song, song_og;
    string line, word, new_w;
    int i = 0;

    while (getline(leer, line))
    {
        new_w.clear();
        song.clear();
        song_og.clear();
        word.clear();
        stringstream s(line);

        if (i > 0)
        {

            // Se normaliza la línea para poder compararla con el input del usuario
            while (getline(s, word, ','))
            {
                new_w = "";
                for (char c : word)
                {
                    if (isalnum(c))
                    {
                        new_w += c;
                    }
                }
                transform(new_w.begin(), new_w.end(), new_w.begin(), ::tolower);
                song.push_back(new_w);
                song_og.push_back(word);
            }

            if (song[1] == new_name)
            {
                // Si se encuentra la cancione en la base de datos igual se actualiza el archivo csv del usuario
                string pl, current;
                bool check;
                fstream leer2;

                leer2.open("users/" + user + ".csv", ios::in);

                string linea, palabra;
                while (getline(leer2, linea))
                {
                    stringstream s(linea);
                    check = false;
                    while (getline(s, palabra, ','))
                    {
                        if (palabra == nombre)
                        {
                            check = true;
                        }

                        if (!check)
                        {
                            pl += palabra + ",";
                        }
                        else
                        {
                            current += palabra + ",";
                        }
                    }
                    if (!check)
                    {
                        pl += "\n";
                    }
                }

                pl += current + song_og[1] + " - " + song_og[3];
                leer.close();

                fstream escribir;
                string archivo = "users/" + user + ".csv";

                // Se sobreescribe el archivo con la actualización en el string
                ofstream file(archivo, std::ios::trunc);
                file.close();

                escribir.open(archivo, ios::out | ios::app);
                escribir << pl << "\n";
                escribir.close();
                leer.close();
                // Se agrega la canción al vector de canciones
                canciones.push_back(song_og[1] + " - " + song_og[3]);

                return "\nSe anadio la cancion " + song_og[1] + " de " + song_og[3] + " a la playlist " + nombre;
            }
        }

        i++;
    }

    leer.close();

    return "\nCancion no encontrada\n";
}

string Playlist::remove_song(int song, string user)
{
    // Se consigue el nombre de la canción a partir del index y se borra de el vector canciones
    string current = canciones[song - 1];
    canciones.erase(canciones.begin() + (song - 1));

    // Después se modifica el csv copiando el contenido pasado menos la canción que se borró
    string new_pl = "Playlist, Canciones\n" + nombre;
    for (int i = 0; i < canciones.size(); i++)
    {
        new_pl += "," + canciones[i];
    }
    new_pl += "\n",

        cout << new_pl << endl;

    fstream leer;
    string archivo = "users/" + user + ".csv";

    leer.open(archivo, ios::in);
    if (!leer.is_open())
    {
        return "\nError al abrir el archivo\n";
    }

    vector<string> playlist;
    string line, word;
    bool check;
    int i = 0;

    while (getline(leer, line))
    {

        playlist.clear();
        stringstream s(line);

        if (i > 0)
        {
            if (i > 1)
            {
                new_pl += "\n";
            }
            while (getline(s, word, ','))
            {
                if (word == nombre)
                {
                    check = true;
                }
                if (!check)
                {
                    playlist.push_back(word);
                }
            }
        }
        for (int i = 0; i < playlist.size(); i++)
        {
            if (i != playlist.size() - 1)
            {
                new_pl += playlist[i] + ",";
            }
            else
            {
                new_pl += playlist[i];
            }
        }
        check = false;
        i++;
    }

    leer.close();

    fstream escribir;

    // Se sobreescribe el archivo con la actualización en el string
    ofstream file(archivo, std::ios::trunc);
    file.close();

    escribir.open(archivo, ios::out | ios::app);
    escribir << new_pl;

    escribir.close();

    return "\nSe borro la cancion " + current + " de la playlist " + nombre;
}

void Playlist::play(string user, int &prints)
{
    // Se itera sobre las canciones para reproducirlas
    for (int j = 0; j < canciones.size(); j++)
    {
        if (prints == 1 || prints == 2)
        {
            prints = 0;
        }
        string name;
        int tiempo;

        // Se agregan las comillas al string para compararlo con la base de datos
        size_t primeraComilla = canciones[j].find('"');
        if (primeraComilla != string::npos)
        {
            size_t segundaComilla = canciones[j].find('"', primeraComilla + 1);
            if (segundaComilla != string::npos)
            {
                name = '"' + canciones[j].substr(primeraComilla + 1, segundaComilla - primeraComilla - 1) + '"';
            }
        }

        fstream leer;
        leer.open("songsdb.csv", ios::in);
        if (!leer.is_open())
        {
            cout << "\nError al abrir el archivo\n";
            leer.close();
            return;
        }

        vector<string> song;
        string line, word;
        int i = 0;

        while (getline(leer, line))
        {
            song.clear();
            stringstream s(line);

            while (getline(s, word, ','))
            {
                song.push_back(word);
            }
            // Se encuentra la canción en la base de datos
            if (song[1] == name)
            {
                string str_tiempo;
                // Se consigue la duración de la canción y se le quitan las comas
                size_t primeraComilla = song[12].find('"');
                if (primeraComilla != string::npos)
                {
                    size_t segundaComilla = song[12].find('"', primeraComilla + 1);
                    if (segundaComilla != string::npos)
                    {
                        str_tiempo = song[12].substr(primeraComilla + 1, segundaComilla - primeraComilla - 1);
                    }
                }
                // Si se puede convertir el tiempo a int, se guarda ese valor en la variable
                if (typeid(stoi(str_tiempo)) == typeid(int) && stoi(str_tiempo) >= 1000)
                {

                    tiempo = stoi(str_tiempo) / 1000;
                }
                // Si no, se asignan 60 segundos por default
                else
                {
                    tiempo = 60;
                }
                break;
            }
        }

        leer.close();
        while (i < tiempo)
        {
            if (prints < 3)
            {
                // Se imprime la salida en el hilo con un delay de un segundo para simular el método de reproducción
                cout << "\rReproduciendo: " << canciones[j] << " [" << i + 1 << "s]" << "   Elige una opcion (num):" << flush;
                this_thread::sleep_for(chrono::seconds(1));
            }
            // Como está en un hilo se pueden seguir recibiendo inputs lo que cambia la canción que se está reproduciendo

            // Se rompre el ciclo para reproducir la siguiente canción cambaindo el valor de j
            if (prints == 1)
            {
                if (j == canciones.size() - 1)
                {
                    j = -1;
                }
                break;
            }
            // Se restan los valores de j y se rompe el ciclo
            else if (prints == 2)
            {
                if (j == 0)
                {
                    j = canciones.size() - 2;
                }
                else
                {
                    j -= 2;
                }
                break;
            }
            // Se rompe el ciclo acabando el método
            else if (prints == 4)
            {
                j = canciones.size();
            }
            i++;
        }
    }
    return;
}

#endif