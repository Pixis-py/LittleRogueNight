CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR} 

BIN_DIR=bin
PROG=${BIN_DIR}/LittleRogueNight

all: LittleRogueNight

LittleRogueNight: ${BIN_DIR}/main.o ${BIN_DIR}/anim.o ${BIN_DIR}/image.o
	${CC} -o ${PROG} ${BIN_DIR}/main.o ${BIN_DIR}/anim.o ${BIN_DIR}/image.o ${LIBS} ${INCLUDES}

${BIN_DIR}/main.o: src/main.c lib/anim.h lib/image.h
	${CC} -c src/main.c -o ${BIN_DIR}/main.o

${BIN_DIR}/anim.o: src/anim.c lib/image.h
	${CC} -c src/anim.c -o ${BIN_DIR}/anim.o

${BIN_DIR}/image.o: src/image.c
	${CC} -c src/image.c -o ${BIN_DIR}/image.o

clean: 
	rm -f ${BIN_DIR}/*.o

mrproper: clean
	rm -f ${PROG}

