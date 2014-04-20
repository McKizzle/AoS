# AoS Installation Procedure
Open the terminal unzip `v0.5.0.zip` and navigate into the extracted directory. 

## OS X
  Still unsupported but, using `homebrew` to install all of the needed libraries should do the trick.

    ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"
    brew install gcc48
    brew install sdl2
    brew install scons
    brew install wget

    wget -N https://github.com/imvu/gmtl/archive/master.zip -O $HOME/gmtl.zip
    unzip -o $HOME/gmtl.zip -d $HOME/
    cp res/gmlt-stuff/SConstruct $HOME/gmtl-master/
    cd $HOME/gmtl-master/
    scons install=$HOME/.aos
    cd -

## Ubuntu
  To build AoS run the following commands in the terminal. 

    sudo apt-get update -y -qq
    sudo apt-get install -qq -y g++-4.8
    sudo apt-get install -qq -y libsdl2-dev
    sudo apt-get install -qq -y scons
    sudo apt-get install -qq -y wget

    wget -N https://github.com/imvu/gmtl/archive/master.zip -O $HOME/gmtl.zip
    unzip -o $HOME/gmtl.zip -d $HOME/
    cd $HOME/gmtl-master/
    sudo scons install
    cd -

\newpage

## Debian 
  To build AoS run the following commands. 

    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo add-apt-repository -y ppa:zoogie/sdl2-snapshots
    sudo apt-get update -y -qq
    sudo apt-get install -qq -y g++-4.8
    sudo apt-get install -qq -y libsdl2-dev
    sudo apt-get install -qq -y scons
    sudo apt-get install -qq -y wget

    wget -N https://github.com/imvu/gmtl/archive/master.zip -O $HOME/gmtl.zip
    unzip -o $HOME/gmtl.zip -d $HOME/
    cd $HOME/gmtl-master/
    sudo scons install
    cd -



