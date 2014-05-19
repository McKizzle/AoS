#!/usr/bin/env sh

echo "Checking for homebrew."
if ! type brew 2>/dev/null; then
    echo "No brew installation found. Go to http://brew.sh/ and install brew with their installation command"
    echo "Afterwards make sure to run `brew doctor` to make sure there will be no issues"
    exit
else
    echo "Brew found, continuing the installation."
fi

brew install sdl2
brew tap homebrew/versions
brew install gcc # should install the newest version (gcc4.8)

brew install git
git clone https://github.com/McKizzle/AoS.git $HOME/AoS

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
