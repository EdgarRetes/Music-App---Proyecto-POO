// Se incluye el archivo MusicApp para tener sus clases disponibles así como los archivos que incluye este archivo
#include "MusicApp.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <thread>
#include <fstream>
#include <sstream>

using namespace std;

// Variables globales
int opcion;
int prints = 0;

// Función para reproducir una playlists con parámetros del tipo Playlist y string
int playing(Playlist playlist, string user)
{
    // Opciones de reproducción
    while (true)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\n1. Siguiente cancion";
        cout << "\n2. Regresar cancion";
        cout << "\n3. Salir" << endl;
        cin >> opcion;
        if (opcion == 1)
        {
            return 1;
        }
        else if (opcion == 2)
        {
            return 2;
        }
        else if (opcion == 3)
        {
            return 3;
        }
        else
        {
            cout << "\nElige una opcion valida" << endl;
        }
    }
    return 0;
}

// Función interfaz de playlist que reciba un apuntador a una variable del tipo Playlist y un string

void playlist_interface(Playlist *playlist, string user)
{
    // Lógica del menú
    while (true)
    {
        /*Se limpia la entrada haciendo que el programa
        vuelva a solicitar entrada al usuario evitando errores.*/
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n> "
             << playlist->get_nombre() << ":" << endl;
        for (int i = 0; i < playlist->get_canciones().size(); i++)
        {
            cout << i + 1 << ". " << playlist->get_canciones()[i] << endl;
        }
        cout << "\n\n1. Anadir cancion";
        cout << "\n2. Eliminar cancion";
        cout << "\n3. Play";
        cout << "\n4. Salir" << endl;
        cout << "\n(Elige un numero): ";
        cin >> opcion;

        // Se añade canción a la playlist
        if (opcion == 1)
        {
            string cancion, info;
            cout << "Nombre de la cancion: ";
            cin.ignore();
            getline(cin, cancion);
            info = playlist->add_song(cancion, user);
            cout << info << endl;
            cout << "(Presione ENTER para continuar)" << endl;
        }

        // Se borra canción de la playlist
        else if (opcion == 2)
        {
            string info;
            int cancion;
            cout << "Numero de la cancion en la playlist: ";
            cin >> cancion;
            info = playlist->remove_song(cancion, user);
            cout << info << endl;
        }
        // Se reproduce la playlist
        else if (opcion == 3)
        {
            // Se crea un hilo para simular el proceso de reproducción en segundo plano con el detach
            thread t(&Playlist::play, playlist, user, ref(prints));
            t.detach();

            // Mientras no se pare la reproducción se va a mostrar las opciones de reproducción
            while (true)
            {
                // Se manda un apuntador con la playlist
                int action = playing(*playlist, user);

                // Si se pasa a la siguiente canción se cambia el valor de prints lo que hace que active una condición dentro del método
                if (action == 1)
                {
                    prints = 1;
                }

                else if (action == 2)
                {
                    prints = 2;
                }

                /*Si se sale del modo reproducción dejará de imprimir lo del hilo ya que se le sumo
                a la variable prints lo que causa que se active una condición dentro del método y
                se rompe el ciclo de estas opciones*/
                else if (action == 3)
                {
                    prints = 4;
                    break;
                }
            }
        }
        else if (opcion == 4)
        {
            break;
        }
        else
        {
            cout << "Elija una opcion valida" << endl;
        }
    }

    return;
}

// Función para cargar las playlists ya existentes en la base de datos del usuario

