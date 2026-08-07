# Detect the operating system
# for now we will only worry about OS X and Linux.
UNAME_S = $(shell uname -s)

CXXFLAGS = -std=c++17 -Wall -pedantic -pipe -g # Minimize what the user needs to install.
CXXLIBS = -pthread

CXX = clang++
TST_CXX = clang++
ifeq ($(UNAME_S),Darwin)
    CXX = clang++
    TST_CXX = clang++
    GLM_FLAGS = -I $(shell brew --prefix glm)/include # glm is header-only; installed via `brew install glm`
    BOOST_INCLUDE = -I /usr/local/include/
    BOOST_LIB = -L /usr/local/lib/ -lboost_unit_test_framework-mt
endif
ifeq ($(UNAME_S),Linux)
    CXX = clang++
    TST_CXX = clang++
    CXXFLAGS := $(CXXFLAGS) -Wl,--no-as-needed #:= prevents recursive expansion
    GL_FLAGS = -lGL -lGLU
    GLM_FLAGS = # glm is header-only; `dnf install glm-devel` puts headers on the default include path
    BOOST_INCLUDE = -L/usr/include/boost
    BOOST_LIB = -L /usr/lib/x86_64-linux-gnu/ -lboost_unit_test_framework
endif

SDL_CFLAGS = $(shell pkg-config --cflags sdl3)
#SDL_LDFLAGS = $(shell pkg-config --libs sdl3)
SDL_SLIBS = $(shell pkg-config --libs sdl3)

ALL_FLAGS = $(CXXFLAGS) $(CXXLIBS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_SLIBS) $(GL_FLAGS) $(GLM_FLAGS) $(BOOST_LIBS)

TST_FLAGS := -I src $(ALL_FLAGS) $(BOOST_INCLUDE) $(BOOST_LIB)

TST_DIR = tests
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
# DIRS = $(SRC_DIR) $(OBJ_DIR) $(BIN_DIR)
# SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TSTS = gravity_tests.cpp collision_tests.cpp system_tests.cpp
SRCS = utils.cpp System.cpp Systems.cpp Object.cpp Game.cpp Player.cpp Ode.cpp Camera.cpp Grid.cpp GravityWell.cpp Collidable.cpp Planet.cpp Collision.cpp Projectile.cpp Score.cpp Weapon.cpp #QuadTree.cpp QuadTreeNode.cpp
#AsteroidsOnSteroids.cpp
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
	cppcheck --quiet --enable=all --inconclusive --std=c++23 --library=gnu $(SRC_DIR) $(TST_DIR) 2> cppcheck.txt

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
