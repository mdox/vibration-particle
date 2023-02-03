CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -O3 -march=native -fno-sized-deallocation
LIBS = -lm -lGL -lglfw -lGLEW -fopenmp

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: main

main: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@
	du -h main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o main

test: clean main
	./main
