#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>

#pragma region Colors
#define Black 0
#define Blue 1  
#define Green 2
#define Aqua 3
#define Red 4
#define Purpule 5
#define Yellow 6
#define White 7
#define Gray 8
#define LightBlue 9
#define LightGreen 10
#define LightAqua 11
#define LightRed 12
#define LightPurpule 13
#define LightYellow 14
#define BrightWhite 15
#pragma endregion

void SetColor(char bg, char fg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg * 16 + fg);
}
void SetColorDefualt()
{
	SetColor(Black, White);
}

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
#define amirk true
using namespace std;
const int size = 22 + 1;
bool box[size][size * 2];
int colorBox[size][size];


void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void clearScreen()
{
	gotoXY(0, 0);
}

struct Location{
	int i;
	int j;

};

#pragma region ClassShape
class shape{
	int state; // 1- 2 -  3 - 4
	int model;
	int color;
	Location location[4];
public:

	bool checkRightEmpty();
	bool checkLeftEmpty();
	void modelRandom(){ model = rand() % 7; };
	void Model(int MODEL){ model = MODEL; };
	void create();
	bool checkDownEmpty();
	void moveDown();
	void moveRigh();
	void moveLeft();
	void move();
	void specialMove();
	bool MovingItem(int i, int j);
	void setColorOfShape(){ color = rand() % 4; };
};
bool shape::MovingItem(int i, int j)
{
	for (int k = 0; k < 4; k++)
	{
		if (location[k].i == i && location[k].j == j)
			return true;
	}

	return false;
}
bool shape::checkRightEmpty()
{


	int SIZE = 0;
	for (int k = 0; k < 4; k++)
	{
		if (box[location[k].i][location[k].j + 1])
		{
			int z;
			for (z = 0; z < 4; z++)
			{
				if (location[z].i == location[k].i && location[z].j == location[k].j + 1)
					break;
			}
			if (z == 4)
				return false;

		}
		if (location[k].j == size - 2)
			return false;
		SIZE++;
		if (SIZE == 4)
			return true;
	}

}

bool shape::checkLeftEmpty()
{

	int SIZE = 0;
	for (int k = 0; k < 4; k++)
	{
		if (box[location[k].i][location[k].j - 1])
		{
			int z;
			for (z = 0; z < 4; z++)
			{
				if (location[z].i == location[k].i && location[z].j == location[k].j - 1)
					break;
			}
			if (z == 4)
				return false;

		}
		if (location[k].j == 1)
			return false;
		SIZE++;
		if (SIZE == 4)
			return true;
	}

}

void shape::create()
{
	setColorOfShape();
	state = 1;
	int k = 0;
	switch (model + 1)
	{
	case 1: // I shape
		for (int i = 0; i < 4; i++)
		{
			location[i].i = i;
			location[i].j = 10;
			box[i][10] = true;


		}
		break;
	case 2: // J Shape
		for (int i = 0; i < 3; i++)
		{
			location[i].i = i;
			location[i].j = 10;
			box[i][10] = true;

		}

		location[3].i = 2; location[3].j = 9;
		box[2][9] = true;

		break;
	case 3: // L shape
		for (int i = 0; i < 3; i++)
		{
			location[i].i = i; location[i].j = 10;
			box[i][10] = amirk;

		}
		box[0][9] = amirk;

		location[3].i = 0; location[3].j = 9;
		break;
	case 4: // O shape;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 9; j < 11; j++)
			{

				box[i][j] = amirk;
				location[k++].i = i;
				location[k - 1].j = j;
			}
		}
		break;
	case 5: // Z shape
		for (int j = 9; j < 11; j++)
		{
			location[k++].i = 0;
			location[k - 1].j = j;
			box[0][j] = amirk;

		}
		for (int j = 10; j < 12; j++)
		{
			location[k++].i = 1;
			location[k - 1].j = j;
			box[1][j] = amirk;

		}
		break;
	case 6: // T Shape
		box[0][10] = amirk;

		location[k++].j = 10;
		location[k - 1].i = 0;
		for (int j = 9; j <12; j++)
		{
			location[k++].i = 1;
			location[k - 1].j = j;
			box[1][j] = amirk;
		}
		break;
	case 7: // S shape
		for (int j = 10; j < 12; j++)
		{
			location[k++].j = j;
			location[k - 1].i = 0;
			box[0][j] = amirk;
		}
		for (int j = 9; j < 11; j++)
		{
			location[k++].i = 1;
			location[k - 1].j = j;
			box[1][j] = amirk;
		}
		break;
	default:
		break;
	}

	for (int k = 0; k < 4; k++)
	{
		colorBox[location[k].i][location[k].j] = color;
	}

}

