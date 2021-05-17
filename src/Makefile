CC = g++
BIN_DIR = ../bin/
OBJ_DIR = ../obj/
# SRC_DIR = ./src/
DEPS = period.h
OBJ = $(OBJ_DIR)MisurazioneTempi.o $(OBJ_DIR)PeriodNaive.o $(OBJ_DIR)PeriodSmart.o

all: $(OBJ)
	$(CC) $(OBJ_DIR)*.o -o $(BIN_DIR)MisurazioneTempi

debug: $(OBJ)
	$(CC) -Og $(OBJ_DIR)*.o -o $(BIN_DIR)MisurazioneTempi.debug

# .o out of .cpp
$(OBJ_DIR)%.o: %.cpp $(DEPS)
	$(CC) -c $< -o $(OBJ_DIR)$@
