CC = g++
BIN_DIR = ./bin/
OBJ_DIR = ./obj/
SRC_DIR = ./src/
DEPS = $(SRC_DIR)period.h
OBJ = $(OBJ_DIR)MisurazioneTempi.o $(OBJ_DIR)PeriodNaive.o $(OBJ_DIR)PeriodSmart.o

all: $(OBJ)
	$(CC) $(OBJ_DIR)*.o -o $(BIN_DIR)MisurazioneTempi

# .o out of .cpp
%.o: $(SRC_DIR)%.cpp $(DEPS)
	$(CC) -c $< -o $(OBJ_DIR)$@