bool shape::checkDownEmpty()
{

	int SIZE = 0;
	for (int k = 0; k < 4; k++)
	{
		if (box[location[k].i + 1][location[k].j])
		{
			int z;
			for (z = 0; z < 4; z++)
			{
				if (location[z].i == location[k].i + 1 && location[z].j == location[k].j)
					break;
			}
			if (z == 4)
				return false;

		}
		if (location[k].i == size - 2)
			return false;
		SIZE++;
		if (SIZE == 4)
			return true;
	}


}

void shape::moveDown()
{

	for (int i = size - 1; i >= 0; i--)
	{

		for (int j = 0; j < 4; j++)
		{
			if (location[j].i == i)
			{
				for (int k = 0; k < size; k++)
				{
					if (location[j].j == k)
					{
						swap(box[i + 1][k], box[i][k]);
						swap(colorBox[i + 1][k], colorBox[i][k]);
						location[j].i++;
					}
				}
			}
		}
	}




}

void shape::moveRigh()
{


	for (int i = size - 1; i >= 0; i--)
	{

		for (int j = 0; j < 4; j++)
		{
			if (location[j].j == i)
			{
				for (int k = size - 1; k >= 0; k--)
				{
					if (location[j].i == k)
					{
						swap(colorBox[k][i], colorBox[k][i + 1]);
						swap(box[k][i], box[k][i + 1]);
						location[j].j++;
					}
				}
			}
		}
	}


}


void shape::moveLeft()
{

	for (int j = 0; j < size; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (location[k].j == j)
			{
				for (int i = 0; i < size; i++)
				{
					if (location[k].i == i){
						swap(colorBox[i][j], colorBox[i][j - 1]);

						swap(box[i][j], box[i][j - 1]);
						location[k].j--;
					}
				}
			}
		}
	}

}


void shape::move()
{
	if (GetAsyncKeyState(VK_UP))
		specialMove();

	if (GetAsyncKeyState(VK_RIGHT))
	if (checkRightEmpty())
	{

		moveRigh();
	}
	if (GetAsyncKeyState(VK_LEFT))
	if (checkLeftEmpty())
	{

		moveLeft();
	}
	if (GetAsyncKeyState(VK_DOWN))
	if (checkDownEmpty())
		moveDown();


}


