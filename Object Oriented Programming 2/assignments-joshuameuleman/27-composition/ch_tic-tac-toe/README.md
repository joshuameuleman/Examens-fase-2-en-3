# Tic-Tac-Toe

## Objective

Write a C++ program to implement the classic **Tic-Tac-Toe** game using a **2D array**. Your program should be cleanly structured with **functions and function prototypes**. Global variables should be avoided as much as possible. Use **enumerations** to track game status and player symbols.

## Requirements

### Base Features

* Use a 2D array to represent the game board.
* Ask for **names of both players** at the beginning.
* Each player takes turns to enter a **row** and **column** to place their symbol (`X` or `O`).
* Print the updated board after every move.
* Use **enumerations** to track:

  * The contents of a cell (`Empty`, `X`, `O`)
  * The status of the game (`Playing`, `Win`, `Draw`)

### Functionality Example

Below is an example of expected console output (input shown in **blue**):

```
*** Tic Tac Toe ***

Enter name of player 1 (uses X symbol): John
Enter name of player 2 (uses O symbol): Emily

Let's start! You will be asked in turn to specify a position in the format <row number><space><column number>

       |       |      
-----------------------
       |       |      
-----------------------
       |       |      

John: enter your position: 1 1
   X   |       |      
-----------------------
       |       |      
-----------------------
       |       |      

Emily: enter your position: 2 2
   X   |       |      
-----------------------
       |   O   |      
-----------------------
       |       |      
```

* If a player wins (3 of the same symbols in a row, column, or diagonal), the game ends with a congratulatory message.
* If the board is full and no player has won, declare a draw.
* After the game ends (win or draw), offer the option to **restart the game**.

## Input Validation

* Players must input valid row and column values.
* Prevent players from selecting an already occupied cell.
* Display a **clear error message** and prompt again in case of invalid input.

## Extension 1: Play Against the Computer

Update the game so that instead of two human players, the second player can be the **computer**.

* The player always plays first.
* The computer randomly selects an available cell for its turn.

## Extension 2: Increased Difficulty

Add one or more of the following advanced features:

### Option 1: Larger Board

* Allow players to select a custom board size (e.g., 4x4).
* Require **4 symbols in a row/column/diagonal** to win.

### Option 2: More Players

* Use a larger board and allow more than 2 players (each with a different symbol).
* The win condition remains 3 in a row (or configurable).

### Option 3: Your Own Idea

* Implement an original challenge (e.g., undo move, limited time per move, score tracking, etc.)

## Code Structure Guidelines

* Use **function prototypes** and break your code into **reusable functions**.
* Use **enumerations** to represent game states and cell contents.
* Optionally, split the program into **multiple files** (e.g., `main.cpp`, `game.cpp`, `game.h`).
* Avoid global variables wherever possible.