void cargar_playlists_csv(Usuario &user)
{
    fstream leer;
    fstream escribir;

    string archivo = "users/" + user.get_user() + ".csv";

    // Si no existe le archivo se crea

    leer.open(archivo, ios::in);
    if (!leer.is_open())
    {
        escribir.open(archivo, ios::out | ios::app);
        escribir << "Playlist" << "," << "Canciones" << "\n";
        escribir.close();
        return;
    }

    // Si existe lo lee para hacer los objetos de tipo Playlist y añadirlos al vector playlists

    string header;
    getline(leer, header);
    vector<Playlist> pl;
    vector<string> songs, row;
    string line, word, name;

    while (getline(leer, line))
    {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        songs.clear();
        for (int i = 1; i < row.size(); i++)
        {
            songs.push_back(row[i]);
        }
        Playlist playlist(row[0], songs);
        pl.push_back(playlist);
    }
    user.set_playlists(pl);
    leer.close();
    return;
}

// Función interfaz de usuario que reciba un apuntador de una variable tipo Usuario

void user_interface(Usuario *user)
{
    // Variable auxiliar para controlar los couts de la reproducción
    prints = 0;
    // Menú
    while (true)
    {
        // Si el usuario es de tipo Básico hara la función
        if (Basico *basico = dynamic_cast<Basico *>(user))
        {
            string anuncio = basico->poner_anuncio();
            if (anuncio == "Anuncio")
            {
                cout << anuncio << " reproduciendose. Espere 5 segundos..." << endl;
                this_thread::sleep_for(chrono::seconds(5));
            }
            /*Se limpia la entrada haciendo que el programa
            vuelva a solicitar entrada al usuario evitando errores.*/
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n"
                 << user->get_user() << ": " << user->get_plan() << endl;
            string costo = user->costo(), npl = user->print_numpl();
            cout << costo;
            cout << npl << endl;
            cout << "\n1. Ver playlists";
            cout << "\n2. Anadir playlist";
            cout << "\n3. Borrar playlist";
            cout << "\n4. Salir" << endl;
            cout << "\n(Elige un numero): ";
            cin >> opcion;

            if (opcion == 1)
            {
                // Otro menú para seleccionar la playlist
                while (true)
                {
                    string playlist = "q";
                    bool check = false;
                    user->ver_Playlists();
                    cout << "\nSeleccione una playlist (Escriba su nombre / 'q' para salir): ";
                    /*Se limpia la entrada haciendo que el programa
                    vuelva a solicitar entrada al usuario evitando errores.
                    Además se permite leer la entrada hasta que haya un salto de línea*/
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, playlist);
                    cout << "(Presione ENTER para continuar)" << endl;
                    if (playlist == "q")
                    {
                        break;
                    }
                    // Itera sobre las playlists del usuario hasta conseguir la playlist correcta y entrar a su interfaz
                    for (int i = 0; i < user->get_playlists().size(); i++)
                    {
                        if (user->get_playlists()[i].get_nombre() == playlist)
                        {
                            check = true;
                            // Se manda la referencia del objeto playlist
                            playlist_interface(&user->get_playlists()[i], user->get_user());
                            break;
                        }
                    }
                    if (!check)
                    {
                        cout << "\nNo existe esa playlist" << endl;
                    }
                }
            }

            // Se añade playlist

            else if (opcion == 2)
            {
                string nombre;
                cout << "Nombre de la playlist nueva (sin espacios): ";
                cin.ignore();
                getline(cin, nombre);
                user->add_Playlist(nombre);
                cout << "(Presione ENTER para continuar)" << endl;
            }

            // Se borra playlist

            else if (opcion == 3)
            {
                string nombre;
                cout << "\nPlaylists: " << endl;
                for (int i = 0; i < user->get_playlists().size(); i++)
                {
                    cout << i + 1 << ". " << user->get_playlists()[i].get_nombre() << endl;
                }
                cout << "\nNombre de la playlist a borrar: ";
                cin.ignore();
                getline(cin, nombre);
                user->remove_Playlist(nombre);
                cout << "(Presione ENTER para continuar)" << endl;
            }

            // Sale del interfaz del usuario
            else if (opcion == 4)
            {
                return;
            }
            // Repite el menú hasta que haya una opción válida
            else
            {
                cout << "Elige una opcion valida" << endl;
            }
        }
        else if (Premium *premium = dynamic_cast<Premium *>(user))
        {
            /*Se limpia la entrada haciendo que el programa
            vuelva a solicitar entrada al usuario evitando errores.*/
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n"
                 << user->get_user() << ": " << user->get_plan() << endl;
            string costo = user->costo(), npl = user->print_numpl();
            cout << costo;
            cout << npl << endl;
            cout << "\n1. Ver playlists";
            cout << "\n2. Anadir playlist";
            cout << "\n3. Borrar playlist";
            cout << "\n4. Ver descuentos";
            cout << "\n5. Salir" << endl;
            cout << "\n(Elige un numero): ";
            cin >> opcion;

            if (opcion == 1)
            {
                // Otro menú para seleccionar la playlist
                while (true)
                {
                    string playlist = "q";
                    bool check = false;
                    user->ver_Playlists();
                    cout << "\nSeleccione una playlist (Escriba su nombre / 'q' para salir): ";
                    /*Se limpia la entrada haciendo que el programa
                    vuelva a solicitar entrada al usuario evitando errores.
                    Además se permite leer la entrada hasta que haya un salto de línea*/
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, playlist);
                    cout << "(Presione ENTER para continuar)" << endl;
                    if (playlist == "q")
                    {
                        break;
                    }
                    // Itera sobre las playlists del usuario hasta conseguir la playlist correcta y entrar a su interfaz
                    for (int i = 0; i < user->get_playlists().size(); i++)
                    {
                        if (user->get_playlists()[i].get_nombre() == playlist)
                        {
                            check = true;
                            // Se manda la referencia del objeto playlist
                            playlist_interface(&user->get_playlists()[i], user->get_user());
                            break;
                        }
                    }
                    if (!check)
                    {
                        cout << "\nNo existe esa playlist" << endl;
                    }
                }
            }

            // Se añade playlist

            else if (opcion == 2)
            {
                string nombre;
                cout << "Nombre de la playlist nueva (sin espacios): ";
                cin.ignore();
                getline(cin, nombre);
                user->add_Playlist(nombre);
                cout << "(Presione ENTER para continuar)" << endl;
            }

            // Se borra playlist

            else if (opcion == 3)
            {
                string nombre;
                cout << "\nPlaylists: " << endl;
                for (int i = 0; i < user->get_playlists().size(); i++)
                {
                    cout << i + 1 << ". " << user->get_playlists()[i].get_nombre() << endl;
                }
                cout << "\nNombre de la playlist a borrar: ";
                cin.ignore();
                getline(cin, nombre);
                user->remove_Playlist(nombre);
                cout << "(Presione ENTER para continuar)" << endl;
            }

            else if (opcion == 4)
            {
                string descuentos = premium->get_descuentos();
                cout << descuentos << endl;
            }

            // Sale del interfaz del usuario
            else if (opcion == 5)
            {
                return;
            }
            // Repite el menú hasta que haya una opción válida
            else
            {
                cout << "Elige una opcion valida" << endl;
            }
        }
        else if (VIP *vip = dynamic_cast<VIP *>(user))
        {
            /*Se limpia la entrada haciendo que el programa
            vuelva a solicitar entrada al usuario evitando errores.*/
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n"
                 << user->get_user() << ": " << user->get_plan() << endl;
            string costo = user->costo(), npl = user->print_numpl();
            cout << costo;
            cout << npl << endl;
            cout << "\n1. Ver playlists";
            cout << "\n2. Anadir playlist";
            cout << "\n3. Borrar playlist";
            cout << "\n4. Ver descuentos";
            cout << "\n5. Ver nuevos lanzamientos exclusivos";
            cout << "\n6. Salir" << endl;
            cout << "\n(Elige un numero): ";
            cin >> opcion;

            if (opcion == 1)
            {
                // Otro menú para seleccionar la playlist
                while (true)
                {
                    string playlist = "q";
                    bool check = false;
                    user->ver_Playlists();
                    cout << "\nSeleccione una playlist (Escriba su nombre / 'q' para salir): ";
                    /*Se limpia la entrada haciendo que el programa
                    vuelva a solicitar entrada al usuario evitando errores.
                    Además se permite leer la entrada hasta que haya un salto de línea*/
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, playlist);
                    cout << "(Presione ENTER para continuar)" << endl;
                    if (playlist == "q")
                    {
                        break;
                    }
                    // Itera sobre las playlists del usuario hasta conseguir la playlist correcta y entrar a su interfaz
                    for (int i = 0; i < user->get_playlists().size(); i++)
                    {
                        if (user->get_playlists()[i].get_nombre() == playlist)
                        {
                            check = true;
                            // Se manda la referencia del objeto playlist
                            playlist_interface(&user->get_playlists()[i], user->get_user());
                            break;
                        }
                    }
                    if (!check)
                    {
                        cout << "\nNo existe esa playlist" << endl;
                    }
                }
            }

            // Se añade playlist

            else if (opcion == 2)
            {
                string nombre;
                cout << "Nombre de la playlist nueva (sin espacios): ";
                cin.ignore();
                getline(cin, nombre);
                user->add_Playlist(nombre);
                cout << "(Presione ENTER para continuar)" << endl;
            }

            // Se borra playlist

            else if (opcion == 3)
            {
                string nombre;
                cout << "\nPlaylists: " << endl;
                for (int i = 0; i < user->get_playlists().size(); i++)
                {
                    cout << i + 1 << ". " << user->get_playlists()[i].get_nombre() << endl;
                }
                cout << "\nNombre de la playlist a borrar: ";
                cin.ignore();
                getline(cin, nombre);
                user->remove_Playlist(nombre);
                cout << "(Presione ENTER para continuar)" << endl;
            }

            else if (opcion == 4)
            {
                string descuentos = vip->get_descuentos();
                cout << descuentos << endl;
            }

            else if (opcion == 5)
            {
                vector<string> nuevo = vip->get_canciones_nuevas();
                cout << "Escucha en nuestra pagina estos nuevos albums:" << endl;
                cout << nuevo[0] << endl;
                cout << nuevo[1] << endl;
                cout << nuevo[2] << endl;
                cout << "Y MAS!!!" << endl;
            }

            // Sale del interfaz del usuario
            else if (opcion == 6)
            {
                return;
            }
            // Repite el menú hasta que haya una opción válida
            else
            {
                cout << "Elige una opcion valida" << endl;
            }
        }
    }
}

