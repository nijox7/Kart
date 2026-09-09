# Kart - Jeu de voiture controlable avec Arduino

## Présentation
L'objectif de ce jeu est de marquer le maximum de but avec un Kart pouvant être contrôlé à l'aide de la souris et le clavier ou à l'aide d'une manette simulée à l'aide d'une carte Arduino, des câbles et 3 boutons poussoir.

## Comment jouer

Pour pouvoir controler le Kart il existe 2 moyens. La manette ou le clavier.

### Manette
Il faut injecter le programme `src/Kart.ino` dans une carte Arduino qui doit avoir respectivement sur ces ports:

- Port 2, bouton "Right"
- Port 3, bouton "Accelerate"
- Port 4, bouton "Left"

Il faut donc relier à chacun de ces ports un bouton-poussoir qui correspondra au nom associé.

Enfin il faut modifier la macro `ARDUINO_PATH` (voir dans le fichier `src/Field.cpp`) de manière à ce qu'elle corresponde au fichier de sortie du moniteur série de la carte Arduino.\
Par défaut elle est égale à `/dev/tyyACM0`.

Enfin les commandes sont:

- Avancer: Bouton du milieu (Accelerate)
- Direction à droite: Bouton de droite (Right)
- Direction à gauche: Bouton de gauche (Left)

### Clavier et Souris
Pour jouer au clavier et à la souris les touches sont les suivantes:

- Avancer: `Z`
- Freiner: `Shift`
- Réinitialiser la position de la balle: `R`
- Direction: Pointeur de la souris

## Compilation
Dans le terminal exécuter la commande:
- qmake

Puis ajouter à la fin du fichier `projet.pro`: 
      
      QT += core gui qml quick widgets

Enfin, dans le terminal exécuter ces dernières commandes:
- qmake -project
- make

Après une modification, il suffit de recompiler avec `make`.
## Sources utilisées

- ["Ecrire sa première application avec Qt 4" - developpez.com](https://alp.developpez.com/tutoriels/qt/premiere-application/?page=sommaire)
- ["Tuto pour créer un jeu en QT, QML, C++ - Chaîne youtube 'Kali'"](https://www.youtube.com/playlist?list=PLeYV3WjZWmHyYUe-BElUVNeFYTmpOQ9Xq)
- ["Documentation officielle de QT - odc.qt.io"](https://doc.qt.io/)
- ["Rappels sur les listes en C++ - w3schools.com"](https://www.w3schools.com/cpp/cpp_list.asp)
