// Name: Adedotun Odutola
// User: aco0008
// Filename: project1_test.cpp
// Sources: Worked in study group to understand the project as a whole.
// How To Compile: makefile

#include "project1_functions.h"


void test_validateAnswer()
{
	string userInput = "Wrong";
	PuzzlePtr head, pretail, tail;
	createPuzzleQuestions(head, pretail, tail);
	cout << "Unit Testing 1: Function - validateAnswer() \n";

	cout << "Case 1: Answer is wrong\n";
	assert(false ==  validateAnswer(userInput, head));
	cout << "Case passed ...\n" << endl;

	userInput = "38";
	cout << "Case 2: Answer is correct\n";
	assert(true ==  validateAnswer(userInput, head));
	cout << "Case passed ...\n" << endl;
}

void test_validateDecision()
{
	string userInput = "0708076324";
	int decisionType = IN_GAME;
	cout << "Unit Testing 2: Function - validateDecision() \n";

	cout << "Case 1: User Input is too long\n";
	assert(false ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;
	
	userInput = "$";
	cout << "Case 2: User Input is not a digit\n";
	assert(false ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;
	
	userInput = "1";
	decisionType = IN_GAME + 3;
	cout << "Case 3: Invalid decision type\n";
	assert(false ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;
	
	userInput = "7";
	decisionType = IN_GAME;
	cout << "Case 4: Decision type is IN_GAME and User Input is greater than 5\n";
	assert(false ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;

	userInput = "-1";
	cout << "Case 5: Decision type is IN_GAME and User Input is less than 1\n";
	assert(false ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;

	userInput = "4";
	cout << "Case 6: Decision type is IN_GAME and User Input is in the range of 1 and 5\n";
	assert(true ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;

	userInput = "5";
	decisionType = MAIN_MENU;
	cout << "Case 7: Decision type is MAIN_MENU and User Input is greater than 3\n";
	assert(false ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;

	userInput = "-1";
	cout << "Case 8: Decision type is MAIN_MENU and User Input is less than 1\n";
	assert(false ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;

	userInput = "3";
	cout << "Case 9: Decision type is MAIN_MENU and User Input is in the range of 1 and 3\n";
	assert(true ==  validateDecision(userInput, decisionType));
	cout << "Case passed ...\n" << endl;

}

void test_changeAttribute()
{
	PlayerModel player;
	bool isCorrect = true;
	PuzzlePtr head, pretail, tail;	
	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	int total = player.time + player.money + player.intelligence;
	int newTotal = 0;
	createPuzzleQuestions(head, pretail, tail);

	cout << "Unit Testing 3: Function - changeAttribute() \n";

	cout << "Case 1: isCorrect is true\n";
	changeAttribute(player, head, isCorrect);
	newTotal = player.time + player.money + player.intelligence;
	assert(newTotal > total);
	cout << "Case passed ...\n" << endl;

	total = player.time + player.money + player.intelligence;
	isCorrect = false;
	cout << "Case 2: isCorrect is false\n";
	changeAttribute(player, head, isCorrect);
	newTotal = player.time + player.money + player.intelligence;
	assert(newTotal < total);
	cout << "Case passed ...\n" << endl;
}

void test_generatePuzzle()
{
	PlayerModel player;
	PuzzlePtr head, pretail, tail;	
	player.time = 5;
	player.intelligence = 5;
	player.money = 5;
	createPuzzleQuestions(head, pretail, tail);
	int numberOfPuzzles = 3;
	cout << "Unit Testing 4: Function - generatePuzzle() (Also encounterPuzzle()) \n";

	cout << "Case 1: Successfully generates a puzzle\n";
	PuzzlePtr current = generatePuzzle(head, numberOfPuzzles, player);
	assert(current != NULL);
	cout << "Case passed ...\n" << endl;
}

void test_startGame()
{
	PlayerModel player;
	cout << "Unit Testing 5: Function - startGame() \n";

	cout << "Case 1: All player attributes initialized\n";
	startGame(player);
	assert(player.time >= 10);
	assert(player.intelligence >= 10);
	assert(player.money >= 10);
	assert(player.distanceFromEnd >= 20);
	cout << "\nCase passed ...\n" << endl;
}

void test_encounters()
{
	PlayerModel player;
	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	cout << "Unit Testing 6: All encounter functions (except encounterPuzzle()) \n";

	cout << "Case 1: encounterProfessor() - Time decreased and Intelligence increased\n";
	encounterProfessor(player);
	assert(player.time < 5);
	assert(player.intelligence > 5);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	cout << "Case 2: encounterGraduateStudent() - Time decreased\n";
	encounterGraduateStudent(player);
	assert(player.time < 5);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	cout << "Case 3: encounterGruntWork() - Time and Intelligence decreased\n";
	encounterGruntWork(player);
	assert(player.time < 5);
	assert(player.intelligence < 5);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	cout << "Case 4: encounterGradePapers() - Time decreased and Money increased\n";
	encounterGradePapers(player);
	assert(player.time < 5);
	assert(player.money > 5);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	cout << "Case 5: encounterNothing() - Player attributes do not change\n";
	encounterNothing(player);
	assert(player.time == 5);
	assert(player.money == 5);
	assert(player.intelligence == 5);
	cout << "Case passed ...\n" << endl;
}

void test_generateEncounter()
{
	EncounterFunctionPtr encounters[] = 
	{
		encounterProfessor,
		encounterGraduateStudent,
		encounterGruntWork,
		encounterGradePapers,
		encounterNothing
	};
	int encounterChances[] = {PROFESSOR_CHANCE, GRADUATE_STUDENT_CHANCE, GRUNT_WORK_CHANCE, GRADE_PAPERS_CHANCE, NOTHING_CHANCE};
	PlayerModel player;
	PuzzlePtr head, pretail, tail;	
	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 5;
	createPuzzleQuestions(head, pretail, tail);

	cout << "Unit Testing 7: Function - generateEncounter() \n";

	cout << "Case 1: Encounter successfully generated\n";
	bool encounterGenerated = generateEncounter(player, encounters, encounterChances, head);
	assert(encounterGenerated == true);
	cout << "\nCase passed ...\n" << endl;
}

void test_inGameDecisions()
{
	PlayerModel player;
	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 5;
	cout << "Unit Testing 8: All in-game user decision functions (except viewCharacter()) \n";

	cout << "Case 1: quitGame() - All player attributes set to zero\n";
	quitGame(player);
	assert(player.time == 0);
	assert(player.intelligence == 0);
	assert(player.money == 0);
	assert(player.distanceFromEnd == 0);
	cout << "\nCase passed ...\n" << endl;
	
	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 5;	
	cout << "Case 2: moveForward() - distanceFromEnd decreases by one\n";
	moveForward(player);
	assert(player.distanceFromEnd == 4);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	cout << "Case 3: readTechnicalPapers() - Time decreases and Intelligence increases\n";
	readTechnicalPapers(player);
	assert(player.time < 5);
	assert(player.intelligence > 5);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 5;	
	cout << "Case 4: searchForChange() - Time decreases and Money increases\n";
	searchForChange(player);
	assert(player.time < 5);
	assert(player.money > 5);
	cout << "\nCase passed ...\n" << endl;
}

void test_shiftRight()
{
	int highScores[5] = {12, 15, 76, 90};
	string highScoreHolders[5] = {"Name1", "Name2", "Name3", "Name4"};
	int location = 1;
	int size = 4;

	cout << "Unit Testing 9: Function - shiftRight() \n";

	cout << "Case 1: Elements successfully shifted to the right\n";
	shiftRight(highScores, highScoreHolders, location, size);
	int newHighScores[5] = {12, 15, 15, 76, 90};
	string newHighScoreHolders[5] = {"Name1", "Name2", "Name2", "Name3", "Name4"};
	size++;
	for(int x = 0; x < size; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}
	
	cout << "\nCase passed ...\n" << endl;
}

void test_shiftLeft()
{
	int highScores[5] = {12, 15, 76, 90, 100};
	string highScoreHolders[5] = {"Name1", "Name2", "Name3", "Name4", "Name5"};
	int location = 4;

	cout << "Unit Testing 10: Function - shiftLeft() \n";

	cout << "Case 1: Elements successfully shifted to the left\n";
	shiftLeft(highScores, highScoreHolders, location);
	int newHighScores[5] = {15, 76, 90, 100, 100};
	string newHighScoreHolders[5] = {"Name2", "Name3", "Name4", "Name5", "Name5"};
	for(int x = 0; x < MAX_NUMBER_OF_HIGH_SCORES; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}
	
	cout << "\nCase passed ...\n" << endl;
}

void test_appendScore()
{
	UserModel user;
	user.userName = "New Guy";
	int score = 75;
	int highScores[5] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
	string highScoreHolders[5] = {};
	int size = 0;

	cout << "Unit Testing 11: Function - appendScore() \n";

	cout << "Case 1: Add element to empty array \n";
	appendScore(score, user, highScores, highScoreHolders, size);
	int newHighScores[5] = {75, EMPTY, EMPTY, EMPTY, EMPTY};
	string newHighScoreHolders[5] = {"New Guy", "", "", "", ""};
	assert(size == 1);
	for(int x = 0; x < size; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}
	
	cout << "\nCase passed ...\n" << endl;

	highScores[0] = 12;
	highScores[1] = 15;
	highScores[2] = 25;
	highScores[3] = 76;
	highScores[4] = EMPTY;
	highScoreHolders[0] = "Name1";
	highScoreHolders[1] = "Name2";
	highScoreHolders[2] = "Name3";
	highScoreHolders[3] = "Name4";	
	highScoreHolders[4] = "";
	size = 4;	
	score = 13;
	cout << "Case 2: Add element to beginning of partially full array \n";
	appendScore(score, user, highScores, highScoreHolders, size);
	newHighScores[0] = 12;
	newHighScores[1] = 13;
	newHighScores[2] = 15;
	newHighScores[3] = 25;
	newHighScores[4] = 76;
	newHighScoreHolders[0] = "Name1";
	newHighScoreHolders[1] = "New Guy";
	newHighScoreHolders[2] = "Name2";
	newHighScoreHolders[3] = "Name3";
	newHighScoreHolders[4] = "Name4";	

	assert(size == 5);
	for(int x = 0; x < size; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}
	
	cout << "\nCase passed ...\n" << endl;
	
	highScores[0] = 12;
	highScores[1] = 15;
	highScores[2] = 25;
	highScores[3] = 76;
	highScores[4] = EMPTY;
	highScoreHolders[0] = "Name1";
	highScoreHolders[1] = "Name2";
	highScoreHolders[2] = "Name3";
	highScoreHolders[3] = "Name4";	
	highScoreHolders[4] = "";
	size = 4;	
	score = 20;
	cout << "Case 3: Add element to middle of partially full array \n";
	appendScore(score, user, highScores, highScoreHolders, size);
	newHighScores[0] = 12;
	newHighScores[1] = 15;
	newHighScores[2] = 20;
	newHighScores[3] = 25;
	newHighScores[4] = 76;
	newHighScoreHolders[0] = "Name1";
	newHighScoreHolders[1] = "Name2";
	newHighScoreHolders[2] = "New Guy";
	newHighScoreHolders[3] = "Name3";
	newHighScoreHolders[4] = "Name4";
	assert(size == 5);
	for(int x = 0; x < size; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}
	
	cout << "\nCase passed ...\n" << endl;

	highScores[0] = 12;
	highScores[1] = 15;
	highScores[2] = 25;
	highScores[3] = 76;
	highScores[4] = EMPTY;
	highScoreHolders[0] = "Name1";
	highScoreHolders[1] = "Name2";
	highScoreHolders[2] = "Name3";
	highScoreHolders[3] = "Name4";	
	highScoreHolders[4] = "";
	size = 4;	
	score = 90;
	cout << "Case 4: Add element to end of partially full array \n";
	appendScore(score, user, highScores, highScoreHolders, size);
	newHighScores[0] = 12;
	newHighScores[1] = 15;
	newHighScores[2] = 25;
	newHighScores[3] = 76;
	newHighScores[4] = 90;
	newHighScoreHolders[0] = "Name1";
	newHighScoreHolders[1] = "Name2";
	newHighScoreHolders[2] = "Name3";
	newHighScoreHolders[3] = "Name4";
	newHighScoreHolders[4] = "New Guy";
	assert(size == 5);
	for(int x = 0; x < size; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}
	
	cout << "\nCase passed ...\n" << endl;	

	highScores[0] = 12;
	highScores[1] = 15;
	highScores[2] = 25;
	highScores[3] = 76;
	highScores[4] = 90;
	highScoreHolders[0] = "Name1";
	highScoreHolders[1] = "Name2";
	highScoreHolders[2] = "Name3";
	highScoreHolders[3] = "Name4";	
	highScoreHolders[4] = "Name5";
	size = 5;	
	score = 13;
	cout << "Case 5: Add element to beginning of full array \n";
	appendScore(score, user, highScores, highScoreHolders, size);
	newHighScores[0] = 13;
	newHighScores[1] = 15;
	newHighScores[2] = 25;
	newHighScores[3] = 76;
	newHighScores[4] = 90;
	newHighScoreHolders[0] = "New Guy";
	newHighScoreHolders[1] = "Name2";
	newHighScoreHolders[2] = "Name3";
	newHighScoreHolders[3] = "Name4";
	newHighScoreHolders[4] = "Name5";
	assert(size == 5);
	for(int x = 0; x < size; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}

	cout << "\nCase passed ...\n" << endl;

	highScores[0] = 12;
	highScores[1] = 15;
	highScores[2] = 25;
	highScores[3] = 76;
	highScores[4] = 90;
	highScoreHolders[0] = "Name1";
	highScoreHolders[1] = "Name2";
	highScoreHolders[2] = "Name3";
	highScoreHolders[3] = "Name4";	
	highScoreHolders[4] = "Name5";
	size = 5;	
	score = 47;
	cout << "Case 6: Add element to middle of full array \n";
	appendScore(score, user, highScores, highScoreHolders, size);
	newHighScores[0] = 15;
	newHighScores[1] = 25;
	newHighScores[2] = 47;
	newHighScores[3] = 76;
	newHighScores[4] = 90;
	newHighScoreHolders[0] = "Name2";
	newHighScoreHolders[1] = "Name3";
	newHighScoreHolders[2] = "New Guy";
	newHighScoreHolders[3] = "Name4";
	newHighScoreHolders[4] = "Name5";
	assert(size == 5);
	for(int x = 0; x < size; x++)
	{
		assert(highScores[x] == newHighScores[x]);
		assert(highScoreHolders[x] == newHighScoreHolders[x]);
	}
	
	cout << "\nCase passed ...\n" << endl;
}

void test_writeHighScoresToFile()
{
	int highScores[5] = {12, 15, 25, 76, 97};
	string highScoreHolders[5] = {"Name1", "Name2", "Name3", "Name4", "Name5"};
	int size = 5;

	cout << "Unit Testing 12: Function - writeHighScoresToFile() \n";

	cout << "Case 1: Write to file successfully\n";
	writeHighScoresToFile(highScores, highScoreHolders, size);
	cout << "\nCase passed ...\n" << endl;
}

void test_readHighScoresFile()
{
	ifstream inStream;
	string filename = "test2.txt";
	int expectedHighScores[5] = {12, 15, 25, 76, 97};
	string expectedHighScoreHolders[5] = {"Name1", "Name2", "Name3", "Name4", "Name5"};
	int actualHighScores[5] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
	string actualHighScoreHolders[5] = {"", "", "", "", ""};
	stringstream ss;
	int size = 0;
	cout << "Unit Testing 13: Function Name - readHighScoresFile()" << endl;
	    
	cout << "Case 1: Read file successfully" << endl;		
	inStream.open((char*)filename.c_str());
	if(inStream.fail()){
		cout << "Input file opening failed." << endl;
		exit(1);
	}
	readHighScoresFile(actualHighScores, actualHighScoreHolders, inStream, ss, size);
	inStream.close();
	//cout << size << endl;
	assert(size == 5);
	for(int x = 0; x < size; x++)
	{
		assert(actualHighScores[x] == expectedHighScores[x]);
		assert(actualHighScoreHolders[x] == expectedHighScoreHolders[x]);
	}
	cout << "\nCase passed ...\n" << endl;
}

void test_actionPerformed()
{
	InGameUserDecisionFunctionPtr inGameUserDecisions[] = 
	{
		moveForward,
		readTechnicalPapers,
		searchForChange,
		viewCharacter,
		quitGame
	};
	int highScores[5] = {12, 15, 25, 76, 97};
	string highScoreHolders[5] = {"Name1", "Name2", "Name3", "Name4", "Name5"};
	PlayerModel player;
	int size = 5;
	int decisionType = IN_GAME;
	int decision = 2;
	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 5;
	cout << "Unit Testing 14: Function Name - actionPerformed()" << endl;
	    
	cout << "Case 1: Decision type is IN_GAME and initiates an in game action" << endl;
	
	bool performedAction = actionPerformed(decision, player, decisionType, highScores, highScoreHolders, inGameUserDecisions, size);
	assert(performedAction == true);

	cout << "\nCase passed ...\n" << endl;
	
	decisionType = MAIN_MENU;
	performedAction = false;
	decision = START_GAME;
	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 5;
	cout << "Case 2: Decision type is MAIN_MENU and initiates an in game action" << endl;

	performedAction = actionPerformed(decision, player, decisionType, highScores, highScoreHolders, inGameUserDecisions, size);
	assert(performedAction == true);
	assert(player.time > 0);
	assert(player.intelligence > 0);
	assert(player.distanceFromEnd > 0);
	assert(player.money > 0);	
	cout << "\nCase passed ...\n" << endl;	
}

void test_isGameOver()
{
	PlayerModel player;
	player.time = 5;
	player.money = 5;
	player.intelligence = 0;
	player.distanceFromEnd = 5;
	cout << "Unit Testing 15: Function - isGameOver() \n";

	cout << "Case 1: One of the player attributes is zero\n";
	bool gameIsOver = isGameOver(player);
	assert(gameIsOver == true);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 5;
	cout << "Case 2: None of the player attributes is zero\n";
	gameIsOver = isGameOver(player);
	assert(gameIsOver == false);
	cout << "\nCase passed ...\n" << endl;
}
void test_hasPlayerWon()
{
	PlayerModel player;
	player.time = 5;
	player.money = 5;
	player.intelligence = 0;
	player.distanceFromEnd = 5;
	cout << "Unit Testing 16: Function - hasPlayerWon() \n";

	cout << "Case 1: One of the player attributes (excluding distanceFromEnd) is zero\n";
	bool playerHasWon = hasPlayerWon(player);
	assert(playerHasWon == false);
	cout << "\nCase passed ...\n" << endl;

	player.time = 5;
	player.money = 5;
	player.intelligence = 5;
	player.distanceFromEnd = 0;
	cout << "Case 2: distanceFromEnd is zero and none of the other player attributes are zero\n";
	playerHasWon = hasPlayerWon(player);
	assert(playerHasWon == true);
	cout << "\nCase passed ...\n" << endl;

	player.time = 0;
	player.money = 0;
	player.intelligence = 0;
	player.distanceFromEnd = 0;
	cout << "Case 3: All player attributes are zero\n";
	playerHasWon = hasPlayerWon(player);
	assert(playerHasWon == false);
	cout << "\nCase passed ...\n" << endl;
}
