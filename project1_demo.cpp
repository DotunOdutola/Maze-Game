// Name: Adedotun Odutola
// User: aco0008
// Filename: project1_demo.cpp
// Sources: Worked in study group to understand the project as a whole.
// How To Compile: Mac Terminal

#include "project1_functions.h"

int main()
{

	EncounterFunctionPtr encounters[] = 
	{ // Array of function pointers
		encounterProfessor,
		encounterGraduateStudent,
		encounterGruntWork,
		encounterGradePapers,
		encounterNothing
	};
	InGameUserDecisionFunctionPtr inGameUserDecisions[] = 
	{ // Array of function pointers
		moveForward,
		readTechnicalPapers,
		searchForChange,
		viewCharacter,
		quitGame
	};
	int encounterChances[] = {PROFESSOR_CHANCE, GRADUATE_STUDENT_CHANCE, GRUNT_WORK_CHANCE, GRADE_PAPERS_CHANCE, NOTHING_CHANCE};
	int highScores[5] = {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY};
	string highScoreHolders[5] = {"", "", "", "", ""};
	PlayerModel player;
	UserModel user;
	ifstream inStream;
	stringstream ss;
	string filename = "high_scores.txt";
	bool isFileOpened = false;	
	int size = 0;
	PuzzlePtr head, pretail, tail;

	createPuzzleQuestions(head, pretail, tail);
	isFileOpened = openFile(inStream, filename); // Open high_scores.txt if it exists
	if(isFileOpened == true)
		readHighScoresFile(highScores, highScoreHolders, inStream, ss, size);

	inStream.close();
	promptUser();
	getline(cin,user.userName);
	string userName = user.userName;
	displayName(userName);
	int decisionType = MAIN_MENU;
	while(true)
	{
		decisionType = MAIN_MENU;
		string userInput, space;
		int decision;
		bool isDecisionValid;
		bool gameIsOver = false;
		do{ // Take user input in main menu and perform the corresponding action
			cout << "Press ENTER to continue..." << endl;
			getline(cin, space);
			isDecisionValid = false;		

			while(isDecisionValid == false){ // Keep prompting user until they enter a valid decision
				displayMenuOptions();
				getline(cin, userInput);
				isDecisionValid = validateDecision(userInput, decisionType);
			}
			decision = atoi(userInput.c_str()); // convert string to int
			
			// Perform the action specified by decision
			actionPerformed(decision, player, decisionType, highScores, highScoreHolders, inGameUserDecisions, size);
		} while(decision != START_GAME);
		
		do{ // Take user input in the in-game menu and perform the corresponding actions
			cout << "Press ENTER to continue..." << endl;
			getline(cin, space);
			isDecisionValid = false;		
			
			while(isDecisionValid == false){ // Keep prompting user until they enter a valid decision				
				displayGameOptions(player);
				getline(cin, userInput);
				isDecisionValid = validateDecision(userInput, decisionType);
			}
			decision = atoi(userInput.c_str()); // convert string to int

			// Perform the action specified by decision
			actionPerformed(decision, player, decisionType, highScores, highScoreHolders, inGameUserDecisions, size);		
			if(decision == MOVE_FORWARD)
				generateEncounter(player, encounters, encounterChances, head);

			gameIsOver = isGameOver(player); // Check if game is over
			if(gameIsOver == true)
			{
				cout << "\nGame Over!" << endl;
				if(hasPlayerWon(player) == true) // Check if player has won
				{
					int score = calculateScore(player);
					cout << "Congragulations! You win!" << endl << "Your score: " << score << endl;
					if(score > highScores[0]) // Check if player's score is top 5 worthy
					{ // Add score and name to their respective arrays and write arrays to file
						appendScore(score, user, highScores, highScoreHolders, size);
						writeHighScoresToFile(highScores, highScoreHolders, size);
						cout << "Your score is now in the top 5." << endl;
					}
				} else {
					cout << "You lose!" << endl;
				} 
				cout << "Thanks for playing! Going back to the main menu..." << endl << endl;
			}
			
		} while(decision != QUIT_GAME && gameIsOver != true);		
	}
	return 0;
}
