# Program Requirements

## Functional Requirements
### Application Requirements
Before the user can play the game the application must provide them with the following options.

  - Game runs on Linux and Darwin operating systems.
  - Upon game startup menu is displayed. From the menu users can:
      - Play the game.
      - View high scores.
      - Configure game settings
          - SFX 
          - Music
          - Resolution
      - Start a network based multilayer session. 
### Game Play Requirements
To make the game entertaining. The application must meet the following player requirements. 

  - Player has a space ship.
  - Space ship is controllable.
  - Space ship has at least a single weapon. 
  - Game generates collideable objects. 
  - Game generates offensive objects.
  - Player ship has shields.
  - Player has five lives. 
  - Player earns additional life after 10,000 points
  - As player score increases:
      - Collideable object speed increases.
      - Gravity effects on the player ship increases. 
      - Enemy ship targeting systems improve in accuracy. 

## Non-Functional Requirments
Delivering a pleasant game requires smooth a smooth game play and system properties that are related to the game. 
 
  - Run at 60fps. The game must update every 16.7 milliseconds. 
  - Support basic enemy AI system.
  - Use vector based collision detection. 
  - Physics Engine 
      - Support basic nbody interactions.
      - Support gravitational interactions. 
      - Support player-object collision detection. 
  - Libraries
      - The game will use SDL (Simple Direct Layer) library to display a game windows and handle user input. 
      - To render the game scene an SDL openGL context will be used. 
      - If possible use lib LAPACK for linear algebra operations. 
  - AI Engine
      - Enemy Ship AI 
      - Difficulty AI
  - Menu Engine
      - Handles user input when in menu mode. 
      - Configures game settings based on input. 
  - Render Engine
      - Render system to openGL context. 
  - Menu Render Engine
      - Render player menu to the screen. 



