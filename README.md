# LittleRogueNight : Adventure in a Labyrinth
**from 19/01/2024 to 25/04/2024**
## Creators
  **Students in L2 Informatique Le Mans**
- **Maelig Pesantez** or `pixis-py` mail: maelig.pesco@gmail.com 
- **Clément Lelandais** or `clay-l1` mail: clelandais510@gmail.com
- **Enzo Desfaudais** or `B0rno` mail: enzo.dsfa@gmail.com

## About The Game 

* LittleRogueNight is a game created for school purpose in **L2 Informatique at Le Mans**, it is a roguelike based on LittleNightmares.
* Each level features a new configuration of rooms and corridors, making each game unique. The aim is to collect treasures, avoid or fight monsters, foil traps and escape quickly.
* In this game, you walk, run, jump and fight to escape from a dark place. Beware of monsters, they can be pretty unprevisible...

## Features

* Procedurally Generated Maze: Each level offers a new layout of rooms and corridors.
* Treasures and Riddles: Explore and recover hidden treasures while solving riddles.
* Monsters and Traps: Battle a variety of monsters and avoid deadly traps.
* Dynamic Bosses: Powerful bosses chase the hero through the labyrinth at the end of every stage.
* Store System: Buy equipment and weapons to strengthen your character.
* Secret Zones: Discover hidden places brimming with riches and rare items.
* Reward System: Be rewarded according to your solving time, performance and discovers of secret objects/places.
* Save System : Save your current game and start and stop when you want.

## Requirements
* Linux

## Installation
* Please use
```
git clone git@github.com:Pixis-py/LittleRogueNight.git
```

## Makefile Usage
* make test files : 
```
make test
```
* make game file : 
```
make all
```
## Bash file Usage
* Simply use the following command to compile test and game, and launch tests and game : 
```
chmod 777 compiler_executer.sh
./compiler_executer.sh
```
## Documentation
* HTML and LaTeX documentation can be found at [/doc/documentation/html](https://github.com/Pixis-py/LittleRogueNight/tree/main/doc/documentation/html) and [/doc/documentation/latex](https://github.com/Pixis-py/LittleRogueNight/tree/main/doc/documentation/latex).
* However, if you want to generate it yourself, place yourself in the main folder and execute:
```
doxygen Doxyfile
```
## Report (Rapport)
* Report can be found as a pdf and LaTeX with all sources at [/doc/rapport](https://github.com/Pixis-py/LittleRogueNight/tree/main/doc/rapport).
* However, if you want to generate it yourself, place yourself in /doc/rapport and execute:
```
pdflatex main.tex
```
## How to play 
### Controls:
* To go left, press **q**.
* To go right, press **d**.
* To go up, press **spacebar**. Note that you can also go up left and up right pressing spacebar + q and spacebar + d.
* To go drift, press **shift**. Note that you can drift left and drift right pressing shift + q and shift + d. Drifting is your main attack against monsters.

## Steps of the projects 
* we have 14 weeks to do this project
* This is our Gantt : https://docs.google.com/spreadsheets/d/1N0l1cyXdz2jDQ7uw1sJApE_-XL1_57rDjFjR6rCOs2c/edit#gid=1115838130
* This is the entire description of the game https://docs.google.com/document/d/15iS2K25yt7P2-7-cuAcIXqtBpi8PWvzSjXZDD9PCUwc/edit?usp=sharing