void shape::specialMove()
{
	bool flag = false;
	switch (model + 1)
	{
	case 1: // I or -
		if (state == 1)
		{
			for (int z = 0; z < 4; z++)
			{
				if (box[location[2].i][location[2].j - 2 + z] && z != 2)
				{
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;
					box[location[i].i][location[i].j] = false;
				}
				location[0].i += 2; location[0].j += 1;
				location[1].i += 1; location[1].j -= 1;
				location[3].i -= 1; location[3].j -= 2;

				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = true;
					colorBox[location[i].i][location[i].j] = color;

				}
				state = 2;
				break;
			}
		}
		if (state == 2)
		{
			for (int z = 0; z < 4; z++)
			{
				if (box[location[2].i + 2 - z][location[2].j] && z != 2)
					flag = true;
			}

			if (!flag)
			{

				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;
					box[location[i].i][location[i].j] = false;
				}
				location[0].i -= 2; location[0].j -= 1;
				location[1].i -= 1; location[1].j += 1;
				location[3].i += 1; location[3].j += 2;

				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;
					box[location[i].i][location[i].j] = true;
				}
				state = 1;
				break;
			}
		}
		break;
	case 2: // J
		if (state == 1)
		{
			if (box[location[1].i][location[1].j + 1] || box[location[1].i][location[1].j - 1] || box[location[1].i - 1][location[1].j - 1])
				flag = true;
			if (!flag)
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}
				location[0].i += 1; location[0].j += 1;
				location[2].i -= 1; location[2].j -= 1;
				location[3].i -= 2;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				state = 2;
				break;
			}


		}
		if (state == 2)
		{
			if (box[location[1].i + 1][location[1].j] || box[location[1].i - 1][location[1].j] || box[location[1].i - 1][location[1].j + 1])
				flag = true;
			if (!flag)
			{

				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}

				location[0].i += 1; location[0].j -= 1;
				location[2].i -= 1; location[2].j += 1;
				location[3].j += 2;

				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = true;
					colorBox[location[i].i][location[i].j] = color;

				}
				state = 3;

			}
			break;
		}
		if (state == 3)
		{
			if (box[location[1].i][location[1].j - 1] || box[location[1].i][location[1].j + 1] || box[location[1].i + 1][location[1].j + 1])
				flag = true;
			if (!flag)
			{

				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}

				location[0].i -= 1; location[0].j -= 1;
				location[2].i += 1; location[2].j += 1;
				location[3].i += 2;

				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = true;
					colorBox[location[i].i][location[i].j] = color;

				}
				state = 4;

			}
			break;

		}

		if (state == 4)
		{
			if (box[location[1].i - 1][location[1].j] || box[location[1].i + 1][location[1].j] || box[location[1].i + 1][location[1].j - 1])
				flag = true;
			if (!flag)
			{


				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}

				location[0].i -= 1; location[0].j += 1;
				location[2].i += 1; location[2].j -= 1;
				location[3].j -= 2;

				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = true;
					colorBox[location[i].i][location[i].j] = color;

				}
				state = 1;

			}
		}
		break;
	case 3: // L
		if (state == 1)
		{
			if (box[location[1].i][location[1].j + 1] || box[location[1].i][location[1].j - 1] || box[location[1].i - 1][location[1].j + 1])
				flag = true;
			if (!flag)
			{
				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = false;
					colorBox[location[i].i][location[i].j] = 0;

				}
				location[0].i += 1; location[0].j += 1;
				location[2].i -= 1; location[2].j -= 1;
				location[3].j += 2;
				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = true;
					colorBox[location[i].i][location[i].j] = color;

				}
				state = 2;

			}
			break;
		}
		if (state == 2)
		{
			if (box[location[1].i + 1][location[1].j] || box[location[1].i - 1][location[1].j] || box[location[1].i + 1][location[1].j + 1])
				flag = true;
			if (!flag)
			{

				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = false;
					colorBox[location[i].i][location[i].j] = 0;

				}

				location[0].i += 1; location[0].j -= 1;
				location[2].i -= 1; location[2].j += 1;
				location[3].i += 2;

				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = true;
					colorBox[location[i].i][location[i].j] = color;

				}
				state = 3;

			}
			break;
		}
		if (state == 3)
		{
			if (box[location[1].i][location[1].j - 1] || box[location[1].i][location[1].j + 1] || box[location[1].i + 1][location[1].j - 1])
				flag = true;
			if (!flag)
			{

				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}

				location[0].i -= 1; location[0].j -= 1;
				location[2].i += 1; location[2].j += 1;
				location[3].j -= 2;

				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = true;
					colorBox[location[i].i][location[i].j] = color;

				}
				state = 4;

			}
			break;

		}

		if (state == 4)
		{
			if (box[location[1].i - 1][location[1].j] || box[location[1].i + 1][location[1].j] || box[location[1].i - 1][location[1].j - 1])
				flag = true;
			if (!flag)
			{


				for (int i = 0; i < 4; i++)
				{
					box[location[i].i][location[i].j] = false;
					colorBox[location[i].i][location[i].j] = 0;

				}

				location[0].i -= 1; location[0].j += 1;
				location[2].i += 1; location[2].j -= 1;
				location[3].i -= 2;

				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}

				state = 1;

			}
		}
		break;

	case 4: // O
		break;
	case 5: // Z
		if (state == 1)
		{
			if (box[location[2].i + 1][location[2].j] || box[location[2].i - 1][location[2].j + 1])
				flag = true;
			if (!flag)
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}
				location[0].j += 2;
				location[1].i += 1; location[1].j += 1;
				location[3].j -= 1; location[3].i += 1;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				state = 2;
				break;
			}

		}
		if (state == 2)
		{
			if (box[location[2].i][location[2].j - 1] || box[location[2].i + 1][location[2].j + 1])
				flag = true;
			if (!flag)
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}
				location[0].i += 2;
				location[1].i += 1; location[1].j -= 1;
				location[3].j -= 1; location[3].i -= 1;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				state = 3;

			}
			break;
		}
		if (state == 3)
		{
			if (box[location[2].i - 1][location[2].j] || box[location[2].i + 1][location[2].j - 1])
				flag = true;
			if (!flag)
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}
				location[0].j -= 2;
				location[1].i -= 1; location[1].j -= 1;
				location[3].j += 1; location[3].i -= 1;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				state = 4;
				break;
			}
		}
		if (state == 4)
		{
			if (box[location[2].i - 1][location[2].j - 1] || box[location[2].i][location[2].j + 1])
				flag = true;
			if (!flag)
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}
				location[0].i -= 2;
				location[1].i -= 1; location[1].j += 1;
				location[3].j += 1; location[3].i += 1;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				state = 1;
				break;

			}
		}
		break;

	case 6: // T
		if (state == 1)
		{
			if (!box[location[2].i + 1][location[2].j])
			{
				swap(box[location[1].i][location[1].j], box[location[1].i + 1][location[1].j + 1]);

				swap(colorBox[location[1].i][location[1].j], colorBox[location[1].i + 1][location[1].j + 1]);
				location[1].i += 1;
				location[1].j += 1;
				state = 2;
			}

			break;
		}
		if (state == 2)
		{
			if (!box[location[2].i][location[2].j - 1])
			{
				swap(colorBox[location[0].i][location[0].j], colorBox[location[0].i + 1][location[0].j - 1]);

				swap(box[location[0].i][location[0].j], box[location[0].i + 1][location[0].j - 1]);
				location[0].i += 1;
				location[0].j -= 1;
				state = 3;
				break;
			}

		}
		if (state == 3)
		{
			if (!box[location[2].i - 1][location[2].j])
			{
				swap(colorBox[location[3].i][location[3].j], colorBox[location[3].i - 1][location[3].j - 1]);

				swap(box[location[3].i][location[3].j], box[location[3].i - 1][location[3].j - 1]);
				location[3].i -= 1;
				location[3].j -= 1;
				state = 4;
				break;
			}
		}
		if (state == 4)
		{
			if (!box[location[2].i][location[3].j + 1])
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;
					box[location[i].i][location[i].j] = false;
				}
				state = 1;
				location[0].i = location[2].i - 1;
				location[0].j = location[2].j;
				location[1].i = location[3].i = location[2].i;
				location[1].j = location[2].j - 1;
				location[3].j = location[2].j + 1;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				break;
			}

		}

	case 7: // S
		if (state == 1)
		{
			if (!box[location[3].i][location[3].j + 1] || !box[location[3].i + 1][location[3].j + 1])
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}
				location[0].i += 1; location[0].j += 1;
				location[1].i += 2;
				location[2].i -= 1; location[2].j += 1;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				state = 2;
				break;
			}

		}
		if (state == 2)
		{
			if (!box[location[3].i][location[3].j - 1] || !box[location[3].i - 1][location[3].j + 1])
			{
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = 0;

					box[location[i].i][location[i].j] = false;
				}
				location[0].i -= 1; location[0].j -= 1;
				location[1].i -= 2;
				location[2].i += 1; location[2].j -= 1;
				for (int i = 0; i < 4; i++)
				{
					colorBox[location[i].i][location[i].j] = color;

					box[location[i].i][location[i].j] = true;
				}
				state = 1;
				break;
			}


		}
		break;
	}




}

