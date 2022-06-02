#pragma once
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>


void move(int board[8][8], int initial_x, int initial_y, int final_x, int final_y)
{
	int temp, x_for_taking, y_for_taking;
	temp = board[initial_y][initial_x]; // preserves the state of the selected tile
	board[initial_y][initial_x] = board[final_y][final_x]; // copies the state of the destination tile to the selected tile (which makes no sense)
	board[final_y][final_x] = temp; // copies the state of the selected tile to the destination tile
	if (abs(initial_y - final_y) != 1) // if a piece moved by more than one square (ergo a piece was taken)
	{
		x_for_taking = (final_x > initial_x) ? 1 : -1;
		y_for_taking = (final_y > initial_y) ? 1 : -1;
		board[initial_y + y_for_taking][initial_x + x_for_taking] = 0; // sets the square that contained the piece that was taken as 'empty'
	}
}



void possible_moves_queen_red(int board[8][8], int possible_moves[4][2], int pos_x, int pos_y, int take_flag = 0)
{
	// flag that forces the piece to take if able
	int size = 0; // actually this is the number of total possible moves, used to store them at a proper place in the array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check whether how many, if any, moves are possible
		}
	}
	if (pos_x != 0 && pos_y != 0 && board[pos_y - 1][pos_x - 1] == 0)
	{
		// selected piece can move to the upper left
		if (!take_flag)
		{
			possible_moves[size][1] = pos_x - 1;
			possible_moves[size][0] = pos_y - 1;
			size++; // increases the number of possible moves
		}
	}
	else
	{
		if (board[pos_y - 1][pos_x - 1] == 2 || board[pos_y - 1][pos_x - 1] == 4) // if the tile to the upper left contains a black piece
		{
			// if selected tile is at least two tiles away from the edge and if the tile directly behind the enemy piece is empty
			if (pos_x != 1 && pos_y != 1 && board[pos_y - 2][pos_x - 2] == 0)
			{
				// selected piece can move to the upper left and take an enemy piece
				possible_moves[size][1] = pos_x - 2;
				possible_moves[size][0] = pos_y - 2;
				take_flag++; // increases the number of moves that result in a piece being taken
				size++; // increases the number of possible moves
			}
		}
	}
	// if the selected tile is not directly on the upper or right edge and if the tile to the upper right is empty
	if (pos_x != 7 && pos_y != 0 && board[pos_y - 1][pos_x + 1] == 0)
	{
		if (!take_flag) // if there isn't a move that results in a piece being taken
		{
			// selected piece can move to the upper right
			possible_moves[size][1] = pos_x + 1;
			possible_moves[size][0] = pos_y - 1;
			size++;
		}  // increases the number of possible moves
	}
	else
	{
		if (board[pos_y - 1][pos_x + 1] == 2 || board[pos_y - 1][pos_x + 1] == 4) // if the tile to the upper right contains a black piece
		{
			// if selected tile is at least two tiles away from the edge and if the tile directly behind the enemy piece is empty
			if (pos_x != 6 && pos_y != 1 && board[pos_y - 2][pos_x + 2] == 0)
			{
				// if the previously checked move wasn't a take, this one overrides the previous one 
				// as to only allow a move that results in a piece being taken if one exists
				if (!take_flag)
				{
					size = 0; // resets the number of possible moves
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible
						}
					}
				}
				take_flag++; // increases the number of possible moves that result in a piece being taken
				// selected piece can move to the upper right and take an enemy piece
				possible_moves[size][1] = pos_x + 2;
				possible_moves[size][0] = pos_y - 2;
				size++; // increases the number of possible moves 
			}
		}
	}
	// if selected piece isn't near the left edge or the down of the board and if the tile to the lower left is empty
	if (pos_x != 0 && pos_y != 7 && board[pos_y + 1][pos_x - 1] == 0)
	{
	// selected piece can move to the lower left
		if (!take_flag)
		{
			possible_moves[size][1] = pos_x - 1;
			possible_moves[size][0] = pos_y + 1;
			size++; // increases the number of possible moves
		}
	}
	else
	{
		if (board[pos_y + 1][pos_x - 1] == 2 || board[pos_y + 1][pos_x - 1] == 4) // if the tile to the lower left contains a black piece
		{
			if (pos_x != 1 && pos_y != 6 && board[pos_y + 2][pos_x - 2] == 0)
			{
				if (!take_flag)
				{
					size = 0;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible
						}
					}
				}
				possible_moves[size][1] = pos_x - 2;
				possible_moves[size][0] = pos_y + 2;
				take_flag++;
				size++;
			}
		}
	}
	if (pos_x != 7 && pos_y != 7 && board[pos_y + 1][pos_x + 1] == 0)
	{
		if (!take_flag)
		{
			possible_moves[size][1] = pos_x + 1;
			possible_moves[size][0] = pos_y + 1;
			size++;
		}
		
	}
	else
	{
		if (board[pos_y + 1][pos_x + 1] == 2 || board[pos_y + 1][pos_x + 1] == 4)
		{
			if (pos_x != 6 && pos_y != 6 && board[pos_y + 2][pos_x + 2] == 0)
			{
				if (!take_flag)
				{
					size = 0;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible
						}
					}
				}
				take_flag++;
				possible_moves[size][1] = pos_x + 2;
				possible_moves[size][0] = pos_y + 2;
				size++;
			}
		}
	}
}

