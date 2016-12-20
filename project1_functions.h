// Name: Adedotun Odutola
// User: aco0008
// Filename: project1_functions.h
// Sources: Worked in study group to understand the project as a whole.
// How To Compile: makefile

#ifndef PROJECT1_FUNCTIONS_H
#define PROJECT1_FUNCTIONS_H

#include <iostream>
#include <assert.h>
#include <sstream>
#include <cctype>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int MAX_NUMBER_OF_HIGH_SCORES = 5;
const int EMPTY = -1; // Used to represent an empty position in an array of type int
const int NUMBER_OF_ENCOUNTERS = 6;

enum inGameUserDecisions {MOVE_FORWARD=1, QUIT_GAME=5};
enum DecisionType {IN_GAME=1, MAIN_MENU=2};
enum MainMenuDecision {START_GAME=1, VIEW_HIGH_SCORES=2, QUIT=3};
enum EncounterChances {PUZZLE_CHANCE=30, PROFESSOR_CHANCE=40, GRADUATE_STUDENT_CHANCE=50, GRUNT_WORK_CHANCE=65, GRADE_PAPERS_CHANCE=75, NOTHING_CHANCE=100};
enum PlayerAttributes {TIME=1, MONEY=2, INTELLIGENCE=3};


struct PlayerModel
{
	int time;
	double money;
	int intelligence;
	int distanceFromEnd;
};

struct UserModel
{
	string userName;
};

struct PuzzleModel
{
	string question;
	string answer;
	int deltaAttribute; //Change in an arbritrary player attribute
	PuzzleModel *next;
};
typedef PuzzleModel* PuzzlePtr;

// Function pointer type definitions
typedef void (*EncounterFunctionPtr) (PlayerModel& player); 
typedef void (*InGameUserDecisionFunctionPtr) (PlayerModel& player);

void displayName(string userName);
/* Input:
 * 	(1) The name of the user
 * Prints the username on the console.
 */

void promptUser();
/* Prompts the user to enter their name  */

void displayMenuOptions();
/* Displays the main menu */

bool validateAnswer(string userInput, PuzzlePtr puzzle);
/* Input:
 * 	(1) The input of the user
 * 	(2) A pointer to the  current puzzle being answered
 * Checks to see if the user has entered the correct answer
 * Returns false if user enters incorrect answer
 * Returns true if user enters correct answer
 */

bool validateDecision(string userInput, int decisionType);
/* Input:
 * 	(1) The input of the user
 * 	(2) The type of decision the user has made
 * Checks to see if the user has made any invalid decisions
 * (e.g.) Inputting the letter 'F' when they were prompted to enter a number
 * Returns true if userInput is valid
 * Returns false if userInput is invalid
 */

void changeAttribute(PlayerModel& player, PuzzlePtr puzzle, bool isCorrect);
/* Input:
 * 	(1) The player
 * 	(2) Pointer to the current puzzle being answered
 * 	(3) Boolean value for whether the player answered the puzzle correctly or incorrectly
 * Changes a random player attribute. Increases that attribute if isCorrect is true
 * Decreases that attribute if isCorrect is false
 */

void displayHighScores(int highScores[], string highScoreHolders[], int size);
/* Input:
 * 	(1) Array of the top 5 scores
 * 	(2) Array of the names of the top 5 scores 
 * 	(3) The size of the arrays
 * Displays the top 5 high scores 
 */

void handlePuzzle(PuzzlePtr puzzle, PlayerModel& player);
/* Input:
 * 	(1) Current puzzle being answered
 * 	(2) The player
 * Displays a randomly generated puzzle question, 
 * takes user input, validates answer, and 
 * uses the amount of points the puzzle is worth to modify
 * one of the player's attributes
 */

PuzzlePtr generatePuzzle(PuzzlePtr head, int numberOfPuzzles, PlayerModel& player);
/* Input:
 * 	(1) Pointer that points to the first node in linked list
 * 	(2) Total number of puzzles to choose from
 * 	(3) The player
 * Generates a random puzzle
 * Returns a pointer to the puzzle generated
 */

void displayGameOptions(PlayerModel player);
/* Input:
 * 	(1) The player
 * Displays the options a player has to choose from
 * for their turn
 */

void displayCharacter(PlayerModel player);
/* Input:
 * 	(1) The player
 * Displays how much intelligence, money and time
 * a player has
 */

void startGame(PlayerModel& player);
/* Input: 
 * 	(1) The player
 * Initializes all character attributes to a random number
 * Displays the game options
 */

void viewHighScores(int highScores[], string highScoreHolders[], int size);
/* Input:
 * 	(1) Array of the top 5 scores
 * 	(2) Array of the names of the top 5 scores 
 * 	(3) The size of the arrays
 * Calls displayHighScores 
 */

void terminateProgram();
/* Terminates the program */

bool generateEncounter(PlayerModel& player, EncounterFunctionPtr encounters[], int encounterChances[], PuzzlePtr head);
/* Input:
 * 	(1) The player
 * 	(2) An array of function pointers for all of the encounter functions
 * 	(3) Array of encounter chances
 * 	(4) Pointer to first Puzzle in linked list
 * Generates a random encounter
 * Returns true if encounter was successfully generated
 * Returns false if encounter was not generated
 */

