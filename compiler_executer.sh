#!/bin/bash

# Faire un 'make all' des fichiers (supposant que vous avez un Makefile configuré)
make clean
make mrproper
make all
make test

# Se rendre dans le dossier 'bin'
cd bin

# Exécuter le programme 'LittleRogueLike'
./test_character
./test_file
./test_pile
./LittleRogueNight
