#!/usr/bin/env sh

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

git clone https://github.com/McKizzle/AoS.git $HOME/AoS
cd $HOME/AoS
make clean && make -j4

# Run the software
bin/AoS --mode=3