void possible_moves_queen_black(int board[8][8], int possible_moves[4][2], int pos_x, int pos_y, int take_flag = 0)
{
	// flag that forces the piece to take if able
	int size = 0; // actually this is the number of total possible moves, used to store them at a proper place in the array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible
		}
	}
	if (pos_x != 0 && pos_y != 0 && board[pos_y - 1][pos_x - 1] == 0)
	{
		// selected piece can move to the upper left
		if (!take_flag)
		{
			possible_moves[size][1] = pos_x - 1;
			possible_moves[size][0] = pos_y - 1;
			size++; // increases the number of possible moves
		}
	}
	else
	{
		if (board[pos_y - 1][pos_x - 1] == 1 || board[pos_y - 1][pos_x - 1] == 3) // if the tile to the upper left contains a black piece
		{
			// if selected tile is at least two tiles away from the edge and if the tile directly behind the enemy piece is empty
			if (pos_x != 1 && pos_y != 1 && board[pos_y - 2][pos_x - 2] == 0)
			{
				// selected piece can move to the upper left and take an enemy piece
				possible_moves[size][1] = pos_x - 2;
				possible_moves[size][0] = pos_y - 2;
				take_flag++; // increases the number of moves that result in a piece being taken
				size++; // increases the number of possible moves
			}
		}
	}
	// if the selected tile is not directly on the upper or right edge and if the tile to the upper right is empty
	if (pos_x != 7 && pos_y != 0 && board[pos_y - 1][pos_x + 1] == 0)
	{
		if (!take_flag) // if there isn't a move that results in a piece being taken
		{
			// selected piece can move to the upper right
			possible_moves[size][1] = pos_x + 1;
			possible_moves[size][0] = pos_y - 1;
			size++;
		}
		  // increases the number of possible moves
	}
	else
	{
		if (board[pos_y - 1][pos_x + 1] == 1 || board[pos_y - 1][pos_x + 1] == 3) // if the tile to the upper right contains a black piece
		{
			// if selected tile is at least two tiles away from the edge and if the tile directly behind the enemy piece is empty
			if (pos_x != 6 && pos_y != 1 && board[pos_y - 2][pos_x + 2] == 0)
			{
				// if the previously checked move wasn't a take, this one overrides the previous one 
				// as to only allow a move that results in a piece being taken if one exists
				if (!take_flag)
				{
					size = 0; // resets the number of possible moves
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible
						}
					}
				}
				take_flag++; // increases the number of possible moves that result in a piece being taken
				// selected piece can move to the upper right and take an enemy piece
				possible_moves[size][1] = pos_x + 2;
				possible_moves[size][0] = pos_y - 2;
				size++; // increases the number of possible moves 
			}
		}
	}
	// if selected piece isn't near the left edge or the down of the board and if the tile to the lower left is empty
	if (pos_x != 0 && pos_y != 7 && board[pos_y + 1][pos_x - 1] == 0)
	{
		// selected piece can move to the lower left
		if (!take_flag)
		{
			possible_moves[size][1] = pos_x - 1;
			possible_moves[size][0] = pos_y + 1;
			size++; // increases the number of possible moves
		}
	}
	else
	{
		if (board[pos_y + 1][pos_x - 1] == 1 || board[pos_y + 1][pos_x - 1] == 3) // if the tile to the lower left contains a black piece
		{
			if (pos_x != 1 && pos_y != 6 && board[pos_y + 2][pos_x - 2] == 0)
			{
				if (!take_flag)
				{
					size = 0;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible
						}
					}
				}
				possible_moves[size][1] = pos_x - 2;
				possible_moves[size][0] = pos_y + 2;
				take_flag++;
				size++;
			}
		}
	}
	if (pos_x != 7 && pos_y != 7 && board[pos_y + 1][pos_x + 1] == 0)
	{
		if (!take_flag)
		{
			possible_moves[size][1] = pos_x + 1;
			possible_moves[size][0] = pos_y + 1;
			size++;
		}

	}
	else
	{
		if (board[pos_y + 1][pos_x + 1] == 1 || board[pos_y + 1][pos_x + 1] == 3)
		{
			if (pos_x != 6 && pos_y != 6 && board[pos_y + 2][pos_x + 2] == 0)
			{
				if (!take_flag)
				{
					size = 0;
					for (int i = 0; i < 4; i++)
					{
						for (int j = 0; j < 2; j++)
						{
							possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible
						}
					}
				}
				take_flag++;
				possible_moves[size][1] = pos_x + 2;
				possible_moves[size][0] = pos_y + 2;
				size++;
			}
		}
	}
}

