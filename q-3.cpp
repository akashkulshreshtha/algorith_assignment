/*
	Submitted by : Akash kulshreshtha
	Roll no		 : 03
	Subject		 : Design and Analysis of Algorithm
	Assignment   : 3, Section A
	Question no. : 3 - Implement N queen's problem using back tracking.
*/

#include "pch.h"
#include <iostream>

using namespace std;

struct Square 
{
	bool 
		hasQueen;

	Square() 
	{
		hasQueen = false;
	}
};

void PrintChessBoard(Square** board, int n) 
{
	for (int row = 0; row < n; row++) 
	{
		for (int column = 0; column < n; column++) 
		{
			if (board[row][column].hasQueen) 
			{
				cout << "Q";
			}
			else 
			{
				cout << ".";
			}
		}
		cout << "\n";
	}
}

bool IsSafeToPutQueen(int row, int column, Square** board, int n) 
{
	int columnLeft = column - 1;
	int rowBelow = row + 1;
	int rowAbove = row - 1;

	while ((columnLeft >= 0) or (rowBelow < n) or (rowAbove >= 0)) 
	{
		bool leftUpperDiagonalAttack = (rowAbove >= 0) && (columnLeft >= 0) && board[rowAbove][columnLeft].hasQueen;

		bool leftLowerDiagonalAttack = (rowBelow < n) && (columnLeft >= 0) && board[rowBelow][columnLeft].hasQueen;

		bool leftAttack = (columnLeft >= 0) && board[row][columnLeft].hasQueen;

		if (leftUpperDiagonalAttack or leftLowerDiagonalAttack or leftAttack) 
		{
			return false;
		}
		else 
		{
			columnLeft--;
			rowAbove--;
			rowBelow++;
		}
	}
	return true;
}

bool CanSolveWithBackTrack(Square** board, int n) 
{
	bool inBacktrack = false;
	int column = 0;
	while (column < n) 
	{
		bool wasQueenPlaced = false;
		for (int row = 0; row < n; row++) 
		{
			if (IsSafeToPutQueen(row, column, board, n)) 
			{
				if (inBacktrack) 
				{
					if (board[row][column].hasQueen) 
					{
						board[row][column].hasQueen = false;
						inBacktrack = false;
						continue;
					}
				}
				else 
				{
					board[row][column].hasQueen = true;
					wasQueenPlaced = true;
					break;
				}
			}
		}

		if ((!wasQueenPlaced) && (!board[n - 1][column].hasQueen))
		{
			column--;
			if (column < 0) 
			{
				return false;
			}
			inBacktrack = true;
		}
		else 
		{
			column++;
		}
	}
	return true;
}

int main(int argc, char* argv[]) 
{
	int n = 0;
	cout << "Enter the value of N" << "\n";
	cin >> n;

	Square** board = new Square*[n];
	for (int i = 0; i < n; i++) 
	{
		board[i] = new Square[n];
	}

	if (CanSolveWithBackTrack(board, n)) 
	{
		cout << "This combination CAN place the queens!" << "\n";
		PrintChessBoard(board, n);
	}
	else 
	{
		cout << "This combination CAN'T place the queens." << "\n";
	}

	for (int i = 0; i < n; i++) 
	{
		delete[] board[i];
	}
	delete[] board;

	return 0;
}
