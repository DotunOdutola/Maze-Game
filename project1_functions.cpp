// Name: Adedotun Odutola
// User: aco0008
// Filename: project1_functions.cpp
// Sources: Worked in study group to understand the project as a whole.
// How To Compile: makefile

#include "project1_functions.h"

void displayName(string userName)
{
	cout << "\n===========================================================" << endl
	<< "\t\tWelcome " << userName << "!" << endl 
	<< "===========================================================" << endl << endl;
}

void promptUser()
{
	cout << "Enter your user name: ";	
}

void displayMenuOptions()
{
	cout << "1) Start a New Game of Dunstan and Dragons!" << endl
	     << "2) View top 10 High Scores!" << endl
	     << "3) Quit" << endl
	     << "Please choose an option: ";
}

bool validateAnswer(string userInput, PuzzlePtr puzzle)
{
	if(userInput == puzzle->answer)
		return true;
	else
		return false;
}

bool validateDecision(string userInput, int decisionType)
{
	bool isDecisionValid = false;
	if(userInput.length() > 1){
		isDecisionValid = false;	
	}
	else if(isdigit(userInput[0]))
	{
		int input = userInput[0] - '0'; // Convert char to int
		if(decisionType == IN_GAME && (input <= 5 && input >= 1))
		{
			isDecisionValid = true;
		}
		else if(decisionType == MAIN_MENU && (input <=3 && input >= 1))
		{
			isDecisionValid = true;
		}
		else
		{
			isDecisionValid = false;
		}
	} else {
		isDecisionValid = false;
	}

	if(isDecisionValid == false)
		cout << "\nInvalid decision. Please enter your option again." << endl << endl;
	
	return isDecisionValid;	
}

void changeAttribute(PlayerModel& player, PuzzlePtr puzzle, bool isCorrect)
{
	srand(time(NULL));
	int playerAttribute = (rand() % 3) + 1;	
	int deltaAttribute;	
	if(isCorrect == true){
		deltaAttribute = puzzle->deltaAttribute;
		cout << "\nYour answer is correct!" << endl << endl;
		cout << "You gained: ";
	} else {
		deltaAttribute = - puzzle->deltaAttribute;
		cout << "\nYour answer is wrong!" << endl << endl;
		cout << "You lost: ";
	}
	switch(playerAttribute)
	{
		case TIME:
			player.time+=deltaAttribute;
			cout << deltaAttribute << " time" << endl << endl;
			break;
		case MONEY:
			player.money+=deltaAttribute;
			cout << deltaAttribute << " money" << endl << endl;
			break;
		case INTELLIGENCE:
			player.intelligence+=deltaAttribute;
			cout << deltaAttribute << " intelligence" << endl << endl;
			break;
		default:
			cout << "Non-existent attribute specified." << endl << endl;
	}
}

void displayHighScores(int highScores[], string highScoreHolders[], int size)
{
	if(highScores[0] == EMPTY){
		cout << "\nNo high scores to be displayed." << endl << endl;
	} else {
		cout << "\nThe top " << size << " High Scores are: " << endl << endl;
		for(int x = size - 1; x >= 0; x--)
		{
			cout << highScoreHolders[x] << " " << highScores[x] << endl;
		}
		cout << endl;
	}
}

void handlePuzzle(PuzzlePtr puzzle, PlayerModel& player)
{
	cout << puzzle->question << endl;
	string userInput;
	getline(cin, userInput);
	bool isCorrect = validateAnswer(userInput, puzzle);
	changeAttribute(player, puzzle, isCorrect);		
}

PuzzlePtr generatePuzzle(PuzzlePtr head, int numberOfPuzzles, PlayerModel& player) 
{
	srand(time(NULL));
	int puzzleNumber = rand() % numberOfPuzzles + 1;
	PuzzlePtr current = head;

	while(puzzleNumber > 1)
	{
		current = current->next;
		puzzleNumber--;
	}
	handlePuzzle(current, player);
	return current;
}

