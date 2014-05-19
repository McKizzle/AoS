[![Build Status](https://travis-ci.org/McKizzle/AoS.png?branch=master)](https://travis-ci.org/McKizzle/AoS)

AoS
===

AoS will deliver the all time classic Asteroids straight to your computer. 
With a few minor differences though gravity and meaner bosses. 
Prepare to have your fingers blown away as you sporadicly attempt to maneuver through debris fields of hell, dodge enemy super lasers, and gravity cannons. 

## Download the Project
`cd` to the directory you want to clone the project to. Then tell git to clone with:

    git clone https://github.com/McKizzle/AoS

Now you should be able to work on the code and compile the project yourself. 

## Dependencies
This project uses the new threading tools provided in the C++11 standard library. 
So make sure that your compiler supports the C++11. 
The compiler I will be using to build the project is `gcc 4.8`. To make the setup process simple run the following
commands to install the required libraries.

    sudo apt-get update -y -qq
    sudo apt-get install -qq -y g++-4.8
    sudo apt-get install -qq -y libsdl2-dev
    sudo apt-get install -qq -y libasound2-dev
    sudo apt-get install -qq -y libxss-dev
    sudo apt-get install -qq -y libxxf86vm-dev
    sudo apt-get install -qq -y libpulse-dev

### Generic Graphics Toolkit
AoS makes use of the Graphics Math Template Library to perform its math calculations. You will need to install it. Linux users need to run the following set of commands. 

    sudo apt-get install -qq -y scons 
    sudo apt-get install -qq -y wget
    wget https://github.com/imvu/gmtl/archive/master.zip
    unzip master.zip
    cd gmtl-master/
    sudo scons install

### OS X Users
First install Homebrew by running the command in the _Install Homebrew_ section at [brew.sh](http://brew.sh/) in the OS X terminal. 
After installing homebrew make sure to run `brew doctor` to ensure that their will be no conflicts with brew installations. 

## Libraries
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
    make -j4

    # run the software
    bin/AoS

### Debian Users
Debian users will have to run these two commands before they can run the commands listed above. 

    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test 
    sudo add-apt-repository -y ppa:zoogie/sdl2-snapshots

## Building
To build the application `cd` to the root directory of the project and run ``make build``. 
Once make has finished compiling the files the binary file __AoS__ should be in the __bin__ directory.

## Documentation
You can either navigate through the header files for the necessary documentation. Or you have the
option to run ``make doxygen`` to run the doxygen command and build the documentation. 

In order to build the documentation make sure to run:

    sudo apt-get install -qq -y doxygen

## Execution
To execute the application simply run ``bin/AoS`` from the terminal in the root directory of the project. 


