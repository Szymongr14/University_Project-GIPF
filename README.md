

# [GIPF](https://en.wikipedia.org/wiki/GIPF_(game)) - game engine implementation

This project was created for my the Data Structures and Algorithms course, focusing on the implementation of a GIPF game engine. The GIPF game is a strategic board game with  hexagonic board, which was the most challenging in this project.

## Coords of board is stored like that
![image](https://github.com/Szymongr14/Cpp/assets/53967196/c8cd85f9-7c5c-4a39-a108-eafb365d5244)

![image](https://github.com/Szymongr14/Cpp/assets/53967196/018fbdff-d1b6-41d8-8b38-31e79694f76d)


## Provided commands
 - **LOAD_GAME_BOARD**, followed by the game parameters and the state of the board. It should be checked whether the provided board state is valid, whether the sum of pawns for both players on the board and in reserves is correct, i.e., identical to the one provided in list L. It should also be checked whether any sequences of pawns triggering their collection have been removed.
 - **PRINT_GAME_BOARD** prints the current state of the board. After loading the game, it should be exactly the same as the printout provided during loading, assuming it was valid.
 - **DO_MOVE <xN - yM>** performs the given move for the active player on the current board.

## Sample input

![image](https://github.com/Szymongr14/Cpp/assets/53967196/59a03549-031e-451e-a76e-474bc87a402a)

## Output

![image](https://github.com/Szymongr14/Cpp/assets/53967196/28724dc1-83f0-4e81-832a-f660a06111a7)
