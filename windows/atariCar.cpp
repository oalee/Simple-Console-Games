#include<Windows.h>
#include<iostream>
#include<time.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
const int X = 28;
const int Y = 12;
char box[X][Y];
bool checkCars[X][Y];

void gotoXY(int x,int y)
{
	CursorPosition.X= x;
	CursorPosition.Y= y;
	SetConsoleCursorPosition(console,CursorPosition);
}
void clearScreen()
{
	gotoXY(0,0);
}
bool checkLose = false;

class car
{
	int iForPlayer;
	int line; 
public:

	void Line(int Line){line = Line;};
	void createCar();
	bool moveDown();
	void movePlayer();
	void createPlayer();
	
	
};

void car::createCar()
{

						                 box[0][2 + (line -1) *4] = 176 ;
		box[1][1 + (line -1) *4] = 176 ; box[1][2 + (line -1) *4] =  ' '; box[1][3 + (line -1) *4] = 176;
		box[2][1 + (line -1) *4] = ' ' ; box[2][2 + (line -1) *4] = 176 ; box[2][3 + (line -1) *4] = ' ';
		box[3][1 + (line -1) *4] = 176 ; box[3][2 + (line -1) *4] =  ' '; box[3][3 + (line -1) *4] = 176;
										 checkCars[2][2 + (line -1) *4] = true;

}

void car::createPlayer()
{
    	iForPlayer = 16;	

						                  box[16][2 + (line -1) *4] = 178 ;
		box[17][1 + (line -1) *4] = 178 ; box[17][2 + (line -1) *4] = ' ' ; box[17][3 + (line -1) *4] = 178;
		box[18][1 + (line -1) *4] = ' ' ; box[18][2 + (line -1) *4] = 178 ; box[18][3 + (line -1) *4] = ' ';
		box[19][1 + (line -1) *4] = 178 ; box[19][2 + (line -1) *4] = ' ' ; box[19][3 + (line -1) *4] = 178;
}
void car::movePlayer()
{
	if(GetAsyncKeyState(VK_LEFT)&& line !=1)
	{
		if(box[iForPlayer][2 + (line -2)*4] != ' '||box[iForPlayer ][1+(line-2)*4] !=' ')
			checkLose = true ;
		for (int i = iForPlayer+1; i < iForPlayer+4 && !checkLose; i++)
		{
			for (int j = 1; j < 4&& !checkLose; j++)
			{
				if(box[i][j +(line-2)*4] != ' ')
					checkLose = true;
			}
		}
		if(!checkLose)
		{
			swap(box[iForPlayer][ 2 + (line -2)*4],box[iForPlayer][2 + (line-1)*4]);
			for (int i = iForPlayer+1; i < iForPlayer+4 ; i++)
				{
					for (int j = 1; j < 4; j++)
					{
						swap(box[i][ j + (line -2)*4],box[i][j+(line -1)*4]);			
					}
				}


			line--;
		}



	}

	
	if(GetAsyncKeyState(VK_RIGHT)&& line !=3)
	{
		if(box[iForPlayer][2 + (line)*4] != ' '||box[iForPlayer][1+(line)*4] != ' ')
			checkLose = true ;
		for (int i = iForPlayer +1; i < iForPlayer+4 && !checkLose; i++)
		{
			for (int j = 1; j < 4&& !checkLose; j++)
			{
				if(box[i][j +(line)*4] != ' ')
					checkLose = true;
			}
		}
		if(!checkLose)
		{
			swap(box[iForPlayer][ 2 + (line)*4],box[iForPlayer][2 + (line-1)*4]);
			for (int i = iForPlayer+1; i < iForPlayer+4 ; i++)
				{
					for (int j = 1; j < 4; j++)
					{
						swap(box[i][ j + (line)*4],box[i][j+(line -1)*4]);			
					}
				}


			line++;
		}



	}

	if(GetAsyncKeyState(VK_UP)&&  iForPlayer !=4)
	{

		if(box[iForPlayer -1][2 + (line-1)*4] != ' ' || box[iForPlayer-1][ 1 + (line -1)*4] != ' ')
			checkLose = true;
		if(!checkLose)
		{
			//swap(box[iForPlayer][2+ (line-1)*4],box[iForPlayer -1][2 + (line-1)*4]);
				for (int i = 0; i < 4; i++)
				{
					for (int j = 1; j < 4; j++)
					{
						swap(box[iForPlayer + i][j + (line-1)*4],box[iForPlayer + i -1][j+ (line-1)*4]);
					}
				}

				iForPlayer--;
		}

	}

	
	if(GetAsyncKeyState(VK_DOWN)&&  iForPlayer !=16)
	{

		if(box[iForPlayer +4][2 + (line-1)*4] != ' ' || box[iForPlayer+4][ 1 + (line -1)*4] != ' ')
			checkLose = true;
		if(!checkLose)
		{
			//swap(box[iForPlayer][2+ (line-1)*4],box[iForPlayer -1][2 + (line-1)*4]);
				for (int i = 3; i >=0; i--)
				{
					for (int j = 1; j < 4; j++)
					{
						swap(box[iForPlayer + i][j + (line-1)*4],box[iForPlayer + i +1][j+ (line-1)*4]);
					}
				}

				iForPlayer++;
		}

	}
}

