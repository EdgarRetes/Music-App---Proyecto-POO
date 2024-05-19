# Music-App---Proyecto-POO
Proyecto Integrador para la clase de Programación Orientada a Objetos

## ¿Qué hace?

El programa simula una aplicación de música donde un usuario se puede registrar y acceder a su cuenta con un tipo de cuenta en específico a modo de suscripción. El usuario puede elegir entre la cuenta básica, premium o VIP dependiendo de las funcionalidades que deseé. Si el usuario elige el plan básico, este solo podra crear una playlist donde puede añadir la música que prefiera. En el plan premium puede tener hasta 5 playlist además de tener la posibilidad de descargar sus playlists para poder escucharlas sin conexión. Por último, el usuario VIP es capaz de tener hasta 12 playlists, descargar sus canciones y hacer sus playlists colaborativas con otro usuario del sistema.

## ¿Cómo se construye?

Para poder diseñar el programa las clases que se utilizaron son las siguientes:

### - MusicAPP

Esta es la clase principal donde los usuarios pueden registrarse y acceder a su cuenta. Tiene un vector con los usuarios del sistema que se hayana creado.

### - Usuario

Esta clase tiene una relación de compisición con MusicApp, siendo la clase hija de esta clase principal (MusicApp). Esta clase se deriva en distintos tipos de usuario por lo que tiene una relación herencia con todos los tipos de usario que pueden crearse. Las características que comparte con todos sus derivados es que todos tienen nombre, contraseña, playlists, y el máximo número de playlists mientras que los métodos que comparten son los de crear y eliminar playlists.

##### .- Básico

Este tipo de usuario solo es capaz de tener 1 playlist. El usuario va a tener anuncios mientras está en su cuenta determinados por su atributo de números de anuncio por hora, que se mostraran con su método.

##### .- Premium

El usuario que sea premium tiene la capacidad de tener hasta 5 playlists. El usuario tendrá descuentos disponibles para poder comprar artículos de música, además de que es capaz de dercaragr sus playlists.

##### .- VIP

Por último, este usuario tiene la característica de poder escuchar canciones nuevas antes de que sean lanzadas al público, que están guardadas en su atributo canciones de tipo vector. Además contará con los decuentos del usuario Premium, tener hasta 12 playlists y la capacidad de descargar sus playlists.
### - Playlist

Esta clase también tiene una relación de composición como elemento hijo de la clase padre Usuario. cada playlist va a tener un nombre y un vector con las canciones que contiene. Además lo que se puede hacer con cada una es reproducir, pausar, reproducir de manera aleatoria, pasar a la siguiente canción, pasar a la canción previa, añadir canciones y eliminar canciones.

El diagrama UML de esta estructura es el siguiente:
![MusicApp drawio](https://github.com/EdgarRetes/Music-App---Proyecto-POO/assets/113946434/a49f9f4d-e4a4-4eab-828e-93b7ae050377)

## Limitantes

Algunas cuestiones que identifiqué que podrían faltar en mi aplicación son los siguientes:

- Se debería implementar una base de datos p implementar alguna API para poder buscar canciones ya que actualmente se deja al usuario implementar una canción que el mismo escriba como se llama.
- Debería haber un sistema para guardar los registros de usuarios y de las playlists paraq ue no se tengan que crear cada vez que corra el programa.
- Muchas de las funciones tendrán como salida strings los cuales van a ser simbólicos, representando un proceso, ya que idealmente se harían todos los procesos en la aplicación.
- No está implementado ningún sistema de costos ni el poder hacer cambio de planes en cuanto a las suscripciones.
- Puede ser que sería más eficiente si la clase usuario tenga un atributo "tipo_de_usuario" para que sea más fácil acceder a que tipo de usuario es cada uno.
- El hacer una playlist colaborativa puede ser un reto ya que tendría que crearse una copia en el usuario elegido y que cada modificación en esa playlist sea visible para todos. Además que podría haber una cuestión con la validación de cuantos playlists tiene y se le permite a cada usuario tener para poder compartirla sin que pase su número de playlists máximas, o que haya un número determinado de personas con las que puedas compartirla.

## Ejecución

...


