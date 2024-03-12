CC=gcc
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR} 

BIN=bin
LIB=lib
OBJ=obj
SRC=src
TEST=test

PROG=$(BIN)/LittleRogueNight
OBJECT=$(OBJ)/main.o $(OBJ)/anim.o $(OBJ)/labyrinthe.o $(OBJ)/image.o $(OBJ)/pile.o $(OBJ)/file.o $(OBJ)/menu.o $(OBJ)/bouton.o

all: LittleRogueNight

LittleRogueNight: $(OBJECT)
	${CC} -o ${PROG} $(OBJECT) ${LIBS} ${INCLUDES}

${OBJ}/%.o: $(SRC)/%.c ${LIB}/*.h
	${CC} -c $< -o $@

clean: 
	rm -f ${OBJ}/*.o

mrproper: clean
	rm -f ${BIN}/*