bool car::moveDown()
{
	for (int i = 2 ; i < 26; i++)
	{
	

		if(checkCars[i][2 + (line -1) *4])
		{
				if(i==24)
		{
			checkCars[24][2+ (line-1)*4] = false;
			box[22][2 +(line-1)*4] = ' ';
			for (int i = 23; i < 26; i++)
			{
				for (int j = 1; j < 4; j++)
				{
					box[i][j + (line-1)*4] = ' ';
				}
			}
			return false;
		}
			if(box[i+2][2 + (line -1)*4] != ' ')
			{
				checkLose = true;
				return false;
			}
			for(int j = 1 ; j < 4 ; j++){
			swap(box[i+1][j+ (line -1)*4],box[i+2][j + (line -1)*4]);
			swap(box[i+1][j+ (line -1)*4],box[i][j + (line -1)*4]);
			swap(box[i-1][j+ (line -1)*4],box[i][j + (line -1)*4]);
		
			}
			swap(checkCars[i+1][2+ (line -1)*4],checkCars[i][2 + (line -1)*4]);
			swap(box[i -2][ 2+ (line-1)*4],box[i-1][2 + (line-1)*4]);
			return true;
		}
	}



}
void show();
bool checkLineEmpty(int line);
int score = 0;
int main()
{
	int Line ;
	srand(time(0));
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			checkCars[i][j] = false;
			box[i][j] = ' ';
		}
	}
	int delay = 0 ;
	car car1;
	car player;
	player.Line(2);
	player.createPlayer();

	car car2;
	bool checkMoveCar1 = false;
	bool checkMoveCar2 = false;
	int i = 0 ;
	while (true)
	{
		if(delay !=8)
		delay++;
		if(checkLose){
			gotoXY(21,20);
				cout<<"You Lose";
				break;
		}

		show();
		
			if(!checkMoveCar1 && delay == 8)
			{
				Line = rand()%3 +1 ;
				if(checkLineEmpty(Line)){
					score++;
					car1.Line(Line );
					car1.createCar();
					checkMoveCar1 = true;
				}
			}
		if(checkMoveCar1)
			checkMoveCar1 = car1.moveDown();
			if(!checkMoveCar2)
			{
					Line = rand()%3 +1 ;
					if(checkLineEmpty(Line)){
					car2.Line(Line);
					car2.createCar();
					checkMoveCar2 = true;}
			}
		if(checkMoveCar2)
			checkMoveCar2 = car2.moveDown();

		player.movePlayer();
	if(score == 20)
		Sleep(1);
		else
		Sleep(100 - 5*score);
		
		clearScreen();

	}

}

void show()
{
	for (int i = 4; i <  23; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			cout<<box[i][j];
		}
		cout<<endl;
		
	}
	gotoXY(X +1,Y +1);
			cout<<"Score = "<<score*5;
}




bool checkLineEmpty(int line)
{

	for (int i = 2; i < 26; i++)
	{
		if(checkCars[i][2 + (line -1) *4])
			return false;
	}

	return true;



}