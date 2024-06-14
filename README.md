# Music-App---Proyecto-POO
Proyecto Integrador para la clase de Programación Orientada a Objetos

## ¿Qué hace?

El programa simula una aplicación de música donde un usuario se puede registrar y acceder a su cuenta con un tipo de cuenta en específico a modo de suscripción. El usuario puede elegir entre la cuenta básica, premium o VIP dependiendo de las funcionalidades que deseé. Si el usuario elige el plan básico, este solo podra crear una playlist donde puede añadir la música que prefiera. En el plan premium puede tener hasta 5 playlist además de tener la posibilidad de descargar sus playlists para poder escucharlas sin conexión. Por último, el usuario VIP es capaz de tener hasta 12 playlists, descargar sus canciones y ver las canciones nuevas que tiene acceso exclusivo.

## ¿Cómo se construye?

Para poder diseñar el programa, las clases que se utilizaron son las siguientes:
* Cada clase tiene sus constructores que tienen sobrecarga.

### - MusicAPP

Esta es la clase principal donde los usuarios pueden registrarse y acceder a su cuenta. Tiene un arreglo dinámico con apuntadores de tipo Usuario para cada tipo de usuario del sistema que se haya creado (Polimorfismo).

### - Usuario

Esta clase tiene una relación de compisición con MusicApp, siendo la clase hija de esta clase principal (MusicApp). Esta clase se deriva en distintos tipos de usuario por lo que tiene una relación herencia con todos los tipos de usario que pueden crearse. Las características que comparte con todos sus derivados es que todos tienen nombre, tipo, contraseña, playlists, y el máximo número de playlists mientras que los métodos que comparten son los de crear y eliminar playlists, además de tener métodos que utilizan sobreescritura para obetener el número de playlists y el costo dependiendo de la clase.

##### .- Básico

Este tipo de usuario solo es capaz de tener 1 playlist. El usuario va a tener anuncios mientras está en su cuenta determinados por su atributo de números de anuncio por hora, que se mostraran con su método.

##### .- Premium

El usuario que sea premium tiene la capacidad de tener hasta 5 playlists. El usuario tendrá descuentos disponibles para poder comprar artículos de música, además de que es capaz de dercaragr sus playlists.

##### .- VIP

Por último, este usuario tiene la característica de poder escuchar canciones nuevas antes de que sean lanzadas al público, que están guardadas en su atributo canciones de tipo vector. Además contará con los descuentos del usuario Premium y tener hasta 12 playlists.
### - Playlist

Esta clase también tiene una relación de composición como elemento hijo de la clase padre Usuario. Cada playlist va a tener un nombre y un vector con las canciones que contiene. Además lo que se puede hacer con cada una es reproducir, añadir canciones y eliminar canciones.

El diagrama UML de esta estructura es el siguiente:
![MusicApp drawio](https://github.com/EdgarRetes/Music-App---Proyecto-POO/assets/113946434/bbff1148-acaa-41fe-b28d-7720922671b8)

## Limitantes

Algunas cuestiones que identifiqué que podrían faltar o algunos errores en mi aplicación son los siguientes:

Primera entrega -
- Se debería implementar una base de datos p implementar alguna API para poder buscar canciones ya que actualmente se deja al usuario implementar una canción que el mismo escriba como se llama. (RESUELTO EN LA SEGUNDA ENTREGA)
- Debería haber un sistema para guardar los registros de usuarios y de las playlists para que no se tengan que crear cada vez que corra el programa.(RESUELTO EN LA SEGUNDA ENTREGA)
- Muchas de las funciones tendrán como salida strings los cuales van a ser simbólicos, representando un proceso, ya que idealmente se harían todos los procesos en la aplicación.
- No está implementado ningún sistema de costos ni el poder hacer cambio de planes en cuanto a las suscripciones.
- Puede ser que sería más eficiente si la clase usuario tenga un atributo "tipo_de_usuario" para que sea más fácil acceder a que tipo de usuario es cada uno. (RESUELTO EN LA SEGUNDA ENTREGA)
- El hacer una playlist colaborativa puede ser un reto ya que tendría que crearse una copia en el usuario elegido y que cada modificación en esa playlist sea visible para todos. Además que podría haber una cuestión con la validación de cuantos playlists tiene y se le permite a cada usuario tener para poder compartirla sin que pase su número de playlists máximas, o que haya un número determinado de personas con las que puedas compartirla.

Segunda entrega -
- Se pueden crear usuarios con el mismo nombre.
- Se pueden crear playlists con el mismo nombre.
- Se pueden añadir las mismas canciones a una playlist.
- El buscador de canciones en la base de datos siempre regresa la primera opción y no todas las canciones con ese nombre para elegir.
- Al poner una playlist que no existe se traba el programa.
- Por alguna razón no corre en mac entonces tengo que revisar eso más adelante.

Entrega final -
- No hay validación de que un usuario pueda tener el número de playlists máximo que se estableció para cada tipo de usuario

## Ejecución

1. Cuando se descarga el zip, se extraen los archivos y tienes que acceder a la carpeta desde la terminal. Dependiendo del folder donde se guarde usas el comando `cd Carpeta` hasta llegar a donde esté la carpeta del proyecto y accedes a ella del mismo modo:
```
cd Music-App---Proyecto-POO
```
2. Se debe compilar el `main.cpp`, creando el .exe del archivo utilizando el siguiente comando:
```
g++ main.cpp -o main
```
*  Si pide que la extensión de std=c++11 compilarlo de la siguiente manera:
```
g++ -std=c++11 main.cpp -o main
```
3. Después se utliza este comando para correr el `main.exe`:
```
./main.exe
```

## Referencias

Ya que se usaron conceptos no vistos en clase, se referencían los conceptos investigados por cuenta propia

- Threads:

cplusplus(2023). Reference:<thread>:this_thread:sleep_for. https://cplusplus.com/reference/thread/this_thread/sleep_for/

Sayan(2023). Multithreading in C++. Geeks for Geeks. https://www.geeksforgeeks.org/multithreading-in-cpp/

- cin:

nikhil(2024). cin in C++. https://www.geeksforgeeks.org/cin-in-c/

- fstream:

cplusplus(2023). Tutorials: C++ Language: Input/output with files. https://cplusplus.com/doc/tutorial/files/
