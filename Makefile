# Detect the operating system 
# for now we will only worry about OS X and Linux. 
UNAME_S := $(shell uname -s)

CXXFLAGS := -g -std=c++11 -Wall -pedantic
CXXLIBS := -pthread

CXX := g++
ifeq ($(UNAME_S),Darwin)
    CXX := g++-4.8 #/usr/local/bin/g++-4.8
endif
ifeq ($(UNAME_S),Linux)
    CXX := g++
    CXXFLAGS := $(CXXFLAGS) -Wl,--no-as-needed
endif


SDL_CFLAGS := $(shell sdl2-config --cflags) 
SDL_LDFLAGS := $(shell sdl2-config --libs)
SDL_SLIBS := $(shell sdl2-config --static-libs) 
SDL_ADD_SLIBS := -lSDL2_image

ALL_FLAGS := $(CXXFLAGS) $(CXXLIBS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_SLIBS)

#CURR_DIR = $(notdir $(shell pwd))
SRC_DIR := src/
OBJ_DIR := obj/
BIN_DIR := bin/
SRC := $(wildcard $(SRC_DIR)*.cpp)
OBJ := $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
BIN := bin/AoS

$(info $(SRC))
$(info $(OBJ))
$(info $(BIN))

build:	$(OBJ) 
	@echo "Building the project"
	@echo "g++ -o $(BIN) $^"

$(OBJ)%.o:	
	@echo "Building object $@"
	touch $@

dirs:
	mkdir -p ./$(OBJ_DIR)
	mkdir -p ./$(SRC_DIR)
	mkdir -p ./$(BIN_DIR)

tsfls:
	touch $(SRC_DIR)src1.cpp
	touch $(SRC_DIR)src2.cpp
	touch $(SRC_DIR)src3.cpp
	touch $(SRC_DIR)src1.h
	touch $(SRC_DIR)src2.h
	touch $(SRC_DIR)src3.h
	touch $(OBJ_DIR)main.o

print:
	make build --just-print

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(BIN)


#$(OBJ)%.o: %.c
#	$(CXX) $@ -c $<

#$(OBJ)%.o: %.c %h
#	$(CXX) -c $< 

#db:
#	make build --print-data-base

#undef:
#	make build --warn-undefined-variables
