# Detect the operating system 
# for now we will only worry about OS X and Linux. 
UNAME_S = $(shell uname -s)

CXXFLAGS = -std=c++11 -Wall -pedantic -pipe -g 
CXXLIBS = -pthread

CXX = g++
TST_CXX = g++
ifeq ($(UNAME_S),Darwin)
    CXX = g++-4.8 
    TST_CXX = g++
    GGT_FLAGS = -I ~/.aos/include/
    BOOST_INCLUDE = -I /usr/local/include/
    BOOST_LIB = -L /usr/local/lib/ -lboost_unit_test_framework-mt 
endif
ifeq ($(UNAME_S),Linux)
    CXX = g++-4.8
    TST_CXX = g++-4.8
    CXXFLAGS := $(CXXFLAGS) -Wl,--no-as-needed #:= prevents recursive expansion
    GL_FLAGS = -lGL -lGLU
    GGT_FLAGS = -I /usr/local/include/
    BOOST_INCLUDE = -L/usr/include/boost
    BOOST_LIB = -L /usr/lib/x86_64-linux-gnu/ -lboost_unit_test_framework

endif

SDL_CFLAGS = $(shell sdl2-config --cflags) 
SDL_LDFLAGS = $(shell sdl2-config --libs)
SDL_SLIBS = $(shell sdl2-config --static-libs) 
SDL_ADD_SLIBS = -lSDL2_image

ALL_FLAGS = $(CXXFLAGS) $(CXXLIBS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_SLIBS) $(GL_FLAGS) $(GGT_FLAGS) $(BOOST_LIBS)

TST_FLAGS := -I src $(ALL_FLAGS) $(BOOST_INCLUDE) $(BOOST_LIB)

TST_DIR = tests
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
# DIRS = $(SRC_DIR) $(OBJ_DIR) $(BIN_DIR)
# SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TSTS = gravity_tests.cpp collision_tests.cpp
SRCS = utils.cpp System.cpp Systems.cpp Object.cpp Game.cpp Player.cpp Ode.cpp Camera.cpp Grid.cpp GravityWell.cpp Collidable.cpp Planet.cpp Collision.cpp
MAIN = main.cpp
MBJS = $(MAIN:%.cpp=$(OBJ_DIR)/%.o)
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
TBJS = $(TSTS:%.cpp=$(TST_DIR)/%.o)
BIN = $(BIN_DIR)/AoS
TBINS = $(TSTS:%.cpp=$(TST_DIR)/%.test)

$(info $(TBIN))
#$(info $(TBJS))
#$(info $(SRCS))
#$(info $(OBJS))
#$(info $(BIN))
#$(info $(CXXFLAGS))

# target: link the objects. 
#	prerequisite: make sure that the objects are compiled first.
#	prerequisite: check for any $(BIN) prerequisites.
build: $(OBJS) $(MBJS) $(BIN)
	$(CXX) -o $(BIN) $(MBJS) $(OBJS) $(ALL_FLAGS)

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

# Build all of the test executables. 
test: $(TBINS)

run_tests:
	sh $(TST_DIR)/run_tests.sh $(TBINS)

# target: create each test binary. 	
$(TST_DIR)/%.test: $(TST_DIR)/%.o $(OBJS)
	$(CXX) -o $@ $< $(OBJS) $(TST_FLAGS)

$(TST_DIR)/%.o: $(TST_DIR)/%.cpp $(TST_DIR) 
	$(CXX) -o $@ -c $< $(TST_FLAGS)

clean_tests:
	rm -f $(TST_DIR)/*.o 
	rm -f $(TST_DIR)/*.test

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
