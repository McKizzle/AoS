[![Build Status](https://travis-ci.org/McKizzle/AoS.png?branch=master)](https://travis-ci.org/McKizzle/AoS)

AoS
===

AoS will deliver the all time classic Asteroids straight to your computer. 
With a few minor differences though gravity and meaner bosses. 
Prepare to have your fingers blown away as you sporadicly attempt to maneuver through debris fields of hell, dodge enemy super lasers, and gravity cannons. 

## Debian Installation, Building, and Execution
Open the terminal and run the following set of commands and then jump to the _Ubuntu Installation, Building, and Execution_ section.

    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo add-apt-repository -y ppa:zoogie/sdl2-snapshots

## Ubuntu Installation, Building, and Execution
Open the terminal and install the following applications. 

    sudo apt-get update -y -qq
    sudo apt-get install -qq -y g++-4.8
    sudo apt-get install -qq -y libsdl2-dev
    sudo apt-get install -qq -y libasound2-dev
    sudo apt-get install -qq -y libxss-dev
    sudo apt-get install -qq -y libxxf86vm-dev
    sudo apt-get install -qq -y libpulse-dev
    sudo apt-get install -qq -y git
    sudo apt-get install -qq -y scons
    sudo apt-get install -qq -y wget
    sudo apt-get install -qq -y libboost-dev
    sudo apt-get install -qq -y libboost-test-dev
    sudo apt-get install -qq -y libftgl2
    sudo apt-get install -qq -y freeglut3-dev freeglut3
    wget -N https://github.com/imvu/gmtl/archive/master.zip -O $HOME/gmtl.zip
    unzip $HOME/gmtl.zip -d $HOME/
    cd $HOME/gmtl-master/
    sudo scons install
    sudo ln -sf /usr/local/include/gmtl-0.7.0/gmtl /usr/local/include/gmtl

    git clone git@github.com:McKizzle/AoS.git $HOME/AoS
    cd $HOME/AoS
    make clean && make -j4
    
    # Run the software
    bin/AoS --mode=3


## OS X Installation, Building, and Execution
First install Homebrew by running the command in the _Install Homebrew_ section at [brew.sh](http://brew.sh/) in the OS X terminal. 
After installing homebrew make sure to run `brew doctor` to ensure that their will be no conflicts with brew installations. 

To build and run AoS run the following commands in the terminal.  

    brew install sdl2
    brew tap homebrew/versions
    brew install gcc # should install the newest version (gcc4.8)    

    brew install git
    git clone git@github.com:McKizzle/AoS.git $HOME/AoS

    mkdir $HOME/.aos 
    brew install wget
    wget -N https://github.com/imvu/gmtl/archive/master.zip -O $HOME/.aos/gmtl.zip
    unzip $HOME/gmtl.zip -d $HOME/.aos

    brew install scons # needed for the gmtl installer. 
    cd $HOME/.aos/gmtl-master
    scons install prefix=$HOME/.aos
    ln -sf $HOME/.aos/include/gmtl-0.7.0/gmtl $HOME/.aos/include/gmtl

    # build the software
    cd $HOME/AoS
    make clean && make -j4

    # run the software
    bin/AoS --mode=3


