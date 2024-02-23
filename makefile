CC=gcc
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR} 

BIN=bin
LIB=lib
SRC=src

PROG=$(BIN)/LittleRogueNight
OBJ=$(BIN)/main.o $(BIN)/anim.o $(BIN)/labyrinthe.o $(BIN)/image.o $(BIN)/pile.o $(BIN)/file.o $(BIN)/menu.o

all: LittleRogueNight

LittleRogueNight: $(OBJ)
	${CC} -o ${PROG} $(OBJ) ${LIBS} ${INCLUDES}

${BIN}/%.o: $(SRC)/%.c ${LIB}/*.h
	${CC} -c $< -o $@

clean: 
	rm -f ${BIN}/*.o

mrproper: clean
	rm -f ${PROG}