#pragma endregion

void nextElemet(int model);
void cleaning();

bool Lose(shape shape1){
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < size - 1; j++)
		{
			if (box[i][j] && !shape1.MovingItem(i, j))
				return true;
		}
	}

	return false;
}

void clearNextElemet(int model);
void show();
long score = 0;
int main(void)
{
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == size - 1 || j == 0 || j == size - 1)
				box[i][j] = true;
			else
				box[i][j] = false;
		}
	}

	int NextElemet = rand() % 7;
	nextElemet(NextElemet);
	int previosElemet = -1;
	shape shape1;
	shape1.modelRandom();
	shape1.create();
	while (true)
	{
		show();
		clearScreen();
		if (shape1.checkDownEmpty())
		{
			shape1.moveDown();
			shape1.move();
		}
		else
		{
			score += 5;
			cleaning();
			if (Lose(shape1))
				break;
			clearNextElemet(NextElemet);
			shape1.Model(NextElemet);
			NextElemet = rand() % 7;
			nextElemet(NextElemet);
			shape1.create();
		}

		Sleep(150);
	}
	gotoXY(size + 15, size / 2);
	cout << "You Lose";
	_getch();

}

void SetColorForShow(int i,int j)
{

	switch (colorBox[i][j])
	{
	case 0:
		SetColorDefualt();
		break;
	case 1: // red
		SetColor(Black, LightRed);
		break;
	case 2: // Blue
		SetColor(Black, Blue);
		break;
	case 3:
		SetColor(Black, LightYellow);
		break;
	default:
		break;
	}

}