void check_possible_moves(int board[8][8], int possible_moves[4][2], int turn, int pos_x, int pos_y)
{
	int take_flag = 0; // flag that forces the piece to take if able
	int size = 0; // actually this is the number of total possible moves, used to store them at a proper place in the array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			possible_moves[i][j] = -1;  // resets the array to only minus ones, that way it's easier to check whether how many, if any, moves are possible
		}
	}
	if (turn) //if it's red's turn
	{
		if (board[pos_y][pos_x] == 1) // if selected tile contains a 1, ergo a red piece
		{
			// if selected piece isn't near the left edge or the top of the board and if the tile to the upper left is empty
			if (pos_x != 0 && pos_y != 0 && board[pos_y - 1][pos_x - 1] == 0)
			{
				// selected piece can move to the upper left
				possible_moves[size][1] = pos_x - 1;
				possible_moves[size][0] = pos_y - 1;
				size++; // increases the number of possible moves
			}
			else
			{
				if (board[pos_y - 1][pos_x - 1] == 2 || board[pos_y - 1][pos_x - 1] == 4) // if the tile to the upper left contains a black piece
				{
					// if selected tile is at least two tiles away from the edge and if the tile directly behind the enemy piece is empty
					if (pos_x != 1 && pos_y != 1 && board[pos_y - 2][pos_x - 2] == 0)
					{
						// selected piece can move to the upper left and take an enemy piece
						possible_moves[size][1] = pos_x - 2;
						possible_moves[size][0] = pos_y - 2;
						take_flag++; // increases the number of moves that result in a piece being taken
						size++; // increases the number of possible moves
					}
				}
			}
			// if the selected tile is not directly on the upper or right edge and if the tile to the upper right is empty
			if (pos_x != 7 && pos_y != 0 && board[pos_y - 1][pos_x + 1] == 0)
			{
				if (!take_flag) // if there isn't a move that results in a piece being taken
				{
					// selected piece can move to the upper right
					possible_moves[size][1] = pos_x + 1;
					possible_moves[size][0] = pos_y - 1;
				}
				size++;  // increases the number of possible moves
			}
			else
			{
				if (board[pos_y - 1][pos_x + 1] == 2 || board[pos_y - 1][pos_x + 1] == 4) // if the tile to the upper right contains a black piece
				{
					// if selected tile is at least two tiles away from the edge and if the tile directly behind the enemy piece is empty
					if (pos_x != 6 && pos_y != 1 && board[pos_y - 2][pos_x + 2] == 0)
					{
						// if the previously checked move wasn't a take, this one overrides the previous one 
						// as to only allow a move that results in a piece being taken if one exists
						if (!take_flag)
						{
							size = 0; // resets the number of possible moves
						}
						take_flag++; // increases the number of possible moves that result in a piece being taken
						// selected piece can move to the upper right and take an enemy piece
						possible_moves[size][1] = pos_x + 2;
						possible_moves[size][0] = pos_y - 2;
						size++; // increases the number of possible moves 
					}
				}
			}
		}
	}
	else // if it's black's turn
	{
		if (board[pos_y][pos_x] == 2) // if the selected tile contains a black piece
		{
			// if selected piece isn't near the left edge or the down of the board and if the tile to the lower left is empty
			if (pos_x != 0 && pos_y != 7 && board[pos_y + 1][pos_x - 1] == 0)
			{
				// selected piece can move to the lower left
				possible_moves[size][1] = pos_x - 1;
				possible_moves[size][0] = pos_y + 1;
				size++; // increases the number of possible moves
			}
			else
			{
				if (board[pos_y + 1][pos_x - 1] == 1 || board[pos_y + 1][pos_x - 1] == 3) // if the tile to the upper left contains a red piece
				{
					if (pos_x != 1 && pos_y != 6 && board[pos_y + 2][pos_x - 2] == 0)
					{
						possible_moves[size][1] = pos_x - 2;
						possible_moves[size][0] = pos_y + 2;
						take_flag++;
						size++;
					}
				}
			}
			if (pos_x != 7 && pos_y != 7 && board[pos_y + 1][pos_x + 1] == 0)
			{
				if (!take_flag)
				{
					possible_moves[size][1] = pos_x + 1;
					possible_moves[size][0] = pos_y + 1;
				}
				size++;
			}
			else
			{
				if (board[pos_y + 1][pos_x + 1] == 1 || board[pos_y + 1][pos_x + 1] == 3)
				{
					if (pos_x != 6 && pos_y != 6 && board[pos_y + 2][pos_x + 2] == 0)
					{
						if (!take_flag)
						{
							size = 0;
						}
						take_flag++;
						possible_moves[size][1] = pos_x + 2;
						possible_moves[size][0] = pos_y + 2;
						size++;
					}
				}
			}
		}
	}
	if (turn)
	{
		if (board[pos_y][pos_x] == 3)
			possible_moves_queen_red(board, possible_moves, pos_x, pos_y);
	}
	else
	{
		if (board[pos_y][pos_x] == 4)
			possible_moves_queen_black(board, possible_moves, pos_x, pos_y);
	}

}