void displayGameOptions(PlayerModel player)
{
	cout << "You are " << player.distanceFromEnd << " steps from the goal. Time left: " << player.time << endl << endl
	     << "1) Move forward(takes time, could be risky…)" << endl
	     << "2) Read technical papers (boost intelligence, takes time)" << endl
	     << "3) Search for loose change (boost money, takes time)" << endl
	     << "4) View Character" << endl
	     << "5) Quit the game" << endl << endl
	     << "Please choose an action: ";
}

void displayCharacter(PlayerModel player)
{
	cout << "\nYou have: " << endl << endl
	     << "Intelligence: " << player.intelligence << endl
	     << "Time: " << player.time << endl
	     << "Money: " << player.money << endl << endl;
}

void startGame(PlayerModel& player)
{
	srand(time(NULL));
	player.intelligence = (rand() % 21) + 10;
	player.time = (rand() % 21) + 10;
	player.money = (rand() % 21) + 10;
	player.distanceFromEnd = (rand() % 21) + 20;
	cout << "\nEntering the Dungeon..." << endl;
	displayCharacter(player);	
}

void viewHighScores(int highScores[], string highScoreHolders[], int size)
{
	displayHighScores(highScores, highScoreHolders, size);
}

void terminateProgram()
{
	cout << "\nTerminating Program..." << endl << endl;
	exit(1);
}

bool generateEncounter(PlayerModel& player, EncounterFunctionPtr encounters[], int encounterChances[], PuzzlePtr head)
{
	bool encounterGenerated = false;
	srand(time(NULL));
	int encounterChance = (rand() % 100) + 1;
	if(encounterChance <= PUZZLE_CHANCE)
	{
		encounterPuzzle(head, player);
		encounterGenerated = true;
		return encounterGenerated;
	} else {
		for(int x = 0; x < NUMBER_OF_ENCOUNTERS - 1; x++)
		{
			if(encounterChance <= encounterChances[x])
			{
				encounters[x](player);
				encounterGenerated = true;
				return encounterGenerated;
			}
		}
	}
	return encounterGenerated;
}

void quitGame(PlayerModel& player)
{
	player.time = 0;
	player.money = 0;
	player.intelligence = 0;
	player.distanceFromEnd = 0;
}

void moveForward(PlayerModel& player)
{
	player.distanceFromEnd--;	
}

void readTechnicalPapers(PlayerModel& player)
{
	srand(time(NULL));	
	int deltaTime = (rand() % 3) + 1;
	int deltaIntelligence = (rand() % 3) + 1;
	player.time -= deltaTime;
	player.intelligence += deltaIntelligence;
	cout << "\nYou read technical papers!" << endl << endl;
	cout << "You lost: -" << deltaTime << " time" << endl;
	cout << "You gained: " << deltaIntelligence << " intelligence" << endl << endl;
}

void searchForChange(PlayerModel& player)
{
	srand(time(NULL));	
	int deltaTime = (rand() % 5) + 1;
	int deltaMoney = (rand() % 5) + 1;
	player.time -= deltaTime;
	player.money += deltaMoney;
	cout << "\nYou searched for loose change!" << endl << endl;
	cout << "You lost: -" << deltaTime << " time" << endl;
	cout << "You gained: " << deltaMoney << " money" << endl << endl;
}

void viewCharacter(PlayerModel& player)
{
	displayCharacter(player);
}

void encounterPuzzle(PuzzlePtr head, PlayerModel& player)
{
	int numberOfPuzzles = 3;
	generatePuzzle(head, numberOfPuzzles, player);
}

void encounterProfessor(PlayerModel& player)
{
	srand(time(NULL));	
	int deltaTime = (rand() % 5) + 1;
	int deltaIntelligence = (rand() % 3) + 1;
	player.time -= deltaTime;
	player.intelligence += deltaIntelligence;
	cout << "\nA Professor saw you and explained The Special Theory of Relativity to you! " << endl << endl;
	cout << "You lost: -" << deltaTime << " time" << endl;
	cout << "You gained: " << deltaIntelligence << " intelligence" << endl << endl;
}

