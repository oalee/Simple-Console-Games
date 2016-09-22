#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
const int size = 20;
char box[size][size];
bool checkMove[size][size] = {0};
int SnakeSize = 1;
bool flag = 0;

class body{
	int row,column;
public :
	void bodies(int i , int j ) { box[i][j] = char(219) ; row = i; column = j;};
	void face(int i, int j) {box[i][j] = 1;};
	int move(int &i, int &j,int defualt);
	int bodyLocatoin(){return row*100+column;};
	void deleteBody(){box[row][column] = ' ';};

};
body snake[50];
void SetColor(char bg,char fg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),bg*16+fg);
}



void random()
{
	while(1)
	{
		int x = rand()%(size*100+size);
		int row = x/100;
		int column = x%100;

		if( box[row][column] == ' ' && row != 0 && row != size -1 && column !=0 && column != size -1)
		{
			box[row][column] = char(219) ;
			break;
		}
	}
	while(1)
	{
		int x = rand()%(size*100+size);
		int row = x/100;
		int column = x%100;

		if( box[row][column] == ' ' && row != 0 && row != size -1 && column !=0 && column != size -1)
		{
			box[row][column] = char(234) ;
			break;
		}
	}
}



int body::move(int &i, int &j,int defualt)
{
	if(defualt == 8)
	{
		if(i==0)
			return -1;
		if(box[--i][j] != char(219) && box[i][j] !=char(234) )
		{
			checkMove[1+i][j] = 1 ;

				swap(box[i+1][j],box[i][j]);


		}
		else if(box[i][j] == char(219))
		{
			
			snake[0].deleteBody();
			checkMove[1+i][j] = 1 ;
			box[i][j] = 1;
			flag = 1;

		}

		else if(box[i][j] == char(234))
			return -1;

		return 8;
	}
	if(defualt == 2)
	{
		if (i==size-1)
			return -1;

		if(box[++i][j] != char(219) && box[i][j] !=char(234))
		{
			checkMove[i-1][j] = 1;

				swap(box[i-1][j],box[i][j]);

		}
		else if(box[i][j] == char(234))
			return -1;
		else
		{
		
			snake[0].deleteBody();
			checkMove[i-1][j] = 1;
			box[i][j] = 1;
			flag = 1;
		}
		return 2;
	}
	if(defualt==6)
	{
		if(j==size -1)
			return -1;

		if(box[i][++j] != char(219) && box[i][j] !=char(234) )
		{
			checkMove[i][j-1] = 1;
			swap(box[i][j-1],box[i][j]);

		}
		else if(box[i][j] == char(234))
			return -1;
		else
		{
			
			snake[0].deleteBody();
			checkMove[i][j-1] = 1;
			box[i][j] = 1;
			flag = 1;
		}
		return 6;
	}
	if(defualt ==4)
	{
		if (j==0)
			return -1;
		if(box[i][--j] != char(219) && box[i][j] !=char(234) )
		{
			checkMove[i][j+1] = 1;
			swap(box[i][j+1],box[i][j]);

		}
		else if(box[i][j] == char(234))
			return -1;
		else
		{
			
			snake[0].deleteBody();
			checkMove[i][j+1] = 1;
			box[i][j] = 1;
			flag = 1;
		}
		return 4;
	}
	return 0;

}
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



void show()
{
	for(int i = 0 ; i < size ; i++)
	{
		for(int j = 0 ; j < size ; j++)
		{
			/*if(checkMove[i][j] == 1)
			cout<<"1";
			else
			cout<<"0";*/
			if(box[i][j] == char(234))
				SetColor(12,0);
			cout<<box[i][j];
				if(box[i][j] == char(234))
				SetColor(0,15);
		}
		cout<<char(219);

			cout<<endl;
	}
	for(int i = 0 ; i <= size ; i++)
	cout<<char(219);
	cout<<endl;
	gotoXY(size*2,10);
		cout<<"Score = "<<(SnakeSize-1)*5<<endl;
		//gotoXY(size*2,8);
		//cout<<"HighScore = "<<(*scores)._score<<endl;

}

int searchCheckMove()
{
	for(int i = 0 ; i < size ; i++)
		for(int j = 0 ; j < size ; j++)
			if(checkMove[i][j] == 1)
				return i*10+j;
	return -1;

}
int main()
{

	srand(time(0));
	for(int i = 0 ; i < size ; i++)
		for(int j = 0 ; j < size ; j++)
			box[i][j] = ' ';
	snake[0].face(size/2,size/2);	// snake's face :)

//	for(int i = 1 ; i < 5 ; i++)
	//	snake[i].bodies(size/2 + i,size/2);// set defualt snake position
	int i = size/2;
	int j = size/2;
	int defualt = 0;
	random();
	//score CurrentScore;
	//cout<<"Name ? ";
	char name[10];
	//CurrentScore.readFromFile("HighScore.txt");
	//cin>>name;

	//int index = CurrentScore.search(name);
	//(*(scores+ index))._score = 0 ;
	//strcpy((*(scores+index)).name,name);

	while(1)
	{

		show();
		int x = snake[0].move(i,j,defualt);
		defualt = x;
		if(GetAsyncKeyState(VK_UP))
			defualt = 8;
		if(GetAsyncKeyState(VK_DOWN))
			defualt = 2;
		if(GetAsyncKeyState(VK_LEFT))
			defualt = 4;
		if(GetAsyncKeyState(VK_RIGHT))
			defualt = 6;
		if( x == -1)
		{
		//	CurrentScore.saveToFile("HighScore.txt");
			system("color c");
			gotoXY(0,size+2);
			cout<<"You LoSE ! Press ESC for exiting ! \n";
			//&score::show;
			while(1){

			if(GetAsyncKeyState(VK_ESCAPE))
			break;
			}
			break;
		}
		if(flag ==1)
		{

			SnakeSize++;
			//scores[line]._score+=5;
			//&score::sort;
			random();
			flag = 0;
		}
		if(SnakeSize<110/2)
		Sleep(110 - SnakeSize*2);
		else
			Sleep(1);
		clearScreen();
	}




}
