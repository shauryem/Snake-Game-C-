#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>


using namespace std;

//indicates when to exit application

bool gameOver;

//dimensions of game

const int width = 20;
const int height = 20;

//players and fruits coordinates

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];

//number of tail elements

int nTail;

//Indicates direction snake is going

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

//Setup function initiailzes the game to initla state

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;

	srand(time(NULL));
	//fruit spawns in random location

	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
// Draw function prints to the game to the console
void Draw()
{
	//clears console
	system("cls"); 


	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	// nested for loops print fruit and snake based on their coordinates

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "*";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}
//Input functon takes in WASD controls from player

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
//Logic function takes care of setting coordinate values for the snake/tail

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	
	// allows each partition of the tail to move behiind its predecessor

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//Handles out of bounds 

	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;

	//if (x >= width) x = 0; else if (x < 0) x = width - 1;
	//if (y >= height) y = 0; else if (y < 0) y = height - 1;
	
	//Handles tail collsions 

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	//Increments score and respawns fruit

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
//Main function repeatedly calls all prior functions
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10);
		// small quality of life fix so snake moves at equal speeds when going up, down, and side to side. 
		if (dir == LEFT || dir == RIGHT)
		{
			Sleep(5);
		}

		Sleep(100);

		if (dir == UP || dir == DOWN)
		{
			Sleep(60);
		}
	}
	return 0;
}