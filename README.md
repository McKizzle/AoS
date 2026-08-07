AoS
===

AoS will deliver the all time classic Asteroids straight to your computer. 
With a few minor differences though gravity and meaner bosses. 
Prepare to have your fingers blown away as you sporadicly attempt to maneuver through debris fields of hell, dodge enemy super lasers, and gravity cannons. 

## Debian Installation, Building, and Execution
Follow the _Ubuntu Installation, Building, and Execution_ section below — the same steps apply.

## Ubuntu Installation, Building, and Execution
Open the terminal and install the following applications. 

    sudo apt-get update -y -qq
    sudo apt-get install -qq -y clang
    sudo apt-get install -qq -y libsdl3-dev
    sudo apt-get install -qq -y libasound2-dev
    sudo apt-get install -qq -y libxss-dev
    sudo apt-get install -qq -y libxxf86vm-dev
    sudo apt-get install -qq -y libpulse-dev
    sudo apt-get install -qq -y git
    sudo apt-get install -qq -y libglm-dev
    sudo apt-get install -qq -y wget
    sudo apt-get install -qq -y libboost-dev
    sudo apt-get install -qq -y libboost-test-dev
    sudo apt-get install -qq -y libftgl2

    git clone https://github.com/McKizzle/AoS.git $HOME/AoS
    cd $HOME/AoS
    make clean && make -j4
    
    # Run the software
    bin/AoS --mode=3


## OS X Installation, Building, and Execution
First install Homebrew by running the command in the _Install Homebrew_ section at [brew.sh](http://brew.sh/) in the OS X terminal. 
After installing homebrew make sure to run `brew doctor` to ensure that their will be no conflicts with brew installations. 

To build and run AoS run the following commands in the terminal.  

    brew install sdl3
    # clang++ ships with the Xcode Command Line Tools, which Homebrew already
    # requires, so no separate compiler install is needed.

    brew install git
    brew install glm
    git clone https://github.com/McKizzle/AoS.git $HOME/AoS

    # build the software
    cd $HOME/AoS
    make clean && make -j4

    # run the software
    bin/AoS --mode=3
