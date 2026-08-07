# OSX Installation Procedures 

First install Homebrew by running the command in the _Install Homebrew_ section at [brew.sh](http://brew.sh/). After installing homebrew make sure to run `brew doctor` to ensure that their will be no conflicts with brew installations. 

## Libraries
To build and run AoS run the following commands. 

    brew install sdl3
    # clang++ ships with the Xcode Command Line Tools, which Homebrew already
    # requires, so no separate compiler install is needed.

    brew install git
    brew install glm
    git clone https://github.com/McKizzle/AoS.git $HOME/AoS

## Build
    # build the software
    cd $HOME/AoS
    make clean && make -j4

## Run

    # run the software
    bin/AoS --mode=3