void quitGame(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Resets all player attributes and calls displayMenuOptions 
 */

void moveForward(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Player takes a step forward.
 * Causes a random encounter to happen
 */

void readTechnicalPapers(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Decrease time and increase intelligence */

void searchForChange(PlayerModel& player);
/* Input: 
 * 	(1) The player
 * Decrease time and increase money */

void viewCharacter(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Call displayCharacter */

void encounterPuzzle(PuzzlePtr head, PlayerModel& player);
/* Input:
 * 	(1) Pointer to the head of the Puzzle Linked List
 * 	(2) The player
 * call generatePuzzle 
 */

void encounterProfessor(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Decrease time and increase intelligence 
 */

void encounterGraduateStudent(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Decrease time 
 */

void encounterGruntWork(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Decrease time and intelligence 
 */

void encounterGradePapers(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Decrease time and increase money 
 */

void encounterNothing(PlayerModel& player);
/* Input:
 * 	(1) The player
 * Tell the user nothing happens
 */

int calculateScore(PlayerModel player);
/* Input:
 * 	(1) The player
 * Calcualtes the player's score
 */

void appendScore(int score, UserModel user, int highScores[], string highScoreHolders[], int& size);
/* Input:
 * 	(1) The player's score
 * 	(2) The user
 * 	(3) The current top 5 high scores
 * 	(4) The names of the players with the top 5 high scores
 * 	(5) Size of arrays
 * Appends the player's high score and username to their respective arrays
 */

void shiftRight(int highScores[], string highScoreHolders[], int location, int size);
/* Input:
 * 	(1) The current top 5 high scores
 * 	(2) The names of the players with the top 5 high scores
 * 	(3) The index where the shifting will start at
 * 	(4) The size of the arrays
 * Shifts all the values to the right starting from location
 */

void shiftLeft(int highScores[], string highScoreHolders[], int location);
/* Input:
 * 	(1) The current top 5 high scores
 * 	(2) The names of the players with the top 5 high scores
 * 	(3) The index where the shifting will start at
 * Shifts all the values to the left starting from location
 */

void writeHighScoresToFile(int highScores[], string highScoreHolders[], int size);
/* Input:
 * 	(1) The current top 5 high scores
 * 	(2) The names of the players with the top 5 high scores
 * 	(3) Size of arrays
 * Writes high scores to a file */

int readHighScoresFile(int highScores[], string highScoreHolders[], ifstream& inStream, stringstream& ss, int& size);
/* Input:
 * 	(1) The current top 5 high scores
 * 	(2) The names of the players with the top 5 high scores
 * 	(3) Input file stream of object 
 * 	(4) A stringstream object
 * 	(5) Size of arrays
 * Return size of the highScores and highScoreHolders array
 * Reads high scores from a file into array
 */

bool openFile(ifstream& inStream, string filename);
/* Input:
 * 	(1) Input file stream of oject
 * 	(2) The name of the file being opened
 * Opens the file in stream
 * Returns false if file could not be opened
 * Returns true if file could be opened
 */
bool actionPerformed(int decision, PlayerModel& player, int& decisionType, 
			int highScores[], string highScoreHolders[], InGameUserDecisionFunctionPtr inGameUserDecisions[], int size);
/* Input:
 * 	(1) The user's decision
 * 	(2) The player
 * 	(3) Type of decision
 * 	(4) The current top 5 high scores
 * 	(5) The names of thep players with the top 5 high scores
 * 	(6) Array of function pointers for all of the in game user decision functions
 * 	(7) The size of the score arrays
 * Uses decision to perform the corresponding action
 * Returns true if action is successfully performed
 * Returns false if action is not performed
 */

void createPuzzleQuestions(PuzzlePtr& head, PuzzlePtr& pretail, PuzzlePtr& tail);
/* Input:
 * 	(1) Pointer that points to first node in linked list
 * 	(2) Pointer that points to second to last node in linked list
 * 	(3) Pointer that points to last node in linked list
 * Initializes linked list with puzzle questions
 */

bool isGameOver(PlayerModel player);
/* Input:
 * 	(1) The player
 * Checks to see if the game is over
 * Returns true if game is over
 * Returns false if game is not over
 */

bool hasPlayerWon(PlayerModel player);
/* Input:
 * 	(1) The player
 * Checks to see if player has won
 * Returns true if player won
 * Returns false if player has not won
 */

/* Test driver declarations */

void test_validateAnswer();
/* Test driver for validateAnswer */

void test_validateDecision();
/* Test driver for validateDecision */

void test_changeAttribute();
/* Test driver for changeAttribute */

void test_generatePuzzle();
/* Test driver for generatePuzzle() */

void test_startGame();
/* Test driver for startGame() */

void test_encounters();
/* Test driver for all of the encounter functions 
 * Except encounterPuzzle()
 */

void test_generateEncounter();
/* Test driver for generateEncounter */

void test_inGameDecisions();
/* Test driver for all of the functions
 * relating to in game user decisions.
 * Except viewCharacter() 
 */

void test_shiftRight();
/* Test driver for shiftRight() */

void test_shiftLeft();
/* Test driver for shiftLeft() */

void test_appendScore();
/* Test driver for appendScore() */

void test_writeHighScoresToFile();
/* Test driver for writeHighScoresToFile() */

void test_readHighScoresFile();
/* Test driver for readHighScoresFile() */

void test_actionPerformed();
/* Test driver for actionPerformed() */

void test_isGameOver();
/* Test driver for isGameOver() */

void test_hasPlayerWon();
/* Test driver for hasPlayerWon() */

#endif // PROJECT1_FUNCTIONS_H


























