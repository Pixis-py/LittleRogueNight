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
OBJECT=$(OBJ)/main.o $(OBJ)/anim.o $(OBJ)/labyrinthe.o $(OBJ)/image.o $(OBJ)/pile.o $(OBJ)/file.o $(OBJ)/menu.o $(OBJ)/bouton.o $(OBJ)/character.o 

all: LittleRogueNight

LittleRogueNight: $(OBJECT)
	${CC} -o ${PROG} $(OBJECT) ${LIBS} ${INCLUDES}

${OBJ}/%.o: $(SRC)/%.c ${LIB}/*.h
	${CC} -c $< -o $@

test: test_character test_file test_pile

test_character: $(OBJ)/test_character.o $(OBJ)/character.o
	${CC} -o $(BIN)/test_character $(OBJ)/test_character.o $(OBJ)/character.o -lcunit 

$(OBJ)/test_character.o: $(TEST)/test_character.c 
	${CC} -c $(TEST)/test_character.c -o $(OBJ)/test_character.o

${OBJ}/%.o: $(SRC)/%.c ${LIB}/*.h
	${CC} -c $< -o $@

test_file: $(OBJ)/test_file.o $(OBJ)/file.o
	${CC} -o $(BIN)/test_file $(OBJ)/test_file.o $(OBJ)/file.o -lcunit 

$(OBJ)/test_file.o: $(TEST)/test_file.c 
	${CC} -c $(TEST)/test_file.c -o $(OBJ)/test_file.o

${OBJ}/%.o: $(SRC)/%.c ${LIB}/*.h
	${CC} -c $< -o $@

test_pile: $(OBJ)/test_pile.o $(OBJ)/pile.o
	${CC} -o $(BIN)/test_pile $(OBJ)/test_pile.o $(OBJ)/pile.o -lcunit 

$(OBJ)/test_pile.o: $(TEST)/test_pile.c 
	${CC} -c $(TEST)/test_pile.c -o $(OBJ)/test_pile.o

${OBJ}/%.o: $(SRC)/%.c ${LIB}/*.h
	${CC} -c $< -o $@

clean: 
	rm -f ${OBJ}/*.o

mrproper: clean
	rm -f ${BIN}/*

