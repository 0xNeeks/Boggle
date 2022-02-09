/* Name: Nicholas Cuevas (SCPD Student)
 * Course: CS106B
 * Section Leader: Diwakar Ganesan (cganesan)
 * Assignment Description:
 * This assignment file is the Boggle Search recursion problem.
 * Additional Resources Used: Reviewed the University of Pittsburgh Boggle Recursion for Initial Hints and Inspiration
 * Found here:
 * http://people.cs.pitt.edu/~jinlei/cs1501/rc2.ppt
 * Additional Resources Used: Reviewed the Developmentality Website for Boggle Recursion  Initial Hints and Pseudocode Inspiration.
 * This pseudocode was more specific but still more general approaches on how to solve the problem recursively.
 * Found here:
 * https://developmentality.wordpress.com/tag/boggle/
 * Additional Resources Used: Looked to a similar solution on Geeks for Geeks for help on how to loop through the adjacent cubes
 * Found here:
 * https://www.geeksforgeeks.org/boggle-find-possible-words-board-characters/
 * Late Days Used: 2 (3 Total Used So Far)
*/

#include <string>
#include "grid.h"
#include "lexicon.h"
#include "set.h"
#include "bogglegui.h"
#include "strlib.h"
using namespace std;

/* Function Prototypes */
bool humanWordSearchHelper(Grid<char>& board, Grid<bool>& visitedCube, string word, int row, int col);
void computerWordSearchHelper(Grid<char>& board, const Lexicon& dictionary, const Set<string>& humanWords, Set<string>& chosenWords, Grid<bool>& visitedCube, string prefixPassed, int rowPassed, int colPassed);
void addToScore(int wordLength);
void addToScoreComputer(const Set<string>& chosenWords);

/*
 * The humanWordSearch function has the board parameter and dictionary passed by reference, as well as the human's entered word passed as a string.
 * The function clears the highlighted board for each new word search. Then the intiial checks the word length minimum and a valid word is passed. If not, immediately
 * returns false. A grid of booleans is used to mark the visited cubes. The function loops through the board to find the first letter of the word and if found, marks
 * that cube as visited, and then calls the recursive helper function to check whether the word is found or not. Finally the appropriate number of points are given to the
 * human if the word was found, by calling a helper function. Returns true if found, false otherwise. Highlights the cubes that make up the word.
 */
bool humanWordSearch(Grid<char>& board, Lexicon& dictionary, string word) {
    BoggleGUI::clearHighlighting();

    if (!dictionary.contains(word) || word.length() < BoggleGUI::MIN_WORD_LENGTH) {
        return false;
    }

    Grid<bool> visitedCube(board.numRows(), board.numCols(), false);
    string wordAsUpper = toUpperCase(word);

    bool humanSearch = false;

    //loop to find first letter of the word
    for (int row = 0; row < board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            char letter = board.get(row,col);

            if (letter == wordAsUpper[0]) {
                humanSearch = humanWordSearchHelper(board, visitedCube, wordAsUpper.substr(1), row, col);
                if (humanSearch) {
                    BoggleGUI::setHighlighted(row, col, true);
                    int wordLength = word.length();
                    addToScore(wordLength); //finds and sets human's score
                    return humanSearch;
                }

            }
        }
    }

    return humanSearch;
}

/*
 * The humanWordSearchHelper function passes the board and visitedCube Grids by reference, the human's word string, the row, and column.
 * The function base case is when the word is empty to return true. Otherwise, it loops through all the adjacent positions to the first letter of
 * the word. The first letter is determined previously and its appropriate position on the board is passed by the row and column coordinates.
 * Then the function checks the bounds and whether the cube has been visited yet. If not, the letter at that row/column of the board is compared against
 * the first letter of teh word. If true, marks that adjacent cube as visited, then recurses with the substring of the word, eventually returning true if the
 * conditions hold, otherwise unchoosing the marked cube and continuing to check the adjacent letters.
 * Assumes valid parameters passed and other constraint checks done previously.
 */
bool humanWordSearchHelper(Grid<char>& board, Grid<bool>& visitedCube, string word, int rowPassed, int colPassed) {

    if (word.empty()) {
        return true;

    } else {
        //loop through all adjacent letters from a given cube position
        for (int row=rowPassed-1; row <= rowPassed+1; row++) {
            for (int column = colPassed-1; column <= colPassed+1; column++) {

                if (board.inBounds(row, column) && !visitedCube[row][column]) {
                    char letter = board.get(row,column);

                    if (letter == word[0]) {
                        visitedCube[row][column] = true; //choose

                        if (humanWordSearchHelper(board, visitedCube, word.substr(1), row, column)) { //explore
                            BoggleGUI::setHighlighted(row, column, true);
                            return true;
                        }

                        BoggleGUI::setHighlighted(row, column, false); //unchoose
                        visitedCube[row][column] = false;

                    } else {
                        BoggleGUI::setHighlighted(row, column, false);
                        visitedCube[row][column] = false;
                    }

                }

            }

        }

        return false;
    }

}

