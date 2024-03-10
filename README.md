## Project Description
Playable Tetris clone using C++ and SDL.

### Controls
| Key | Desc |
|:----|:-----|
| Esc or P | Pause game
| X | Rotate counter clockwise
| C | Rotate clockwise
| G | Toggle to draw ghost block
| Left Arrow | Move left
| Down Arrow | Move down
| Right Arrow | Move right
| Space | Places the block where ghost block is at

## Design Pattern
This game uses the observer pattern to update the background color after reaching a new level. The observer (tetris.cpp) notifices all subjects (renderer.cpp) that level has changed and the subject can do stuff based on the info it got. 
This pattern was chosen as it was the one that fitted the game project the most. When making the game, I wanted to use flyweight pattern but after implenting the core of tetris, it didn't seemed to fit and observer was picked instead.

Observer class can be found at observer.h and renderer class inherits the observer class and overrides the OnNotify() function. The subject (tetris.cpp) has a vector of observers and notifies them on level change. It registers the observers before the game starts in game.cpp. 

## Screenshots & Gameplay
![image](https://github.com/FG22-GP/214-design-patterns-assignment-solo/assets/16321823/0cda3bce-0ba1-4c78-bfac-c8c7b52ba8a1)

<br>

![image](https://github.com/FG22-GP/214-design-patterns-assignment-solo/assets/16321823/957bad96-0001-4954-b76c-c332e27d3466)

<br>

https://github.com/FG22-GP/214-design-patterns-assignment-solo/assets/16321823/1992a911-2e5d-450b-bed5-882efd964517
