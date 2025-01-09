# Projet S101 : Jeu en C++

Note: ce fichier est extrait du [dépôt GitHub](https://github.com/maxime-mp4/S101), et a été adapté pour le rendu du travail.

## Description

Ce projet a été réalisé dans le cadre de la ressource **R101** à l'IUT d'Aix-Marseille.
Le but était d'implémenter un jeu type [Pac-Man](https://fr.wikipedia.org/wiki/Pac-Man) programmé en C++, en répondant à certains besoins, qui seront détaillés plus tard.

Le jeu permet à plusieurs joueurs d'interagir avec une grille de jeu, de pouvoir se déplacer, avec une interface simple et fluide, et permet aussi la modification des paramètres d'une manière intuitive.
On expliquera ici les défis qu'était de faire ce jeu, ainsi que les étapes d'installation.

## Fonctionnalités principales

- **Grille de jeu** : Le jeu se déroule sur une grille de taille configurable, où des murs peuvent être placés aléatoirement, et des joueurs placés au préalable.
- **Gestion des joueurs** : Chaque joueur choisit un nom, un jeton (une lettre) et une couleur pour le rendre unique et identifiable.
- **Interaction avec la grille** : Les joueurs peuvent se déplacer, interagir avec des éléments comme les murs et les bordures.
- **Paramétrable** : Les joueurs peuvent, avant de lancer une partie, modifier les touches pour qu'elles puissent être convenable, ainsi que des paramètres essentiels (taille de grille, téléportation, fréquence des murs...)
- **Tour par tour** : Les joueurs prennent leur tour pour effectuer des actions, et le jeu gère automatiquement le passage d'un joueur à l'autre.

##  Technologies utilisées

- **Langage de programmation** : C++.
- **Bibliothèques** : bibliothèques standard (iostream, vector...) ainsi que [yaml-cpp](https://github.com/jbeder/yaml-cpp).
- **Makefile** : possibilité de rendre le jeu exécutable en 4 lettres.

## Installation

### Prérequis

Ici, les étapes seront décrites pour une machine sous Arch Linux. Les étapes d'installation sont les mêmes pour tout autre système UNIX.

Avant de commencer, assurez-vous que les outils suivants sont installés sur votre machine :

- **Git** : Outil de gestion de version pour cloner le dépôt.
    - Installation : `sudo pacman -S git`

- **CMake** : Outil de gestion de la compilation de projets C++.
    - Installation : `sudo pacman -S cmake`

- **Compilateur C++** (GCC ou Clang) : Vous devez disposer d'un compilateur C++ pour compiler le projet.
    - GCC : `sudo pacman -S gcc`
    - Clang : `sudo pacman -S clang`

Une fois ces outils installés, vous pourrez cloner le projet et le compiler sans problème.


### Étapes d'installation

#### 1 - yaml-cpp

1. Cloner le dépôt :
    ```bash
    git clone https://github.com/jbeder/yaml-cpp.git
    ```

2. Créer et accéder au répertoire de build
    ```bash
    cd yaml-cpp
    mkdir build && cd build
    ```

3. Configurer le projet avec CMake
    ```bash
    cmake ..
    ```

4. Spécifier le chemin d'installation
    ```bash
    cmake .. -DCMAKE_INSTALL_PREFIX=~/local
    ```
   
⚠️ Bien que redondante, cette étape est primordiale pour l'inclusion de la bibliothèque yaml-cpp. Sans cela, le programme ne pourra pas se compiler et le jeu ne pourra pas se lancer.

4. Compiler et installer
    ```bash
    make
    make install
    ```

#### 1 - Le projet

1. Cloner le dépôt :
    ```bash
    git clone https://github.com/maxime-mp4/S101.git
    ```

2. Accédez au répertoire du projet :
    ```bash
    cd S101/
    ```

3. Compilez le projet :
    ```bash
    make
    ```

4. Exécutez le programme :
    ```bash
    ./jeu
    ```

## Utilisation

Une fois le programme lancé, vous arriverez sur le menu principal. Dirigez-vous vers `[2] Réglages` et suivez les instructions pour afficher les réglages globaux, ou les modifier. Vous pourrez par la suite lancer le jeu : vous serez invité à entrer le nombre de joueurs, puis à spécifier un nom, un jeton et une couleur pour chaque joueur. Ensuite, le jeu commencera.

## Structure du projet

```
.
├── docs/                               # Répértoire contenant la documentation
├── build/                              # Généré après la compilation, contenant tous les fichiers objets
├── include/
    ├── game.h                          # Fichier d'en-tête du jeu
    ├── grid_management.h               # Fichier d'en-tête de la gestion de la grille 
    ├── menu.h                          # Fichier d'en-tête du menu
    ├── player_management.h             # Fichier d'en-tête de la gestion des joueurs 
    ├── settings.h                      # Fichier d'en-tête des paramètres
    ├── terminal_management.h           # Fichier d'en-tête de la gestion du terminal 
    └── type.h                          # Fichier d'en-tête des types globaux
├── src/
    ├── game.cpp                        # Fichier source du jeu
    ├── grid_management.cpp             # Fichier source de la gestion de la grille 
    ├── menu.cpp                        # Fichier source du menu
    ├── player_management.cpp           # Fichier source de la gestion des joueurs 
    ├── settings.cpp                    # Fichier source des paramètres
    └── terminal_management.cpp         # Fichier source de la gestion du terminal 
├── README.md                           # Documentation
├── Makefile                            # Fichier permettant la compilation
├── settings.yml                        # Paramètres utilisateur modifiable depuis le jeu
├── .default.yml                        # Paramètres par défaut en cas de fichier utilisateur non valide [NE PAS MODIFIER]
├── Doxyfile                            # Fichier de génération de la documentation
└── main.cpp                            # Point d'entrée du programme
```

## Documentation

Le projet est fourni avec une documentation Doxygen. Même si celle-ci est générée par défaut, les étapes suivantes indiqueront comment la mettre en place

### Pré-requis

- **Doxygen** : Outil de création de documentation (avec graphviz pour les graphes des fonctions)
    - Installation : `sudo pacman -S doxygen graphviz`

### Configuration

La configuration de la documentation se fait avec une simple commande :
```bash
doxygen Doxyfile
```
La documentation se générera automatiquement dans le dossier docs, et vous pourrez ensuite ouvrir le fichier index.html pour tout voir.

## Pour en savoir plus

Le projet était long à faire, ce n'était pas si simple honnêtement et on a eu énormément de soucis, donc on a dû réfléchir pour rendre ce meilleur code. On a ainsi procédé de la sorte :

1. Réécriture du code : on a refait le code à 90% pour le rendre plus flexible avec nos ambitions
2. Ajout de nouveautés : on a au fur et à mesure ajouté des features, individuellement. On a préféré se concentrer sur moins de features mais entièrement fonctionnelles plutôt que des bribes de codes inutiles.
3. Ajout du menu, des documentations et de toute érgonomie pour l'utilisateur : après avoir fait le jeu, on s'est occupé du menu afin de rendre le jeu agréable et plaisant, avec des crédits, des paramètres, du lore.
4. Création de la documentation (avec Doxygen). C'était le plus simple.

Ci-dessous sont les features que nous devont initiallement ajouter, mais que nous avons pas fait pour diverses raisons.

### Liste des bonus à impletementer

- Bombe (elimine/casse les murs adjacents au joueur)
- Inversion de position (entre le joueur qui active le bonus et un joueur au hasard)
- Permet de jouer une seconde fois (directement, non gardé dans l'inventaire)
- Déplacement x2 pendant 2 tours

## Annulé
- ~~Ajout de bonus : ils apparaiteront tous les 5 rounds et il sera un bonus au hasard parmis la liste, il sera ensuite activable pendant 5 rounds, avant de disparaitre de l'utilisateur.~~ Annulé par complexité
- ~~Inventaire joueur~~ Annulé par complexité
- ~~Fichier de score à lire/écrire, avec le score le plus haut pour chaque joueur~~ Remplacé par plus concis (téléportation et menu)
- ~~[OPTIONNEL] Ajout de la création de grilles~~ Annulé par complexité


## Licence

Ce projet est sous licence MIT. Consultez le fichier LICENSE pour plus de détails.
