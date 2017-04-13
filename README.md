# kudasai

Projet de jeu vidéo en C++ avec Vulkan avec MaitreVanDiest et delthas.

## Dépendances
### Cross plateforme
- Vulkan SDK : tout est inclus dans le dépôt, lié dynamiquement via le loader
- GLFW : headers inclus dans le dépot, liaison statique via pkg-config
- CMake : outil d'automatisation de build, à installer

### Unix
- pkg-config : outil d'aide au build de certaines libraries
- Dlfnc : header inclus dans le dépôt
- GLFW3 : à installer et compiler, voir [ici](http://www.glfw.org/download.html)

### Windows
Pas de dépendances particulières

### MacOS
Non supporté.

##Build
Il faut avoir installé une toolchain C++. Les fichiers exécutables seront placés dans le dossier ```bin```.
### Unix
Aller dans le dossier du dépôt avec un terminal et taper les commandes suivantes :
```shell
cmake -DCMAKE_BUILD_TYPE=Release . # pour la version release, ou
cmake -DCMAKE_BUILD_TYPE=Debug . # pour la version debug
make
```
### Windows
Lancer CMake et indiquer le dossier du dépôt pour l'emplacement du code source et l'emplacement où placer les fichiers binaires. Indiquer éventuellement sa toolchain si demandé. Cliquer sur configurer puis générer.