/*
 * The addToScore function has a wordLength parameter.
 * The function sets the valid score for the human based on the word length.
 * Assumes a positive number and that the case to add zero points is taken care of elsewhere.
 */
void addToScore(int wordLength) {
    if (wordLength > 7) {
        BoggleGUI::scorePointsHuman(11);

    } else if (wordLength == 7) {
        BoggleGUI::scorePointsHuman(5);

    } else if (wordLength == 6) {
        BoggleGUI::scorePointsHuman(3);

    } else if (wordLength == 5) {
        BoggleGUI::scorePointsHuman(2);

    } else {
        BoggleGUI::scorePointsHuman(1);
    }
}

/*
 * The addToScoreComputer function passes the chosenwords set by reference.
 * The function loops through each word in the set, then sets the valid score for the computer based on the word length.
 * Assumes a positive number and that the case to add zero points is taken care of elsewhere.
 */
void addToScoreComputer(const Set<string>& chosenWords) {
    for (string word : chosenWords) {
        int wordLength = word.length();
        if (wordLength > 7) {
            BoggleGUI::scorePointsComputer(11);

        } else if (wordLength == 7) {
            BoggleGUI::scorePointsComputer(5);

        } else if (wordLength == 6) {
            BoggleGUI::scorePointsComputer(3);

        } else if (wordLength == 5) {
            BoggleGUI::scorePointsComputer(2);

        } else {
            BoggleGUI::scorePointsComputer(1);
        }

    }

}

/*
 * The computerWordSearch function has a board parameter passed by reference, a dictionary passed by reference, and a set of the selected human words passed by reference.
 * The function creates a set of chosen words to keep track of the valid computer generated words. The visitedCube grid keeps track of the cube's already visited as a boolean.
 * The string prefix is created to help prune the dictionary, eventually becoming a word to add to the valid computer words set.
 * Loops through the board's rows and columns, grabbing the letter to use as the prefix basis the words to find. This is done by passing the prefix to the helper function
 * where all possible words starting with that letter will be added to the set.
 * The cube is then reset to use for future searches. Finally, the score is added up for the computer and the set of found words is returned.
 * Assumes valid parameters are passed.
 */
Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary, Set<string>& humanWords) {
    Set<string> chosenWords;
    Grid<bool> visitedCube(board.numRows(), board.numCols(), false);
    string prefix = "";

    //loop to set first letter of potential words search, based on the position on the board
    for (int row=0; row<board.numRows(); row++) {
        for (int col = 0; col < board.numCols(); col++) {
            visitedCube[row][col] = true;
            char letter = board.get(row,col);
            prefix = letter;
            computerWordSearchHelper(board, dictionary, humanWords, chosenWords, visitedCube, prefix, row, col);
            visitedCube[row][col] = false;
        }
    }

    addToScoreComputer(chosenWords); //finds and sets computer's score

    return chosenWords;
}

/*
 * The computerWordSearchHelper function has a board, dictionary, humanwords, chosenwords, and visited cubes passed by reference. The prefix string, row, and column are also passed.
 * The function loops through all the adjacent cube positions. Additionally, if the board is in bounds and the cube hasn't been checked yet, it is marked and the letter of that position
 * is added to the prefix to check against the dictionary's prefixes to prune the search. Then the prefix is checked against the human words, chosen words, and min length before adding
 * it to the computer's word set. Then it explores the next row/column for a new letter to add to the prefix. The cube is marked false for creating a valid prefix if it is not in the dictionary.
 * Valid words are added to the set which is passed by reference to use in the computerWordSearch function.
 * Assumes valid parameters are passed.
 */
void computerWordSearchHelper(Grid<char>& board, const Lexicon& dictionary, const Set<string>& humanWords, Set<string>& chosenWords, Grid<bool>& visitedCube, string prefixPassed, int rowPassed, int colPassed) {
    //loop through all adjacent letters from a given cube position
    for (int row=rowPassed-1; row <= rowPassed+1; row++) {
        for (int column = colPassed-1; column <= colPassed+1; column++) {

            if (board.inBounds(row, column) && !visitedCube[row][column]) {
                visitedCube[row][column] = true; //choose
                char letter = board.get(row,column);
                string prefix = prefixPassed + letter;

                if (dictionary.containsPrefix(prefix)) {
                    if (dictionary.contains(prefix) && !humanWords.contains(prefix) && !chosenWords.contains(prefix) && prefix.length() >= BoggleGUI::MIN_WORD_LENGTH) {
                        prefix = toUpperCase(prefix);
                        chosenWords.add(prefix);
                    }

                    computerWordSearchHelper(board, dictionary, humanWords, chosenWords, visitedCube, prefix, row, column); //explore
                }

                visitedCube[row][column] = false;

            }

        }
    }

}
