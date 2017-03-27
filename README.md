# kudasai

Projet de jeu vidéo en C++ avec Vulkan avec MaitreVanDiest et delthas.

# Dépendances
## Cross plateforme
- Vulkan SDK : tout est inclus dans le dépôt, lié dynamiquement via le loader
- GLFW : headers inclus dans le dépot, liaison statique dans le makefile via pkg-config
## Unix
- Dlfnc : pour ouvrir les bibliothèques à l'execution. À installer et à ajouter au path
## Windows
- Loader Windows
## MacOS
C'est non. MacOS ne supporte pas Vulkan.

#Build
## Unix
Aller dans le dossier du dépôt avec un terminal et taper la commande :
```shell
make
```
## Windows
heu...
