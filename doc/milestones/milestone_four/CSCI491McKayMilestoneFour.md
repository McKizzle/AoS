# Milestone Four

## Schedule

Right now the project is about three days behind schedule. The primary cause was implementation difficulties and other assignments.

The application is capable of rendering the player's spaceship and accepting keyboard input.

## Implementation

As the sole developer, my primary focus this week has been implementing a class that allows me to swap out different integration functions for my game. Once properly implemented, objects will have a special function that calculates it's derivatives. 

## Challenges 

The first set of challenges that I faced was from SDL itself. After setting up my system, I discovered that I was unable to pass events to other objects in the code due to either a limitation in SDL or a in C++. I was able to pass the union reference to different objects but calling components of the union such as key events would return nothing. Since the main loop was running in the main thread, then bug may be due to an SDL limitation.

Besides wrestling with SDL. C++ has also consumed a fair amount of time. It is a complicated language and there are a lot of components to it. Not being aware of these components has resulted in an endless struggle with compiler errors and segfaults. 


