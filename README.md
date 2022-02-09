# Boggle

Project is part of Stanford's CS 106B: Programming Abstractions Course and the code authored can be found in src/bogglesearch.cpp

Problem Description:
Boggle is a board game with a 4x4 square grid of letter cubes where players try to make words by connecting letters on adjacent cubes. For this part of the assignment, you will write code to search a Boggle board for words using backtracking.

We provide you with starter code in bogglemain.cpp that implements the text user interface of the game. You must write the functions to search the board for words in bogglesearch.cpp.

Letter cubes are 6­sided dice with a letter on each side rather than a number. In the real game, you shake up the letter cubes and lay them out on the board. In our version, we will ask you to type the 16 letters that make up the board.

The goal is to find words on the board by tracing a path through neighboring letters. Two letter cubes are neighbors if they are next to each other horizontally, vertically, or diagonally. Therefore there are up to eight neighbors near a cube. Each cube can be used at most once in a given word.

In the real­life version of this game, all players work at the same time, listing the words they find on a piece of paper. But in the version we will write, a single human player will play a single turn against an omniscient computer opponent.

The human player plays first, entering words one by one. Your code verifies that the word is is at least 4 letters long, then uses backtracking to see if the word can be made using letters on the board, using any cube at most once.

Once the player has found as many words as they can, the computer player takes a turn. The computer searches through the board using recursive backtracking to find all the possible words that can be formed. The computer's algorithm is similar to the human's, but rather than verifying the existence of a single word in the board, you are exhaustively finding the set of all possible words.
