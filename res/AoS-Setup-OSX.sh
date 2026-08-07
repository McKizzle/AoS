#!/usr/bin/env sh

echo "Checking for homebrew."
if ! type brew 2>/dev/null; then
    echo "No brew installation found. Go to http://brew.sh/ and install brew with their installation command"
    echo "Afterwards make sure to run `brew doctor` to make sure there will be no issues"
    exit
else
    echo "Brew found, continuing the installation."
fi

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