// Main

int main()
{
    MusicApp app;
    fstream file;

    // Si no existe un archivo de usuarios, va a construir el objeto app sin parámetros
    file.open("usuarios.csv", ios::in);
    if (!file.is_open())
    {
        file.close();
        MusicApp app;
    }

    // Si existe el archivo, va a cargar los usuarios
    else
    {
        // Crea el arreglo dinámico para guardar los tipos de usuario que existen
        Usuario *users[1000];
        vector<string> user;
        string line, word;
        int i = 0, id = 0;

        // Lee el archivo línea por línea y se divide la linea por las comas agregándolos al vector user
        // En el primer índice está su nombre, en el segundo su contraseña y en el último su tipo
        while (getline(file, line))
        {
            user.clear();
            stringstream s(line);

            while (getline(s, word, ','))
            {
                user.push_back(word);
            }

            // Si no hay usuarios en la primera o segunda línea se rompe el ciclo
            if (user.empty() && i == 0 || user.empty() && i == 1)
            {
                break;
            }

            // Casos para agregar los usuarios al array de Usuarios utilizando new
            // Cada que se agrega un usuario se debe aumentar el índice para agregar el siguiente usuario en la siguiente posición
            if (user[2] == "BASICO")
            {
                users[id] = new Basico(user[0], user[1], 5);
                id++;
                app.set_id(id);
            }
            else if (user[2] == "PREMIUM")
            {
                users[id] = new Premium(user[0], user[1]);
                id++;
                app.set_id(id);
            }
            else if (user[2] == "VIP")
            {
                users[id] = new VIP(user[0], user[1]);
                id++;
                app.set_id(id);
            }
            i++;
        }

        // Se checa si hay algún pointer a un usuario para crear el constructor de MusicApp con la variable de users
        bool check = false;

        for (int k = 0; k < 1000; k++)
        {
            if (users[i] != nullptr)
            {
                check = true;
                break;
            }
        }

        if (!check)
        {
            app = MusicApp(users);
        }
    }
    file.close();

    // Lógica de menú
    while (true)
    {
        cout << "\nBienvenido a Music App" << endl;
        cout << "\n1. Entrar";
        cout << "\n2. Registrarse";
        cout << "\n3. Salir" << endl;
        cout << "\n(Elige un numero): ";

        cin >> opcion;

        if (opcion == 1)
        {
            while (true)
            {
                // Ingresan datos de usuario existente
                string usuario, contrasena;
                cout << "\n(Escribe 'q' en el nombre de usuario para salir): ";
                cout << "\nNombre de usuario: ";
                cin >> usuario;
                if (usuario == "q")
                {
                    break;
                }
                cout << "Contrasena: ";
                cin >> contrasena;
                // Verifica si el usuario existe
                if (app.login(usuario, contrasena))
                {
                    /*Si el usuario existe, se define un puntero de tipo Usuario que apunta a la matriz regresada
                    por el método la cuál es de tipo Usuario *array[]
                    */

                    Usuario **usuarios = app.get_usuarios();

                    // Se recorre toda la matriz utilizando el método en la clase usuario para encontrar el usuario con el que se trabajará

                    for (int i = 0; i < 1000; i++)
                    {

                        if (usuarios[i]->get_user() == usuario)
                        {
                            cout << "ok" << endl;
                            // Se utiliza el puntero al usuario como parámetro para cambiar directamente sus atributos y no cambiar sus copias
                            // Se llama la función para cargar las playlists del usuario en sus vectores playlists.
                            cargar_playlists_csv(*usuarios[i]);
                            // Una vez obtenidas sus playlists entra a la interfaz del usuario.
                            user_interface(usuarios[i]);
                            break;
                        }
                    }

                    break;
                }
            }
        }
        else if (opcion == 2)
        {
            // Ingresan datos de un nuevo usuario
            string usuario, contrasena, tipo;
            int cuenta;
            cout << "\nNombre de usuario: ";
            cin >> usuario;
            cout << "Contrasena: ";
            cin >> contrasena;

            // Se define el tipo de usuario
            while (true)
            {
                cout << "\nTipo de cuenta: \n1. BASICO \n2. PREMIUM \n3. VIP\n(Elige un numero): ";
                cin >> cuenta;

                if (cuenta == 1)
                {
                    tipo = "BASICO";
                    break;
                }
                else if (cuenta == 2)
                {
                    tipo = "PREMIUM";
                    break;
                }
                else if (cuenta == 3)
                {
                    tipo = "VIP";
                    break;
                }
                else
                {
                    cout << "Elige una opcion valida" << endl;
                }
            }
            // Se registra al usuario
            app.register_(usuario, contrasena, tipo);
        }
        // Se termina el programa
        else if (opcion == 3)
        {
            cout << "!Hasta la proxima!" << endl;
            // Aquí implementar un proceso para liberar memoria
            return 0;
        }
        // El programa continua hasta obtener una respuesta válida
        else
        {
            cout << "Elige una opcion valida" << endl;
        }
    }
    return 0;
}

/*
Limitantes:
Se pueden crear usuarios con el mismo nombre
Se pueden crear playlists con el mismo nombre
Se pueden añadir las mismas canciones a una playlist
El buscador de canciones en la base de datos siempre regresa la primera opción y no todas las canciones con ese nombre para elegir
Al poner una playlist que no existe se traba el programa
*/