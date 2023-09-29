#include <iostream>
#include <cstring>
#include <array>
using namespace std;

/*
 * Author | Sophia You
 * Date | 10/03/2023
 * Description | A two player tic tac toe game played through the
 * command line. Each user puts in the move they want to make
 * (ex/ A1 is the top left square, all the way down to C3)
 * and after each player's move, the computer reprints the updated
 * board. At the end of the game, the computer announces who won
 * or if there was a tie.
 *
 * Sources |
 * https://cplusplus.com/doc/oldtutorial/typecasting/
 * + my previous project tictactoe from Java Programming
 *
 */

void printBoard(int board[][3], int rowlength, int columnlength);
void clearBoard(int board[][3], int rowlength, int columnlength);
bool checkWin(int board[][3], int player);
bool checkTie(int board[][3], int rowlength, int columnlength);

// denotes whether the board is filled with an x, an o, or blank
const int BLANK = 0;
const int X_MOVE = 1;
const int O_MOVE = 2;

// denotes which player is moving
const bool X_TURN = true;
const bool O_TURN = false;

int main()
{
  int row = 3;
  int column = 3;
  int board[row][3];
  
  int move = X_MOVE;
  bool turn = X_TURN; // determines whose turn it is
  int max = 11;
  char input[max]; // stores input from command line

  // tracks the score
  int xWins = 0;
  int oWins = 0;
  int numTies = 0;

  bool playing = true; // if this is false, the game will stop

  while (playing)
    {
      clearBoard(board, row, column);
      printBoard(board, row, column);
      turn = X_TURN; // x always starts first
      move = X_MOVE;

      // the game keeps running while the user is playing
      while (!checkWin(board, X_MOVE) &&
	     !checkWin(board, O_MOVE) &&
	     !checkTie(board, row, column))
	{
	  if (turn == X_TURN)
	    {
	      cout << "It's Player X's turn." << endl;
	    }
	  else if (turn == O_TURN)
	    {
	      cout << "It's Player O's turn." << endl;
	    }

	  // input from command line
	  cout << "Please enter the location of your move (ex/ A1 is the top left)" << endl;
	  cout << "Use lowercase letters only (ex/ a1 for A1)." << endl;
	  cin.getline(input, max);

	  // the input must be 2 characters long, with the first being a, b or c and the second being 1, 2, or 3
	  bool validMove = false;
	  int inputRow = -1;
	  int inputColumn = -1;

	  while (validMove == false)
	    {
	      if (strlen(input) == 2
		  && (input[1] >= '1' && input[1] <= '3'))
		{
		  if (input[0] >= 'a' && input[0] <= 'c')
		    {
		      inputRow = input[0] - 'a'; // the row "A" is actually board[0][] in the code, so you must subtract
		      inputColumn = input[1] - '1'; // the column '1' is actually board[][0] in the code
		      if (board[inputRow][inputColumn] == BLANK) // make sure the move spot is empty before moving!
			{
			  validMove = true;
			}
		      else // the move isn't legal
			{
			  cout << "That slot is already taken. Please pick another move." << endl;
			  cin.getline(input, max);
			}
		    }
		  else
		    {
		      cout << "Please only enter lowercase letters!" << endl;
		      cin.getline(input, max);
		    }
		}
	      else // if the move isn't valid you have to enter another move
		{
		  cout << "Please enter a valid move." << endl;
		  cin.getline(input, max);
		}
	    }


	  // translate the move from the command line to coordinates on the board
	  board[inputRow][inputColumn] = move;
	  printBoard(board, row, column);

	  turn = !turn; // the next player gets to move
	    if (turn == X_TURN)
	    {
	      move = X_MOVE;
	    }
	  else if (turn == O_TURN)
	    {
	      move = O_MOVE;
	    }

	    // print who won
	    if (checkWin(board, X_MOVE))
	      {
		xWins++;
		cout << "X wins this round!" << endl;
	      }
	    else if (checkWin(board, O_MOVE))
	      {
		oWins++;
		cout << "O wins this round!" << endl;
	      }
	    else if (checkTie(board, row, column))
	      {
		numTies++;
		cout << "It's a tie!" << endl;
	      }
	}

      // print the scores
       cout << "X Score: " << xWins << endl;
       cout << "O Score: " << oWins << endl;
       cout << "Number of Ties: " << numTies << endl;

      // ask the user if they want to play again
      // credit to myself, C++ guessing game assignment
      cout << "Play again? Press 1 to continue, press 0 to quit." << endl;
      char inputPlay = ' ';
      cin >> inputPlay;
      if (inputPlay == '0')
	{
	  playing = false;
	}

    }
  
  cout << "Game over." << endl;
  return 0;
}

    // prints board out to the command line
    void printBoard(int board[][3], int rowlength, int columnlength)
    {
      cout << "\t1\t2\t3" << endl; // number headers

      for (int row = 0; row < rowlength; row++)
	{
	  cout << (char)('A' + row);
	  for (int column = 0; column < columnlength; column++)
	    {
	      if (board[row][column] == X_MOVE)
		{
		  cout << "\tX";
		}
	      else if (board[row][column] == O_MOVE)
		{
		  cout << "\tO";
		}
	      else if (board[row][column] == BLANK)
		{
		  cout << "\t";
		}

	    }
	  cout << endl;
    }

}

// clears the command line board and the move tracker
void clearBoard(int board[][3], int rowlength, int columnlength)
{
  for (int row = 0; row < rowlength; row++)
    {
      for (int column = 0; column < columnlength; column++)
        {
          board[row][column] = BLANK;
        }
    }
}

// checks the board to determine if a player has won
// credit to myself, ticTacToe java, circa October 2022 for this function
bool checkWin(int board[][3], int player)
{
  // Row wins
  // Top row
    if (board[0][0] == player &&
	    board[0][1] == player &&
	    board[0][2] == player)
    {
      return true;
    }

    // Middle row
    else if (board[1][0] == player &&
		    board[1][1] == player &&
	     board[1][2] == player)
    {
      return true;
    }

    // Bottom row
    else if (board[2][0] == player &&
		    board[2][1] == player &&
		    board[2][2] == player)
    {
      return true;
    }

    // Diagonal wins

    // Left to right diagonal
    else if (board[0][0] == player &&
		    board[1][1] == player &&
		    board[2][2] == player)
    {
      return true;
    }

    // Right to left diagonal
    else if (board[0][2] == player &&
		    board[1][1] == player &&
		    board[2][0] == player)
    {
      return true;
    }

    // Column wins

    // Left column
    else if (board[0][0] == player &&
		    board[1][0] == player &&
		    board[2][0] == player)
    {
      return true;
    }

    // Middle column
    else if (board[0][1] == player &&
		    board[1][1] == player &&
		    board[2][1] == player)
    {
      return true;
    }

    // Right column
    else if (board[0][2] == player &&
		    board[1][2] == player &&
		    board[2][2] == player)
    {
      return true;
    }

    return false;
}

// checks to see if all squares are filled - that means there's a tie
bool checkTie(int board[][3], int rowlength, int columnlength)
{
  for (int row = 0; row < rowlength; row++) // walks through every square on the board
    {
      for (int column = 0; column < columnlength; column++)
	{
	  if (board[row][column] == BLANK) // checks if it is filled
	    {
	      return false;
	    }
	}
    }
  return true;
}
