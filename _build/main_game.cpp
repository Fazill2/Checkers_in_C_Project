#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "gamelogic.h"



constexpr auto SCREEN_WIDTH = 800;;
constexpr auto SCREEN_HEIGHT = 800;;
constexpr auto BOARD_SIZE = 8;;

int main()
{
	// set up the window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "checkers");
	Image crown = LoadImage("crown.png"); // loads the image of the crown
	ImageResize(&crown, 75, 75); // resizes the image
	Texture2D texture = LoadTextureFromImage(crown);  // creates texture from the image
	UnloadImage(crown);  // unloads the image from ram
	int flag = 1;  // flag for drawing the board
	int possible_moves[4][2]; // array for possible moves
	int possible_moves_win_condition[4][2]; // array used for counting number_of_possible_moves, created as to not interfere with the other array
	// board initialization
	int board[BOARD_SIZE][BOARD_SIZE] =
	{ { 0, 2, 0, 2, 0, 2, 0, 2 },
	{ 2, 0, 2, 0, 2, 0, 2, 0 },
	{ 0, 2, 0, 2, 0, 2, 0, 2 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 0, 1, 0, 1, 0, 1, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0 } };
	int turn = 1;  // flag for turn
	int take_flag = 0; // flag whether the piece is doing a multiple captures
	int force_take_flag = 0; // flag whether there is a move that results in a piece being taken
	int clicked_tile_x = 9, clicked_tile_y = 9;  // coordinates of a tile clicked by user
	int selected_tile_x = 9, selected_tile_y = 9;  // coordinates of a tile last selected by user
	int selecting_move_flag = 0; // flag whether player is making a move
	int close_flag = 0; // flag whether the game is over
	int num_of_possible_moves = 0; // variable containing number of possible moves that active player can play, used for checking if the game is over
	int queen_square = 0;
	int red_queen = 0, black_queen = 0;
	int num_of_pieces_record[300];
	int turn_count = 0;
	int draw_flag = 0;
	SetTargetFPS(60);
	Vector2 mousePosition = { 0 };
	// game loop
	while (!WindowShouldClose())
	{
		// drawing
		BeginDrawing();
		
		ClearBackground(BLACK); // sets background as black, doesn't matter as the board takes up the whole window
		// drawing tiles
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)  // loop that checks every square
			{
				if (flag)
					DrawRectangle(i * 100, j * 100, 100, 100, BEIGE);
				else
					DrawRectangle(i * 100, j * 100, 100, 100, BROWN);
				if (i == clicked_tile_x && j == clicked_tile_y)
				{
					DrawRectangle(i * 100, j * 100, 100, 100, GREEN);  // currently clicked tile is green
				}
				for (int k = 0; k < 4; k++)
				{
					if (i == possible_moves[k][1] && j == possible_moves[k][0])
					{
						DrawRectangle(i * 100, j * 100, 100, 100, DARKGREEN); // possible moves are dark green
					}
				}
				flag = (flag) ? 0 : 1; // next square will have a diffrent color than the current one
			}
			flag = (flag) ? 0 : 1; // if first square in the row was beige, in the next row the first square will be brown
		}
		// drawing pieces
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) // loop that checks every single square on the board
			{
				if (board[i][j] == 1)
					DrawCircle(j * 100 + 50, i * 100 + 50, 40, RED); // red pieces are represented by ones
				if (board[i][j] == 3)
				{
					DrawCircle(j * 100 + 50, i * 100 + 50, 40, RED); // red queens are represented by threes
					DrawTexture(texture, j * 100 + 12, i * 100 + 10,  WHITE); // draws the crown ontop of the queen
				}
				if (board[i][j] == 2)
					DrawCircle(j * 100 + 50, i * 100 + 50, 40, BLACK);  // black pieces are represented by twos
				if (board[i][j] == 4)
				{
					DrawCircle(j * 100 + 50, i * 100 + 50, 40, BLACK);  // black queens are represented by fours
					DrawTexture(texture, j * 100 + 12, i * 100 + 10, WHITE);  // draws the crown ontop of the queen
				}
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))  // if player pressed left mouse button
		{
			mousePosition = GetMousePosition();  // gets mouse position when the left button is pressed
			clicked_tile_x = (int)mousePosition.x / 100; // turns mouse coordinates into positions in array
			clicked_tile_y = (int)mousePosition.y / 100; // turns mouse coordinates into positions in array

			// if player isn't currently selecting destination tile, clicked tile isn't empty and if player isn't making a multiple captures in a row
			if (!selecting_move_flag && board[clicked_tile_y][clicked_tile_x] != 0 && !take_flag) 
			{
				selected_tile_x = clicked_tile_x, selected_tile_y = clicked_tile_y; // previously clicked tile becomes the selected tile
				if (!force_take_flag)
					check_possible_moves(board, possible_moves, turn, clicked_tile_x, clicked_tile_y); // checks possible moves for the selected tile
				else
					check_possible_moves_only_takes(board, possible_moves, turn, clicked_tile_x, clicked_tile_y);
				selecting_move_flag = 1; // player is selecting a destination tile
			}
			else
			{
				for (int i = 0; i < 4; i++) // checks all possible moves for selected tile
				{
					if (clicked_tile_y == possible_moves[i][0] && clicked_tile_x == possible_moves[i][1]) // if player chose a tile that was a possible move
					{
						move(board, selected_tile_x, selected_tile_y, possible_moves[i][1], possible_moves[i][0]); // moves the piece from selected tile to destination tile
						queen_square = possible_moves[i][1];
						if (possible_moves[i][0] == 0 && turn) // if the red piece just moved to the oposite edge of the board
							red_queen = 1;
						if (possible_moves[i][0] == 7 && !turn)  // if the black piece just moved to the oposite edge of the board
							black_queen = 1;
						selecting_move_flag = 0; // player is no longer selecting a destination tile 
						possible_moves[0][0] = -1; // sets the first entry in possible_moves to -1 for future if
						if (abs(selected_tile_x - clicked_tile_x) != 1) // checks whether a piece was taken in the last move
						{
							// checks if the piece that just took can take again
							check_possible_moves_only_takes(board, possible_moves, turn, clicked_tile_x, clicked_tile_y); 
							// sets selected tile to the tile that the piece just moved to
							selected_tile_x = clicked_tile_x;
							selected_tile_y = clicked_tile_y;
						}
						if (possible_moves[0][0] == -1) // if true, the piece that just moved cannot take again
						{
							turn = (turn) ? 0 : 1; // passes the turn
							turn_count++;
							num_of_pieces_record[turn_count - 1] = count_pieces(board);
							if (turn_count > 300)
							{
								draw_flag = 1;
								close_flag = 1;
							}
							else
							{
								if (turn_count > 50) // draw condition
								{
									if (num_of_pieces_record[turn_count - 1] == num_of_pieces_record[turn_count - 50]) // draw condition
									{
										draw_flag = 1;
										close_flag = 1;
									}
								}
							}
							if (red_queen)
								board[0][queen_square] = 3; // replaces the red piece with the red queen
							if (black_queen)
								board[7][queen_square] = 4;
							black_queen = red_queen = 0;
							take_flag = 0; // resets the flag
							force_take_flag = 0;
							for (int i = 0; i < 8; i++)
							{
								for (int j = 0; j < 8; j++) // checks whether the new active player can make any moves
								{
									check_possible_moves_only_takes(board, possible_moves_win_condition, turn, i, j);
									if (possible_moves_win_condition[0][0] != -1)
										force_take_flag = 1;
								}
							}
						}
						else
						{
							take_flag = 1; // piece that just moved can take and has to move again
						}
						num_of_possible_moves = 0; // resets the count of possible moves
						for (int i = 0; i < 8; i++)
						{
							for (int j = 0; j < 8; j++) // checks whether the new active player can make any moves
							{
								check_possible_moves(board, possible_moves_win_condition, turn, i, j);
								if (possible_moves_win_condition[0][0] != -1)
									num_of_possible_moves++;
								if (possible_moves_win_condition[1][0] != -1)
									num_of_possible_moves++;
							}
						}
						if (num_of_possible_moves == 0) // true if active player has no moves
						{
							close_flag = 1; // states that the game is over and inactive player won
						}
						
						break; // breakes the loop, doesn't do much becouse of the low number of possible moves
					}
				}
			}

		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !take_flag) // resets possible moves and allows user to select another piece to move
		{
			selecting_move_flag = 0;  // active player is no longer selecting a destination tile
			check_possible_moves(board, possible_moves, turn, 9, 9);  // resets the possible_moves
		}



		EndDrawing();
		if (close_flag)  // game is over and window should be closed
		{
			break; // breaks the game loop
		}
	}

	// cleanup
	CloseWindow();

	InitWindow(250, 50, "End_of_the_game");  // initializes window with the information as to who won
	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// drawing
		BeginDrawing();
		ClearBackground(WHITE);
		if (draw_flag)
		{
			DrawText("Draw", 75, 0, 42, BLACK);
		}
		else
		{
			if (turn)
				DrawText("Black Wins", 10, 0, 42, BLACK);  // black wins if they were inactive when game concluded 
			else
				DrawText("Red Wins", 25, 0, 42, RED); // red wins if they were inactive when game concluded 
		}
		EndDrawing();

	}
	CloseWindow();
	return 0;
}