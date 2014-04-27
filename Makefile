# Detect the operating system 
# for now we will only worry about OS X and Linux. 
UNAME_S = $(shell uname -s)

CXXFLAGS = -g -std=c++11 -Wall -pedantic -pipe
CXXLIBS = -pthread

CXX = g++
ifeq ($(UNAME_S),Darwin)
    CXX = g++-4.8 #/usr/local/bin/g++-4.8
    GGT_FLAGS = -I ~/.aos/include/
    #OPEN_GL = -framework OpenGL
    #GGT_FLAGS = -lgmtl
endif
ifeq ($(UNAME_S),Linux)
    CXX = g++-4.8
    CXXFLAGS := $(CXXFLAGS) -Wl,--no-as-needed #:= prevents recursive expansion
    GL_FLAGS = -lGL -lGLU
    GGT_FLAGS = -I /usr/local/include/
endif

SDL_CFLAGS = $(shell sdl2-config --cflags) 
SDL_LDFLAGS = $(shell sdl2-config --libs)
SDL_SLIBS = $(shell sdl2-config --static-libs) 
SDL_ADD_SLIBS = -lSDL2_image

ALL_FLAGS = $(CXXFLAGS) $(CXXLIBS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_SLIBS) $(GL_FLAGS) $(GGT_FLAGS)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
# DIRS = $(SRC_DIR) $(OBJ_DIR) $(BIN_DIR)
# SRCS = $(wildcard $(SRC_DIR)/*.cpp) 
SRCS = main.cpp utils.cpp System.cpp Systems.cpp Object.cpp Game.cpp Player.cpp Ode.cpp Camera.cpp Grid.cpp GravityWell.cpp #Collision.cpp
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
BIN = $(BIN_DIR)/AoS

$(info $(SRCS))
$(info $(OBJS))
$(info $(BIN))
#$(info $(CXXFLAGS))

# target: link the objects. 
#	prerequisite: make sure that the objects are compiled first.
#	prerequisite: check for any $(BIN) prerequisites.
build: $(OBJS) $(BIN)
	$(CXX) -o $(BIN) $(OBJS) $(ALL_FLAGS)

cppcheck:
	cppcheck --quiet --enable=all --inconclusive --std=c++11 * 2> cppcheck.txt

# Builds and then runs the game.
run: build
	clear
	./$(BIN)	

# target: do work for creating the binary file. 
#	prerequisite: Make sure that there is a bin directory. 
$(BIN):	$(BIN_DIR)

# target: If a dependency asks for files in the OBJ_DIR that have teh .o extension then
#   build those objects.
#	prerequisite: Find the matching source file in the SRC_DIR.
# 	prerequisite: Make sure that the object directory exists.
# $(SRC_DIR)/%.h
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp $(OBJ_DIR)
	$(CXX) -o $@ -c $< $(ALL_FLAGS)

# target: Make make an executables directory if necessary. 
$(BIN_DIR): 
	mkdir -p ./$(BIN_DIR)

# target: Make an object directory if necessary. 
$(OBJ_DIR):
	mkdir -p ./$(OBJ_DIR)

print:
	make build --just-print

clean:
	/bin/rm -rf $(OBJ_DIR)
	/bin/rm -rf $(BIN_DIR)

db:
	make build --print-data-base

undef:
	make build --warn-undefined-variables

doxygen:
	cd ./doc/doxygen/; make doc

#$(OBJ)%.o: %.c
#	$(CXX) $@ -c $<

#$(OBJ)%.o: %.c %h
#	$(CXX) -c $< 
