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
int SnakeSize = 5;
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

void random()
{
	while(1)
	{
		int x = rand()%(size*1000+size);
		int row = x/1000;
		int column = x%1000;

		if( box[row][column] == ' ' && row != 0 && row != size -1 && column !=0 && column != size -1)
		{
			box[row][column] = char(219) ;
			break;
		}
	}
}



int body::move(int &i, int &j,int defualt)
{
	if(defualt == 8) // up
	{
		if(i==0)
			return -1;
		if(box[--i][j] != char(219))
		{
			checkMove[1+i][j] = 1 ;

			swap(box[i+1][j],box[i][j]);


		}
		else
		{
			for(int z = 1 ; z < SnakeSize ;z++)
				if(i*100+j == snake[z].bodyLocatoin() )
					return -1;
			snake[0].deleteBody();
			checkMove[1+i][j] = 1 ;
			box[i][j] = 1;
			flag = 1;

		}

		return 8;
	}
	if(defualt == 2) // down
	{
		if (i==size-1)
			return -1;

		if(box[++i][j] != char(219))
		{
			checkMove[i-1][j] = 1;

			swap(box[i-1][j],box[i][j]);

		}
		else
		{
			for(int z = 1 ; z < SnakeSize ;z++)
				if(i*100+j == snake[z].bodyLocatoin() )
					return -1;
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

		if(box[i][++j] != char(219))
		{
			checkMove[i][j-1] = 1;
			swap(box[i][j-1],box[i][j]);

		}
		else
		{
			for(int z = 1 ; z < SnakeSize ;z++)
				if(i*100+j == snake[z].bodyLocatoin() )
					return -1;
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
		if(box[i][--j] != char(219))
		{
			checkMove[i][j+1] = 1;
			swap(box[i][j+1],box[i][j]);

		}
		else
		{
			for(int z = 1 ; z < SnakeSize ;z++)
				if(i*100+j == snake[z].bodyLocatoin() )
					return -1;
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

			cout<<box[i][j];
		}
		cout<<char(219);

		cout<<endl;
	}
	for(int i = 0 ; i <= size ; i++)
		cout<<char(219);
	cout<<endl;
	gotoXY(size + size / 2,10);
	cout<<"Score = "<<SnakeSize*5 - 25<<endl;

}

int searchCheckMove()
{
	for(int i = 0 ; i < size ; i++)
		for(int j = 0 ; j < size ; j++)
			if(checkMove[i][j] == 1)
				return i*100+j;
	return -1;

}
int main()
{

	srand(time(0));
	for(int i = 0 ; i < size ; i++)
		for(int j = 0 ; j < size ; j++)
			box[i][j] = ' ';
	snake[0].face(size/2,size/2);	// snake's face :)

	for(int i = 1 ; i < 5 ; i++)
		snake[i].bodies(size/2 + i,size/2);// set defualt snake position
	int i = size/2;
	int j = size/2;
	int defualt = 0;
	int defualtBackUP = 0 ;
	random();
	while(1)
	{
		show();
		int x = snake[0].move(i,j,defualt);
		defualt = x;
		if(GetAsyncKeyState(VK_UP))
			if(defualtBackUP!=2)
			defualt = 8;
		if(GetAsyncKeyState(VK_DOWN))
			if(defualtBackUP != 8)
			defualt = 2;
		if(GetAsyncKeyState(VK_LEFT))
			if(defualtBackUP!=6)
			defualt = 4;
		if(GetAsyncKeyState(VK_RIGHT))
			if(defualtBackUP !=4)
			defualt = 6;
		defualtBackUP = defualt;
		if( x == -1)
		{
			gotoXY(size + size / 2 ,13);
			system("color c");
			cout<<"GAME OVER!";
			gotoXY(size + size / 2 ,14);
			cout<<"Press Enter to exit";
			char z;
			while(1){
				z = getch();
				if(z==13)
					return 0;
			}
		}
		if(flag ==1)
		{

			SnakeSize++;
			random();
		}


		for(int k = 1 ; k < SnakeSize &&  searchCheckMove() != -1 ; k++)
		{
			if(k == SnakeSize -1 && flag == 1)
			{
				flag = 0 ;
				snake[k].bodies(searchCheckMove()/100,searchCheckMove()%100);
				checkMove[(searchCheckMove()/100)][(searchCheckMove()%100)] = 0 ;
				break;
			}

			int row = snake[k].bodyLocatoin()/100 ;
			int column = snake[k].bodyLocatoin()%100;
			snake[k].deleteBody();
			snake[k].bodies(searchCheckMove()/100,searchCheckMove()%100);
			checkMove[(searchCheckMove()/100)][(searchCheckMove()%100)] = 0 ;

			if(k != SnakeSize -1)
				checkMove[row][column] = 1;

		}
		if (SnakeSize == 49 )
		{
			gotoXY(size + size/2 , 13);
			cout<<"You Won!\nPress Enter to exit";
				char z;

			while(1){
				z = getch();
				if(z==13)
					return 0;
			}
		}

		if(SnakeSize <50)
		Sleep(100 - SnakeSize*2);
		else
			Sleep(1);
		clearScreen();
	}

	return 0;


}
