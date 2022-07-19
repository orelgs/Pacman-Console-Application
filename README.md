# Pacman-Console-Application
 This is a Pacman game console application created in C++, during a C++ course in The Academic College of Tel Aviv, Yaffo, 2022.

# File Formats
 Steps File Format:
 -Each steps file will start with the line: "Colours +" / "Colours -" - indicating whether or not the game shall run with colours.
 
 -The rest of the lines will have a number - identifying which entity is about to move, following the direction:
 0: Pacman
 1: Fruit
 2: Ghost #1
 3: Ghost #2
 4: Ghost #3
 5: Ghost #4
 
 (Note: Number of ghosts may change)
 
 A: Left
 W: Up
 S: Stay
 X: Down
 D: Right
 
 -Special treatment:
 Fruit - When a fruit appears, the line will read: "1 S X Y VALUE", indicating the fruit appears with the direction Stay,
 its X and Y location values, and the digit value of the fruit.
 When a fruit disappears, the line will read: "1 -".
 
 Result File Format:
 There will be 2 possible types of lines in this file:
 -PacmanDeath <Time Stamp> - indicating the point of time the pacman died on this screen.
 -FinishedScreen <Time Stamp> - indicating the point of time the pacman finished the screen successfully.