void encounterGraduateStudent(PlayerModel& player)
{
	srand(time(NULL));	
	int deltaTime = (rand() % 3) + 1;
	player.time -= deltaTime;
	cout << "\nA Graduate Student bumped into you and you dropped your books!" << endl << endl;
	cout << "You lost: -" << deltaTime << " time" << endl;
}

void encounterGruntWork(PlayerModel& player)
{
	srand(time(NULL));	
	int deltaTime = (rand() % 2) + 1;
	int deltaIntelligence = (rand() % 2) + 1;
	player.time -= deltaTime;
	player.intelligence -= deltaIntelligence;
	cout << "\nYou were caught slacking and forced to do Grunt Work!" << endl << endl;
	cout << "You lost: -" << deltaTime << " time" << endl;
	cout << "You lost: -" << deltaIntelligence << " intelligence" << endl << endl;
}

void encounterGradePapers(PlayerModel& player)
{
	srand(time(NULL));	
	int deltaTime = (rand() % 3) + 1;
	int deltaMoney = (rand() % 3) + 1;
	player.time -= deltaTime;
	player.money += deltaMoney;
	cout << "\nA professor hired you to Grade Papers!" << endl << endl;
	cout << "You lost: -" << deltaTime << " time" << endl;
	cout << "You gained: " << deltaMoney << " money" << endl << endl;
}

void encounterNothing(PlayerModel& player)
{
	cout << "\nNothing happens! You got lucky!" << endl << endl;
}

int calculateScore(PlayerModel player)
{
	return player.time * player.money * player.intelligence;
}

void appendScore(int score, UserModel user, int highScores[], string highScoreHolders[], int& size)
{
	if(highScores[0] == EMPTY) // Add to empty array
	{		
		highScores[0] = score;
		highScoreHolders[0] = user.userName;
		size++;
		return;
	}

	// Add to partially full 
	if(size < MAX_NUMBER_OF_HIGH_SCORES){

		for(int x = 0; x <= size; x++)
		{
			if(highScores[x] == EMPTY) // Add to array if the loop has reached an empty position
			{		
				highScores[x] = score;
				highScoreHolders[x] = user.userName;
				size++;
				return;
			}

			if(score <= highScores[x]) // Shift right from insertion point and then add score to array
			{
				shiftRight(highScores, highScoreHolders, x, size);
				highScores[x] = score;
				highScoreHolders[x] = user.userName;
				size++;
				return;
			}		
		}
	} else { // Add to full array

		if(score <= highScores[1]) // The new score replaces the current lowest score without shifting
		{
			highScores[0] = score;
			highScoreHolders[0] = user.userName;			
			return;
		}
		for(int x = 0; x < MAX_NUMBER_OF_HIGH_SCORES; x++)
		{
			if(score <= highScores[x]) // Shift left from insertion point and then add to array
			{
				shiftLeft(highScores, highScoreHolders, x - 1);
				highScores[x - 1] = score;
				highScoreHolders[x - 1] = user.userName;				
				return;
			}
		}
	}
	 
}

void shiftRight(int highScores[], string highScoreHolders[], int location, int size)
{
	for(int x = size - 1; x >= location; x--)
	{
		highScores[x + 1] = highScores[x];
		highScoreHolders[x + 1] = highScoreHolders[x];
	}
}

void shiftLeft(int highScores[], string highScoreHolders[], int location)
{
	for(int x = 0; x < location; x++)
	{
		highScores[x] = highScores[x + 1];
		highScoreHolders[x] = highScoreHolders[x + 1];
	}
}

void writeHighScoresToFile(int highScores[], string highScoreHolders[], int size)
{
	int index = size - 1;	
	string filename = "high_scores.txt";
	ofstream outStream;
	outStream.open(filename.c_str());
	if(outStream.fail()){
		cout << "Output file opening failed." << endl;
		exit(1);
	}
		
	while(index >= 0){		
		outStream << highScoreHolders[index] << " " << highScores[index] << endl;
		index--;
	}
}

