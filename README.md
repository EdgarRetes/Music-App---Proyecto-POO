# Music-App---Proyecto-POO
Proyecto Integrador para la clase de Programación Orientada a Objetos

## ¿Qué hace?

El programa simula una aplicación de música donde un usuario se puede registrar y acceder a su cuenta con un tipo de cuenta en específico a modo de suscripción. El usuario puede elegir entre la cuenta básica, premium o VIP dependiendo de las funcionalidades que deseé. Si el usuario elige el plan básico, este solo podra crear una playlist donde puede añadir la música que prefiera. En el plan premium puede tener hasta 5 playlist además de tener la posibilidad de descargar sus playlists para poder escucharlas sin conexión. Por último, el usuario VIP es capaz de tener hasta 12 playlists, descargar sus canciones y hacer sus playlists colaborativas con otro usuario del sistema.

## ¿Cómo se construye?

Para poder diseñar el programa las clases que se utilizaron son las siguientes:

### - MusicAPP

Esta es la clase principal donde los usuarios pueden registrarse y acceder a su cuenta. Tiene un vector con los usuarios del sistema que se hayana creado.

### - Usuario

Esta clase tiene una relación de compisición con MusicApp, siendo la clase hija de esta clase principal (MusicApp). Esta clase se deriva en distintos tipos de usuario por loq ue tiene una relación herencia con todos los tipos de usario que pueden crearse. Las características que comparte con todos sus derivados es que todos tienen nombre, contraseña, id del usuario y playlists, mientras que los métodos que comparten son los de crear y eliminar playlists.

##### .- Básico

Este tipo de usuario solo es capaz de tener una playlist, definido por su atributo de máximo número de playlists.

##### .- Premium

El usuario que sea premium tiene la capacidad de tener hasta 5 playlists determinadas por el mismo atributo de maxnum_pl además de poder descargar las canciones que contienen sus listas.

##### .- VIP

Por último, este usuario tiene las mismas características que los demás, con la diferencia de que puede tener hasta 12 playlists y hacer sus playlists colaborativas con otros usuarios del sistema.

### - Playlist

Esta clase también tiene una relación de composición como elemento hijo de la clase padre Usuario. cada playlist va a tener un nombre y un vector con las canciones que contiene. Además lo que se puede hacer con cada una es reproducir, pausar, reproducir de manera aleatoria, pasar a la siguiente canción, pasar a la canción previa, añadir canciones y eliminar canciones.

El diagrama UML de esta estructura es el siguiente:
![Music App drawio](https://github.com/EdgarRetes/Music-App---Proyecto-POO/assets/113946434/f727ffb8-2ddb-4ac5-b38b-5b0bbc8cad81)

## Ejecución

...



