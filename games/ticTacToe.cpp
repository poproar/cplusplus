//	Author:		Andrew T. Pilcher 0623706
//	Program:	CS12 - 33853 Extra Credit 1
//	Date:		February 13th, 2011
//	Descri:		Exercise 9, from pages 715-716, from chapter 12

#include <iostream>

using namespace std;

//*****************************************************************************************************
// CLASS - Tic Tac Toe
//*****************************************************************************************************

class ticTacToe
{
private:
	char board[3][3];
	int player;
	char marker;

public:
	void displayBoard();					//prints board
	void getMove();							//pick play
	bool validateMv(char select);			//check board
	void playMove();						//registers move
	bool gameOver();						//end game
	void endGame();							//end play

	ticTacToe();							//constructor (initialization?)

};

int main()
{
	ticTacToe game;
	char again;


	do{
	system("cls");
	game.playMove();
	game.displayBoard();
	game.getMove();
	if (game.gameOver())
	{
		game.endGame();
	}
	}while(!game.gameOver());

	return 0;
}

//*****************************************************************************************************
// FUNCTIONS of ticTacToe CLASS also defined as the Implementation File
//*****************************************************************************************************
void ticTacToe::displayBoard()
{

							
						 cout << "\n\t\t\t   |   |   "							<< endl
		<< "\t\t\t " << board[0][0]	<< " | "				<< board[0][1] << " | " << board[0][2] << " " << endl
								<< "\t\t\t   |   |   "								<< endl
								<< "\t\t\t===|===|==="								<< endl
								<< "\t\t\t   |   |   "								<< endl
		<< "\t\t\t " << board[1][0] << " | "				<< board[1][1] << " | " << board[1][2] << " " << endl
								<< "\t\t\t   |   |   "								<< endl
								<< "\t\t\t===|===|==="								<< endl
								<< "\t\t\t   |   |   "								<< endl
		<< "\t\t\t " << board[2][0] << " | "				<< board[2][1] << " | " << board[2][2] << " " << endl
								<< "\t\t\t   |   |   "								<< endl << endl;
}
void ticTacToe::getMove()
{
	char select;

		//set mark: X for player 1 ; O for player 2
		if (player == 1) {
			marker = 'X';
		} else {
			marker = 'O';
		}
		//prompt player
		cout << "Player " << player << " select move:" ;
		
		do{
			cin >> select;
		}
		while (!validateMv(select));


}
bool ticTacToe::validateMv(char select)
{
	 	if		  (select == '1' && board[0][0] == '1') {
			board[0][0] = marker;
			return true;
		} else if (select == '2' && board[1][0] == '2') {
			board[1][0] = marker;
			return true;
		} else if (select == '3' && board[2][0] == '3') {
			board[2][0] = marker;
			return true;
		} else if (select == '4' && board[0][1] == '4') {
			board[0][1] = marker;
			return true;
		} else if (select == '5' && board[1][1] == '5') {
			board[1][1] = marker;
			return true;
		} else if (select == '6' && board[2][1] == '6') {
			board[2][1] = marker;
			return true;
		} else if (select == '7' && board[0][2] == '7') {
			board[0][2] = marker;
			return true;
		} else if (select == '8' && board[1][2] == '8') {
			board[1][2] = marker;
			return true;
		} else if (select == '9' && board[2][2] == '9') {
			board[2][2] = marker;
			return true;
		} else {
			cout << "Invalid Move. Try again." << endl;
			return false;
		}
	
}
void ticTacToe::playMove()
{
	if (player == 1) 
	{
		player = 2;
	} else {
		player = 1;
	}
}
bool ticTacToe::gameOver()
{
	
		if (((board[0][0] == board[1][0]) && (board[1][0] == board[2][0])) || 
			((board[0][1] == board[1][1]) && (board[1][1] == board[2][1])) || 
			((board[0][2] == board[1][2]) && (board[1][2] == board[2][2])) ||
			((board[0][0] == board[0][1]) && (board[0][1] == board[0][2])) ||
			((board[1][0] == board[1][1]) && (board[1][1] == board[1][2])) ||
			((board[2][0] == board[2][1]) && (board[2][1] == board[2][2])) ||
			((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) ||
			((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))) 
		{
			cout << "Player " << player << " wins!" << endl;
			return true;
		}
		
		else if (board[0][0] != '1' &&
				board[1][0] != '2' &&
				board[2][0] != '3' &&
				board[0][1] != '4' &&
				board[1][1] != '5' &&
				board[2][1] != '6' &&
				board[0][2] != '7' &&
				board[1][2] != '8' &&
				board[2][2] != '9' )
		{
			return true;
		}

		else
		{
			return false;
		}
}
void ticTacToe::endGame()
{
	char again = 'y';

	cout << "Again ? (y/n): ";
	cin >> again;
	
	if (again == 'Y' || again == 'y') //then reset
	{
		board[0][0] = '1';
		board[1][0] = '2';
		board[2][0] = '3';
		board[0][1] = '4';
		board[1][1] = '5';
		board[2][1] = '6';
		board[0][2] = '7';
		board[1][2] = '8';
		board[2][2] = '9';

		player = 2;
		gameOver();
	}
	
		
}
ticTacToe::ticTacToe()
{
	board[0][0] = '1';
	board[1][0] = '2';
	board[2][0] = '3';
	board[0][1] = '4';
	board[1][1] = '5';
	board[2][1] = '6';
	board[0][2] = '7';
	board[1][2] = '8';
	board[2][2] = '9';

	player = 2;

}