// checks possible moves, but only those that result in a piece being taken
void check_possible_moves_only_takes(int board[8][8], int possible_moves[4][2], int turn, int pos_x, int pos_y)
{
	int size = 0; // actually this is the number of total possible moves, used to store them at a proper place in the array
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			possible_moves[i][j] = -1; // resets the array to only minus ones, that way it's easier to check how many, if any, moves are possible 
		}
	}
	if (turn) //if it's red's turn
	{
		if (board[pos_y][pos_x] == 1) // if selected tile contains a 1, ergo a red piece
		{
			// if the selected tile isn't directly near the edge and the tile to the upper left contains a black piece
			if (pos_x != 0 && pos_y != 0 && board[pos_y - 1][pos_x - 1] == 2)
			{
				if (pos_x != 1 && pos_y != 1 && board[pos_y - 2][pos_x - 2] == 0)
				{
					possible_moves[size][1] = pos_x - 2;
					possible_moves[size][0] = pos_y - 2;
					size++;
				}
			}
			if (pos_x != 7 && pos_y != 0 && board[pos_y - 1][pos_x + 1] == 2)
			{
				if (pos_x != 6 && pos_y != 1 && board[pos_y - 2][pos_x + 2] == 0)
				{
					possible_moves[size][1] = pos_x + 2;
					possible_moves[size][0] = pos_y - 2;
					size++;
				}

			}
		}
	}
	else // if it's black's turn
	{
		if (board[pos_y][pos_x] == 2)
		{
			if (pos_x != 0 && pos_y != 7 && board[pos_y + 1][pos_x - 1] == 1)
			{
				if (pos_x != 1 && pos_y != 6 && board[pos_y + 2][pos_x - 2] == 0)
				{
					possible_moves[size][1] = pos_x - 2;
					possible_moves[size][0] = pos_y + 2;
					size++;
				}
			}
			if (pos_x != 7 && pos_y != 7 && board[pos_y + 1][pos_x + 1] == 1)
			{
				if (pos_x != 6 && pos_y != 6 && board[pos_y + 2][pos_x + 2] == 0)
				{
					possible_moves[size][1] = pos_x + 2;
					possible_moves[size][0] = pos_y + 2;
					size++;
				}

			}
		}
	}
	if (turn)
	{
		if (board[pos_y][pos_x] == 3)
			possible_moves_queen_red(board, possible_moves, pos_x, pos_y, 1);
	}
	else
	{
		if (board[pos_y][pos_x] == 4)
			possible_moves_queen_black(board, possible_moves, pos_x, pos_y, 1);
	}
}

int count_pieces(int board[8][8])
{
	int result = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			result += (board[i][j] != 0) ? 1 : 0;
	}
	return result;
}