void show()
{

	int I = size / 2;
	int J = size;
	for (size_t k = 0; k < 3; k++)
	{
		for (size_t l = -1; l < 2; l++)
		{
			colorBox[I + k][J + l] = 0;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size * 2; j++)
		{
			if (j == 0 || j == size - 1)
				cout << (char)176;
			else if (i == size - 1 && j < size)
				cout << (char)176;
			else if (box[i][j] )
			{
				SetColorForShow(i, j);
				cout << (char)219;
				SetColorDefualt();
			}
			else
				cout << " ";
		}
		cout << endl;
	}
	gotoXY(size + 5, 3);
	cout << "Score = " << score;

}

bool checkLineFull(int line)
{
	for (int i = 1; i < size - 1; i++)
	{
		if (!box[line][i])
			return false;
	}

	return true;
}
bool checkLineEmpty(int line)
{
	for (int i = 1; i < size - 1; i++)
	{
		if (box[line][i])
			return false;
	}

	return true;

}

void cleaning()
{
	for (int i = 5; i < size - 1; i++)
	{
		if (checkLineFull(i))
		{
			for (int j = 1; j < size - 1; j++)
			{
				colorBox[i][j] = 0;
				box[i][j] = false;

			}
			for (int k = i - 1; k >= 0 && !checkLineEmpty(k); k--)
			{
				score += 50;
				for (int Z = 1; Z < size - 1; Z++)
				{
					swap(colorBox[k][Z], colorBox[k + 1][Z]);
					swap(box[k][Z], box[k + 1][Z]);
				}
			}
		}
	}
}
void nextElemet(int model)
{
	int I = size / 2;
	int J = size;
	int k = 0;
	switch (model + 1)
	{
	case 1: // I shape
		for (int i = 0; i < 4; i++)
		{
			box[i + I][10 + J] = true;
		}
		break;
	case 2: // J Shape
		for (int i = 0; i < 3; i++)
		{
			box[i + I][10 + J] = true;
		}
		box[2 + I][J + 9] = true;
		break;
	case 3: // L shape
		for (int i = 0; i < 3; i++)
		{
			box[i + I][10 + J] = amirk;
		}
		box[0 + I][9 + J] = amirk;
		break;
	case 4: // O shape;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 9; j < 11; j++)
			{
				box[i + I][j + J] = amirk;
			}
		}
		break;
	case 5: // Z shape
		for (int j = 9; j < 11; j++)
		{
			box[0 + I][j + J] = amirk;
		}
		for (int j = 10; j < 12; j++)
		{
			box[1 + I][j + J] = amirk;
		}
		break;
	case 6: // T Shape
		box[I + 0][J + 10] = amirk;
		for (int j = 9; j <12; j++)
		{
			box[1 + I][j + J] = amirk;
		}
		break;
	case 7: // S shape
		for (int j = 10; j < 12; j++)
		{
			box[0 + I][J + j] = amirk;
		}
		for (int j = 9; j < 11; j++)
		{
			box[1 + I][J + j] = amirk;
		}
		break;
	default:
		break;
	}




}
void clearNextElemet(int model)
{

	int I = size / 2;
	int J = size;
	for (size_t k =0; k < 3; k++)
	{
		for (size_t l = -1; l < 2; l++)
		{
			colorBox[I + k][J + l] = 0;
		}
	}

	int k = 0;
	switch (model + 1)
	{
	case 1: // I shape
		for (int i = 0; i < 4; i++)
		{
			box[i + I][10 + J] = false;
		}
		break;
	case 2: // J Shape
		for (int i = 0; i < 3; i++)
		{
			box[i + I][10 + J] = false;
		}
		box[2 + I][J + 9] = false;
		break;
	case 3: // L shape
		for (int i = 0; i < 3; i++)
		{
			box[i + I][10 + J] = false;
		}
		box[0 + I][9 + J] = false;
		break;
	case 4: // O shape;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 9; j < 11; j++)
			{
				box[i + I][j + J] = false;
			}
		}
		break;
	case 5: // Z shape
		for (int j = 9; j < 11; j++)
		{
			box[0 + I][j + J] = false;
		}
		for (int j = 10; j < 12; j++)
		{
			box[1 + I][j + J] = false;
		}
		break;
	case 6: // T Shape
		box[I + 0][J + 10] = false;
		for (int j = 9; j <12; j++)
		{
			box[1 + I][j + J] = false;
		}
		break;
	case 7: // S shape
		for (int j = 10; j < 12; j++)
		{
			box[0 + I][J + j] = false;
		}
		for (int j = 9; j < 11; j++)
		{
			box[1 + I][J + j] = false;
		}
		break;
	default:
		break;
	}




}