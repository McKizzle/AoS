# OSX Installation Procedures 

First install Homebrew by running the command in the _Install Homebrew_ section at [brew.sh](http://brew.sh/). After installing homebrew make sure to run `brew doctor` to ensure that their will be no conflicts with brew installations. 

# Libraries
To build and run AoS run the following commands. 

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


