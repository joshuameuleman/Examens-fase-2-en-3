# Memory Game

## Description

Write a C++ program to implement the **Memory Game**.

The game board consists of a number of cards arranged in pairs with identical symbols. The cards are initially hidden, and players take turns revealing two cards. The goal is to find as many matching pairs as possible.

## Requirements

### Technical Implementation

* Use a **2D array** to represent the game board.
* Make **extensive use of functions** and **function prototypes** for clean, modular code.
* **Do not use global variables**.
* Use **enumerations** to represent game states.

### Game Functionality

#### Player Input

* Ask for the **names of the two players** before starting the game.

#### Board Initialization

* The board is a grid of cards containing **pairs of matching symbols** (e.g., 4x4 grid = 8 pairs).
* Cards are **randomly placed** and **initially hidden**.
* Provide a constant (e.g., `DEBUG_MODE`) to **always show the cards** during development/testing.

#### Game Flow

* On their turn, each player **selects two cards** to reveal (using row and column coordinates).
* If the cards match, they **remain visible**, and the player scores a point.
* If not, the cards are hidden again, and the turn passes to the other player.

#### Game Over

* The game ends when **all pairs are found**.
* The player with the **most pairs wins**.
* In case of a **tie**, display a suitable message.

#### Restart Option

* Offer the option to **restart the game** after a round finishes.

#### Input Validation

* Ensure that selected card positions are:

  * Within the board bounds.
  * Not already revealed.
* Provide **clear error messages** for invalid moves.

## Example Console Output

```plaintext
*** Memory Game ***
Enter name of player 1: Alice
Enter name of player 2: Bob

Let's start! The board is 4x4.
You will be asked in turn to specify two positions in the format <row> <column>

Score:
Alice: 0 pairs
Bob: 0 pairs

   1 2 3 4
1 | | | |
-----------------------
2 | | | |
-----------------------
3 | | | |
-----------------------
4 | | | |

Alice, it's your turn!
Select your first card (row column): 1 1
Select your second card (row column): 2 2

   1 2 3 4
1 A | | |
-----------------------
2 | B | |
-----------------------
3 | | | |
-----------------------
4 | | | |

Sorry Alice, the cards do not match. Try again next turn!

Bob, it's your turn!
Select your first card (row column): 3 3
Select your second card (row column): 4 4

   1 2 3 4
1 | | | |
-----------------------
2 | | | |
-----------------------
3 | | C |
-----------------------
4 | | | C

Congratulations Bob! You found a pair!

Score:
Alice: 0 pairs
Bob: 1 pair
```

*(... The game continues until all pairs are matched ...)*

```plaintext
*** End of Game ***
Final Score:
Alice: 5 pairs
Bob: 3 pairs

Congratulations Alice! You have won the game with 5 pairs!
Well played Bob! Better luck next time!

Would you like to play again? (y/n)
```

## Optional Extensions

You may further expand the game with additional difficulty levels or features:

* Allow a **larger board size** to increase game duration.
* Let players **flip 3 cards** instead of 2.
* Add support for **more than 2 players**.
* Any other creative ideas you wish to implement!

