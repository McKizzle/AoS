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
The compiler I will be using to build the project is `gcc 4.8`. 
In simple terms, here is a list of dependencies.

  - gcc 4.8
  - lapack (not confirmed)

## Building
To build the application `cd` to the root directory of the project and run ``make build``. 
Once make has finished compiling the files the binary file __AoS__ should be in the __bin__ directory.

## Execution
To execute the application simply run ``bin/AoS`` from the terminal. 


