#include<iostream>
#include <cstdlib> 
#include<conio.h>
#include<time.h>
using namespace std;
int cpu(char a[3][3], int);
void ClearScreen();
int win(char a[3][3]);
int direction(int );
void show(char array[3][3],int ,int ,int );


int main()
{
	int input,playType,playerType = 0;
	int numberOfPlayedRounds ;
	char a[3][3];
	while (1)
	{
		for (int i = 0 ; i < 3 ; i++)
		for (int j = 0 ; j <3 ; j++)
			a[i][j] = ' ';
		cout<<"For single playing enter 1 , for multiplaying enter 2 \n";
		cin>>playType;
			while(1)
			{
				if(playType != 1 && playType != 2)
					cout<<"Try Again ! remember Only 2 or 1 \n";
				else 
					break;
				cin>>playType;
			}
		ClearScreen();
		numberOfPlayedRounds = 1 ;
		if(playType ==2)
			while(numberOfPlayedRounds!=10 && win(a)==0)
			{
				show(a,numberOfPlayedRounds,playType,playerType);
				while(1)
				{
					input = (int)_getch();
					input -= (int)'0';
					input = direction(input);
					if(a[input/10][input%10]!=' '&& input!=-1)
						cout<<"Error! The Place has been used ! Try Again ";
					if(input!=-1 && a[input/10][input%10] == ' ')
						break;
				}
				if(numberOfPlayedRounds%2==0)
					a[input/10][input%10] = 'X';
				else
					a[input/10][input%10] = 'O';
				if(win(a)==1)
				{
					ClearScreen();	
					show(a,numberOfPlayedRounds,playType,playerType);
					break;
				}
				numberOfPlayedRounds++;
				ClearScreen();
			}

		else
		{
			cout<<"You want to be first or Secound ? (1 = first & 2 = secound)\n ";
			cin>>playerType;
			while(1)
			{
				if(playerType != 1 && playerType != 2)
					cout<<"Try Again ! remember Only 2 or 1 \n";
				else break;
				cin>>playerType;
			}
			ClearScreen();
			while(numberOfPlayedRounds!=10)
			{
				if(playerType ==2 && numberOfPlayedRounds == 1 ){
					a[cpu(a,playerType)/10][cpu(a,playerType)%10] = 'O';
					numberOfPlayedRounds++;
					show(a,numberOfPlayedRounds,playType,playerType);
					ClearScreen();
				}

				show(a,numberOfPlayedRounds,playType,playerType);
				while(1)
				{

					input = (int)_getch();
					input -= (int)'0';
					input = direction(input);
					if(a[input/10][input%10]!=' '&& input!=-1)
						cout<<"\nError! The Place is used ! Try Again ";
					if(input!=-1 && a[input/10][input%10] == ' ')
						break;
				}
				if(playerType == 1)
				{
					a[input/10][input%10] = 'O';
					numberOfPlayedRounds++;
					if(numberOfPlayedRounds!=10 && win(a) == 0 ){
						a[cpu(a,playerType)/10][cpu(a,playerType)%10] = 'X';
						numberOfPlayedRounds++;
					}
				}
				else
				{
					a[input/10][input%10] = 'X';
					numberOfPlayedRounds++;
					if (win(a) == 0 ){
					a[cpu(a,playerType)/10][cpu(a,playerType)%10] = 'O';
					numberOfPlayedRounds++;
					}
				}
				if(win(a)==1)
				{
					ClearScreen();	
					show(a,numberOfPlayedRounds,playType,playerType);
					break;
				}
				
				
				ClearScreen();
			}

		}

		if(numberOfPlayedRounds==10 && win(a)==0)
		{
			ClearScreen();
			show(a,10,playType,playerType);
		}

		cout<<"Do you want to play Again ? (y/n)";
		char end;
		end = 'x';
		while(end !='y' && end !='n')
			cin>>end;
		if (end == 'n')
			return 0;
		ClearScreen();

	}
	
}
int cpu(char a[3][3], int playerType)
{
	char ch;
	if (playerType == 1)
		ch = 'X';
	else
		ch = 'O';
	int j = 1 ;
	for(int z = 2 ; z != 0 ; z--)
	{
		for(int i = 0 ; i < 3 ; i++)
		{
			if ( a[i][0] == a[i][j] && a[i][0] == ch && a[i][j+1] == ' ')
				return i*10 + j+1;
			if (a[i][0] == a[i][j+1] && a[i][0] == ch && a[i][j] == ' ')
				return i*10+j;
			if ( a[i][j] == a[i][j+1] && a[i][j] == ch && a[i][0] ==' ')
				return i*10;
		}
		for(int i = 0 ; i < 3 ; i++)
		{
			if ( a[0][i] == a[j][i] && a[0][i] == ch && a[j+1][i] == ' ')
				return (j+1)*10 + i ;
			if (a[0][i] == a[j+1][i] && a[0][i] == ch && a[j][i] == ' ')
				return j*10+i;
			if ( a[j][i] == a[j+1][i] && a[j][i] == ch && a[0][i] ==' ')
				return i;
		}
		if (a[0][0] == a[1][1] && a[0][0] == ch && a[2][2] ==' ')
			return 22;
		if (a[0][0] == a[2][2] && a[0][0] == ch && a[1][1] ==' ')
			return 11;
		if (a[1][1] == a[2][2] && a[1][1]== ch && a[0][0] ==' ')
			return 0;
		if (a[0][2] == a[1][1] && a[1][1] == ch && a[2][0] ==' ')
			return 20;
		if (a[0][2] == a[2][0] && a[0][2] == ch && a[1][1] ==' ')
			return 11;
		if(a[1][1] ==a[2][0] && a[1][1] == ch && a[0][2] ==' ')
			return 2;

		if (ch == 'O')
			ch = 'X';
		else
			ch = 'O';
	}
	srand((unsigned int)time(0));
	int x ;
	while (1)
	{
		x = rand()%23;
		if(a[x/10][x%10] == ' ')
			return x;
	}
}
void ClearScreen()
{
	system("CLS");
}
void column()
{
	for(int i = 1 ; i <= 15 ; i++)
	{
		if(i==1 )
			cout<<(char)221;
		else if(i!=1 && i%5==0)
			cout<<(char)219;
		else
			cout<<" ";

	}
	cout<<endl;
}
void columnWithValue(char array[3][3], int n)
{
	int z = 0;
	for(int i = 1 ; i <= 15 ; i++)
	{
		if(i==1 )
			cout<<(char)221;
		else if(i!=1 && i%5==0)
			cout<<(char)219;
		else if(i==3 || i == 8 || i == 13 )
			cout<<array[n][z++];
		else
			cout<<" ";


	}
	cout<<endl;


}
void raw()
{
	for(int i = 1 ; i <= 15 ; i++)
		cout<<(char)219;
	cout<<endl;

}
int direction(int numpad)
{
	switch(numpad)
	{
	case 1 : return 20;
	case 2 : return 21;
	case 3 : return 22;
	case 4 : return 10;
	case 5 : return 11;
	case 6 : return 12;
	case 7 : return 00;
	case 8 : return 01;
	case 9 : return 02;
	default : cout<<"\t\t\tError ! Please Try Again\n";
		return -1; 
	}
	return -1;

}
int win(char a[3][3]) // if win == return 1 ; else return 0;
{ 
	int t = 0 , j = 0 ;
	if (a[t][j]==a[t+1][j+1] && a[t][j]==a[t+2][j+2] && a[t][j]!=' ')
		return 1;
	if(a[0][2]==a[1][1] && a[0][2]==a[2][0] && a[0][2]!=' ')
		return 1;
	for (int i = 0 ; i < 3 ; i++)
	{
		if((int)a[i][0]==(int)a[i][1] && (int)a[i][0]==(int)a[i][2] && a[i][0]!=' ')
			return 1;
		if( (int)a[0][i]==(int)a[1][i] && (int)a[0][i]==(int)a[2][i] && a[0][i]!=' ')
			return 1;
	}
	return 0;

}
void show(char array[3][3], int numberOfPlayedRounds,int playType,int playerType)
{
	for(int i = 0 ; i < 3 ; i++)
	{
		if(i==0)
			raw();
		column();
		columnWithValue(array,i);
		column();
		raw();

	}
	if(playType == 2 && numberOfPlayedRounds != 10)
		cout<<"\t\t Player 1 = O \n\t\t Player 2 = X\n";
	else
	{
		if( win(array)== 0 && numberOfPlayedRounds != 10)
		{
			if(playerType ==1)
				cout<<"Your Turn ! Player = O\n ";
			else 
				cout<<"Your Turn ! Player = X \n" ;
		}
	}
	if(win(array)==1)
	{
		if(numberOfPlayedRounds%2==0 && playType == 2 )
			cout<<"\n\t\t\t Player 2 Won ! \n";
		 if (numberOfPlayedRounds%2 ==1 && playType == 2)
			cout<<"\n\t\t\t Player 1 Won ! \n";

		 if(playType == 1)
		 {
			 if(playerType == 1 )
			 {
				 if(numberOfPlayedRounds%2==0 )
					cout<<"\t\t\t\tYou Won ! \n";
				 else
					 cout<<"\t\t\t\tYou Lose ~! CPU won ! \n";
			 }
			 else
			 {
				 if(numberOfPlayedRounds%2 == 0 )
					 cout<<"\t\t\t\tYou Lose ~! CPU won ! \n";
				 else
					 cout<<"\t\t\t\tYou Won ! \n";

			 }
		 }
		
	}
	else
	{
		if(numberOfPlayedRounds%2==0 && playType == 2 )
			cout<<"Player 2 Turn ! , Please enter with numpads ";
		else if (numberOfPlayedRounds%2==1 && playType == 2 )
			cout<<"Player 1 Turn ! , Please enter with numpads ";

	}
	if(numberOfPlayedRounds==10 && win(array) == 0 )
		cout<<"\n\t\t\t Draw ! \n";
}