int readHighScoresFile(int highScores[], string highScoreHolders[], ifstream& inStream, stringstream& ss, int& size)
{
	int index = 0;
	string line = "";
	int score = 0;
	string name = "";
	int temp1[5];
	string temp2[5];	
	while(getline(inStream, line))
	{	
		// clear the stringstream
		ss.str("");
		ss.clear();

		ss << line; // Puts the current line we are on in the stringstream
		ss >> name >> score;
		temp2[index] = name;
		temp1[index] = score; // Reads the username and score into their respective arrays
		index++;
		size++;
		if(size == 5)
		{
			inStream.ignore();
		}
	}
	int counter = size - 1;
	for(int x = 0; x < size; x++) //Scores are put in to increasing order instead of decreasing
	{
		
		highScores[counter] = temp1[x];
		highScoreHolders[counter] = temp2[x];
		counter--;
	}
	return index;
}

bool openFile(ifstream& inStream, string filename)
{
	inStream.open((char*)filename.c_str());
	if(inStream.fail()){
		return false;
	} else {
		return true;
	}
}

bool actionPerformed(int decision, PlayerModel& player, int& decisionType, 
			int highScores[], string highScoreHolders[], InGameUserDecisionFunctionPtr inGameUserDecisions[], int size)
{
	bool actionInitiated = false;
	if(decisionType == IN_GAME) 
	{
		inGameUserDecisions[decision - 1](player);	
		actionInitiated = true;
	} 
	else if(decisionType == MAIN_MENU)
	{
		switch(decision)
		{
			case START_GAME:
				startGame(player);
				decisionType = IN_GAME;
				actionInitiated = true;
				break;
			case VIEW_HIGH_SCORES: 
				viewHighScores(highScores, highScoreHolders, size);
				actionInitiated = true;
				break;
			case QUIT:
				terminateProgram();
				actionInitiated = true;
				break;
			default:
				cout << "Unknown Decision" << endl;
		}
	}
	return actionInitiated;
}

void createPuzzleQuestions(PuzzlePtr& head, PuzzlePtr& pretail, PuzzlePtr& tail)
{
	tail = new PuzzleModel; // Create first node in linked list and tail currently points to this node
	if(tail == NULL) { 
		cout << "Error: Insufficient memory.\n";
		exit(1);
	} 
	tail->question = "How long was the shortest war on record?(Hint: how many minutes)";
	tail->answer = "38";	
	tail->deltaAttribute = 2;
	head = tail; // head now points to the first node in the linked list
	pretail = tail; // pretail points to first node in linked list

	tail = new PuzzleModel; // Create second node node linked list and tail currently points to this node
	if(tail == NULL) { 
		cout << "Error: Insufficient memory.\n";
		exit(1);
	}
	pretail->next = tail; // Makes the first node point to the second node in the linked list
	tail->question = "What was Bank of America's original name?(Hint: Bank of Italy or Bank of Germany)";
	tail->answer = "Bank of Italy";	
	tail->deltaAttribute = 2;
	pretail = tail; // pretail points to second node in linked list

	tail = new PuzzleModel; // Create third node for linked list and tail currently points to this node
	if(tail == NULL) { 
		cout << "Error: Insufficient memory.\n";
		exit(1);
	}
	pretail->next = tail; // Makes the second node point to the third node in the linked list
	tail->question = "What is the best-selling video game of all time?(Hint: Call of Duty or Wii Sports)";
	tail->answer = "Wii Sports";
	tail->deltaAttribute = 2;	
	tail->next = NULL; // Marks the end of the linked list	
}

bool isGameOver(PlayerModel player)
{
	if(player.time <=  0 || player.money <= 0 || player.intelligence <= 0 || player.distanceFromEnd <= 0)
		return true;
	else
		return false;
}

bool hasPlayerWon(PlayerModel player)
{
	if(player.time <= 0 || player.money <= 0 || player.intelligence <= 0)
		return false;
	else
		return true;
}

