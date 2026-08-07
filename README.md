AoS
===

AoS will deliver the all time classic Asteroids straight to your computer. 
With a few minor differences though gravity and meaner bosses. 
Prepare to have your fingers blown away as you sporadicly attempt to maneuver through debris fields of hell, dodge enemy super lasers, and gravity cannons. 

## Debian Installation, Building, and Execution
Open the terminal and run the following set of commands and then jump to the _Ubuntu Installation, Building, and Execution_ section.

    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test

## Ubuntu Installation, Building, and Execution
Open the terminal and install the following applications. 

    sudo apt-get update -y -qq
    sudo apt-get install -qq -y g++-4.8
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
    brew tap homebrew/versions
    brew install gcc # should install the newest version (gcc4.8)    

    brew install git
    brew install glm
    git clone https://github.com/McKizzle/AoS.git $HOME/AoS

    # build the software
    cd $HOME/AoS
    make clean && make -j4

    # run the software
    bin/AoS --mode=3
