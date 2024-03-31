/*  CCDSTRU MP SOURCE CODE

    Do not forget to encode your name, section and date of submission.
    
    LASTNAME1, FIRSTNAME1:    GALAN, RUSSELL EMMANUEL	    SECTION1: S11
    LASTNAME2, FIRSTNAME2:    MANGUBAT, MARVIN IVAN			SECTION2: S11
    
    DATE SUBMITTED:	March 31, 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define boardVAL 6 //constant for 6x6 board
#define GREEN "\e[1;92m"
#define PURPLE "\e[1;95m"
#define RED "\e[1;91m"
#define RESET "\033[0m"

void playTuneWin(){
	Beep(523, 500);
	Sleep (15);
	Beep(659, 500);
	Sleep (15);
	Beep(784, 500);
	Sleep (15);
	Beep(659, 500);
	Sleep (15);
	Beep(523, 500);
	Sleep (15);
	Beep(659, 500);
	Sleep (15);
	Beep(784, 500);
	Sleep (15);
}

void playTuneLose(){
	Beep((int)261.63, 500);
	Sleep (15);
	Beep((int)392.00, 500);
	Sleep (15);	
	Beep((int)329.63, 500);
	Sleep (15);
	Beep((int)293.66, 500);
	Sleep (15);
	Beep((int)261.63, 750);
	Sleep (15);
}           

void displayBOARD (char board[][6]){ //displays the board and updates if there is a valid input
    int i, j;
	printf( "                                                  1   2   3   4   5   6\n");
	// printf(RESET);                       
	printf("                                                -------------------------\n");
    for (i = 0; i < boardVAL; i++){
		printf("                                              %d ", i + 1);
        for (j = 0; j < boardVAL; j++){
            if (j == 0){
            	if (board[i][j] == 'X'){
            		printf("|");
            		printf(GREEN " %c ", board[i][j]);
            		printf(RESET); //reset color for other prints
            		printf("|");
				}
            		
            	else if (board[i][j] == 'O'){
            		printf("|");
            		printf(PURPLE " %c ", board[i][j]);
            		printf(RESET);
            		printf("|");
				}
            		
            	else
            		printf("| %c |", board[i][j]);
			}	
			else{
				if (board[i][j] == 'X'){;
					printf(GREEN " %c ", board[i][j]);
					printf(RESET);
					printf("|");
				}	
            	else if (board[i][j] == 'O'){
					printf(PURPLE " %c ", board[i][j]);
            		printf(RESET);
            		printf("|");
				}	
            	else
            		printf(" %c |", board[i][j]);
			}   
        }                                      
		printf("\n                                                -------------------------\n");
    }   
	
}

int possibleMoves (char Board[][6]){ //checks if there are possible moves/spaces that aren't filled
	int ctrmoves = 0;
	int i, j;
	
	for (i = 0; i < boardVAL; i++){
		for (j = 0; j < boardVAL; j++){
			if (Board[i][j] == ' ')
			ctrmoves++;
		}
	}
	
	return ctrmoves;
}

void NextPlayerMove (int *next, char board[][6], int* prevMoveRow, int* prevMoveCol){ //gets inputs from player 1 and player 2
	int playera, playerb;
	
	switch (*next){
		case 1: scanf("%d %d", &playera, &playerb);
			*prevMoveRow = playera;
			*prevMoveCol = playerb;
		while (playera < 1 || playerb > 6 || board[playera - 1][playerb - 1] != ' '){
		printf(RED "                                         \tInvalid input! Try Again: ");
		scanf("%d %d", &playera, &playerb);
			*prevMoveRow = playera;
			*prevMoveCol = playerb;
		}
		board[playera - 1][playerb - 1] = 'X';
		*next += 1;
		printf("\n");
		break;
		
		case 2: scanf("%d %d", &playera, &playerb);
			*prevMoveRow = playera;
			*prevMoveCol = playerb;
		while (playera < 1 || playerb > 6 || board[playera - 1][playerb - 1] != ' '){
		printf(RED "                                         \tInvalid input! Try Again: ");
		scanf("%d %d", &playera, &playerb);
			*prevMoveRow = playera;
			*prevMoveCol = playerb;
		}
		board[playera - 1][playerb - 1] = 'O';
		*next = 1;
		printf("\n");
		break;
	}	
	
}

int checkPattern(int next, char board[][6]) { //checks if player 1 or player 2 's if they meet the winning conditions
	int result, combo[4] = {0};
	char piece;
	
	if (next == 1)
	piece = 'X';
	if (next == 2)
	piece = 'O';
	
	// the indexes are subtracted by 1 since the board starts at [0][0] and was seen based from the specs
	if (board[0][0] == piece && board[0][2] == piece && board[1][1] == piece && board[2][0] == piece && board[2][2] == piece)
	combo[0] = 1;
	if (board[3][3] == piece && board[3][5] == piece && board[4][4] == piece && board[5][3] == piece && board[5][5] == piece)
	combo[1] = 1;
	if (board[0][4] == piece && board[1][3] == piece && board[1][4] == piece && board[1][5] == piece && board[2][4] == piece)
	combo[2] = 1;
	if (board[3][0] == piece && board[3][2] == piece && board[4][0] == piece && board[4][2] == piece && board[5][0] == piece 
		&& board[5][2] == piece)
	combo[3] = 1;
	
	if (combo[0] == 1 && combo[1] == 1)
	result = 1;
	else if (combo[2] == 1 && combo[3] == 1)
	result = 1;
	else
	result = 0;
	
	return result;
}


int GameOver (char board[][6]){ //decides when to end the game whether player 1 or 2 wins or tie
	int gamestate;
	int moves = possibleMoves(board);
	
	if (moves == 0){
		gamestate = 1; 
		printf("\n\n");
		displayBOARD(board);
		printf(RED "\n\n\t                                   No more possible moves! No one won!");
		printf(RESET);
		playTuneLose();
	}
		
	else if (checkPattern(1, board) == 1){
		gamestate = 1;
		printf("\n\n");
		displayBOARD(board);
		printf(GREEN "\n\n\t                                       \t      Player 1 Won!");
		printf(RESET);
		playTuneWin();
	}
		
	else if (checkPattern(2, board) == 1){
		gamestate = 1;
		printf("\n\n");
		displayBOARD(board);
		printf(PURPLE "\n\n\t                                       \t      Player 2 Won!");
		printf(RESET);
		playTuneWin();
	}
		
	else
		gamestate = 0;
		
	return gamestate;
}

void MainMenu(){
	printf("\n");
	system("COLOR F5");
	printf("          ==========================================================================================================\n\n");
	printf("                                                 CCDSTRU MP - S11 Group 1\n");
	printf("                                       by: RUSSELL GALAN ^ MARVIN IVAN C. MANGUBAT\n\n");
		printf("                                         \t -----------------------\n");
		printf("                                         \t|                       |\n");
		printf("                                         \t|   4x TIC->TAC->TOE    |\n");
		printf("                                         \t|                       |\n");
		printf("                                         \t| [1] Start a New Game  |\n");
		printf("                                         \t| [2] Instructions      |\n");
		printf("                                         \t| [3] Quit Game         |\n");
		printf("                                         \t|                       |\n");
		printf("                                          \t -----------------------\n");
	
	printf("\n                                               Welcome to 4x TIC->TAC->TOE!\n");
	printf("                                Similar to the normal Tic-Tac-Toe, however, there are 4 grids!\n");
	printf("              To win, you need to complete two opposite grids before your opponent or before running out of tiles!\n\n");
	printf("          ==========================================================================================================\n\n");
} 
	
void ClosingScreen(){
	system("cls");
	system("COLOR F5");
	printf("          ==========================================================================================================\n\n");
	printf("                                                 CCDSTRU MP - S11 Group 1\n");
	printf("                                       by: RUSSELL GALAN ^ MARVIN IVAN C. MANGUBAT\n\n");
	printf("                                         \t -----------------------\n");
	printf("                                         \t|                       |\n");
	printf("                                         \t|   4x TIC->TAC->TOE    |\n");
	printf("                                         \t|                       |\n");
	printf("                                         \t|      Thanks for       |\n");
	printf("                                         \t|       playing!        |\n");
	printf("                                         \t|                       |\n");
	printf("                                         \t|                       |\n");
	printf("                                          \t -----------------------\n\n");
	printf("          ==========================================================================================================\n\n");
}

void InstructionsScreen(){
	system("cls");
	system("COLOR F5");
	printf("          ==========================================================================================================\n\n");
	printf("          1. In each round, the current player will choose a tile from the board to put their mark in.\n\n");
	printf("          2. This will repeat until one of the players completes the correct pattern on opposite sides of the board.\n\n");
	printf("          3. If the players wish to play again, they will be redirected to the main menu. Otherwise, they will be \n");
	printf("             redirected to the closing screen.\n\n");
	printf("          ==========================================================================================================\n\n");
}

int main (){
	
	int nMenuSelection = 0;
	int nGoBack = 0;
	int nPlayAgain = 0;
	
	int prevMoveRow = 0;
	int prevMoveCol = 0;
	
	while (nPlayAgain != 2) {
        while (nMenuSelection != 1) {
            nMenuSelection = nGoBack = 0;
            system("cls");
            MainMenu();
			printf("\n                        Please enter [1] to begin, [2] for the instructions, or [3] to quit the game: ");
			scanf("%d", &nMenuSelection);
	
	while (nMenuSelection < 1 || nMenuSelection > 3){ // Ensures the user input is correct.
		printf(RED "                   Invalid input. Please enter [1] to begin, [2] for the instructions, or [3] to quit the game: ");
		scanf("%d", &nMenuSelection);
	}
	
	if (nMenuSelection == 3){
		ClosingScreen();
		return 0;
	}
	
	if (nMenuSelection == 2){
		InstructionsScreen();
		printf("          Enter [1] to go back to the main menu: ");
		scanf("%d", &nGoBack);
		while (nGoBack < 1 || nGoBack > 1){ // Ensures the user input is correct.
			printf(RED "          Invalid input. Please enter [1] to go back to the main menu: ");
			scanf("%d", &nGoBack);
		}
	}
	}
	
	if (nMenuSelection == 1){
		system("cls");
			system("COLOR 0F");
			printf("\n");
			printf(RED "                                                ====== GAME START! ======\n\n");
			printf(RESET);
		    char Board [6][6] = {{' ', ' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' ', ' '}};
			int next = 1;
			int over = 0;
			

			while (!over){
			printf("\n\n");
			printf("                                           Player 1:"); 
			printf(GREEN " 'X'");
			printf(RESET);
			printf(" ======= Player 2: ");
			printf(PURPLE "'O'\n\n");
			printf(RESET);
			displayBOARD(Board);
			printf("\n");
			printf(RED "                                           Previous move was: %d %d\n", prevMoveRow, prevMoveCol);
			printf(RESET);
			printf("                                           Its Player %d's turn:\n", next);
			printf("                                           Enter inputs (ex: [row] [column]): ");
			NextPlayerMove (&next, Board, &prevMoveRow, &prevMoveCol);	
			system ("cls");
			
			over = GameOver(Board);
			}
	}
	
			printf("\n\n                              Enter [1] if you want to play again or [2] if you want to exit: ");
			scanf("%d", &nPlayAgain);
				while (nPlayAgain < 1 || nPlayAgain > 2){ // Ensures the user input is correct.
					printf(RED "            Invalid input. Please enter [1] to go back to the main menu or [2] if you want to exit: ");
					scanf("%d", &nPlayAgain);
				}
				if (nPlayAgain == 2){
					ClosingScreen();
					return 0;
				}
	}
	return 0;
}
	
	
	
	
