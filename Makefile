# Detect the operating system 
# for now we will only worry about OS X and Linux. 
UNAME_S := $(shell uname -s)

CXXFLAGS = -g -std=c++11 -Wall -pedantic
CXXLIBS = -pthread

CXX = g++
ifeq ($(UNAME_S),Darwin)
    CXX = g++-4.8 #/usr/local/bin/g++-4.8
endif
ifeq ($(UNAME_S),Linux)
    CXX = g++
    CXXFLAGS := $(CXXFLAGS) -Wl,--no-as-needed
endif


SDL_CFLAGS := $(shell sdl2-config --cflags) 
SDL_LDFLAGS := $(shell sdl2-config --libs)
SDL_SLIBS := $(shell sdl2-config --static-libs) 
SDL_ADD_SLIBS = -lSDL2_image

ALL_FLAGS := $(CXXFLAGS) $(CXXLIBS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_SLIBS)

CURR_DIR = $(notdir $(shell pwd))
SRC_DIR = src/
OBJ_DIR = obj/
BIN_DIR = bin/
SRC = $(wildcard $(SRC_DIR)*.cpp)
OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
BIN = bin/AoS

#test: $(OBJ)
#	@echo "$(SRC)"
#	@echo "$(OBJ)"
#	@echo "$(BIN)"
#
#%.o:
#	@echo "Making em objects"

build: 
	#@echo "$(OBJ)"
	@echo "Building the project"
	@echo "$(CXX) -o $(BIN) $^ $(ALL_FLAGS)"

#%.o: %.c 
#$(OBJ)%.o: $(SRC)%.c
#	@echo "$(CXX) -o $@ -c $<"

#%.o: %.c %h
#	@echo "$(CXX) -c $<"

dirs:
	mkdir -p ./$(OBJ_DIR)
	mkdir -p ./$(SRC_DIR)
	mkdir -p ./$(BIN_DIR)

srcs:
	touch $(SRC_DIR){src1.cpp,src2.cpp,src3.cpp}
	touch $(SRC_DIR){src1.h,src2.h,src3.h}

print:
	make build --just-print

#db:
#	make build --print-data-base
#
#undef:
#	make build --warn-undefined-variables
#
#$(OBJ)%.o: %.c
#	$(CXX) $@ -c $<
#
#$(OBJ)%.o: %.c %h
#	$(CXX) -c $< 
#

#clean:
#	/bin/rm -f $(OBJ)
#	/bin/rm -f $(BIN)
