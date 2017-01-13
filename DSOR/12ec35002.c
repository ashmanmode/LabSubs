//Tic Tac Toe
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define maxsiz 1000000
#define F first
#define S second
#define fr(i,k,n) for(int i = k ; i < n ; i++ )
typedef unsigned long long int ull;

int size_TT = 3 ;

char** input_board()
{
	char board[3][3];
	char x ;
	fr(i,0,size_TT)
	{
		scanf("%c%c%c",&board[i][0],&board[i][1],&board[i][2]);
	}
	printf("%s\n","hdfsbvhjd" );
	return board;
}

void print_board(char** board)
{
	printf("%s %d\n","printin",**board );
	fr(i,0,size_TT)
	{
		fr(j,0,size_TT)
			printf("%c ",*(*(board+i)+j)) ;
		printf("\n"); 
	}
}

int if_win(char** board, char mark)
{
    if ((board[0][0] == mark && board[0][1] == mark && board[0][2] == mark) ||
        (board[1][0] == mark && board[1][1] == mark && board[1][2] == mark) ||
        (board[2][0] == mark && board[2][1] == mark && board[2][2] == mark) ||
        (board[0][0] == mark && board[1][0] == mark && board[2][0] == mark) ||
        (board[0][1] == mark && board[1][1] == mark && board[2][1] == mark) ||
        (board[0][2] == mark && board[1][2] == mark && board[2][2] == mark) ||
        (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark))
        return 1;
    return 0;
}

bool if_over(char** board)
{
	bool over = true;
	fr(i,0,size_TT)
	{
		fr(j,0,size_TT)
		{
			if(board[i][j]=='-')
				over = false;
		}
	}
	return over;
}

int TTT_score(char** board, int depth)
{
	if(if_win(board,'X'))
		return 10-depth;
	if(if_win(board,'O'))
		return depth-10;
	return 0;
}

char** make_board(char** board,int x,int y,char mark)
{
	char new_board[3][3];
	fr(i,0,size_TT)
	{
		fr(j,0,size_TT)
		{
			new_board[i][j] = board[i][j];
			if(i==x && j==y)
				new_board[i][j] = mark ;
		}
	}
	return new_board;
}

int TTT_PlayerX(char** board, int depth)
{

	if(if_win(board,'X'))
		return 10 - depth;
	else if(if_win(board,'O'))
		return depth - 10;

	//If game is already over
	if(if_over(board))
		return TTT_score(board,depth) ;

	//Iterating through all possible states
	int max_score = -1*INT_MAX  ;
	int max_i,max_j ; 
	int min_score = INT_MAX  ;
	int min_i,min_j;
	fr(i,0,size_TT)
	{
		fr(j,0,size_TT)
		{
			if(board[i][j]=='-')
			{
				if(depth%2==0)
				{
					char** new_board = make_board(board,i,j,'X');
					int score = TTT_PlayerX(new_board,depth+1);
					if(score > max_score)
					{
						max_score = score ;
						max_i = i ;
						max_j = j ;
					}
				}
				else
				{
					char** new_board = make_board(board,i,j,'O');
					int score = TTT_PlayerX(new_board,depth+1);
					if(score < min_score)
					{
						min_score = score ;
						min_i = i ;
						min_j = j ;
					}
				}
			}

		}
	}
	
	if(depth==0)
		print_board(make_board(board,max_i,max_j,'X'))  ;
	if(depth%2==0)
		return max_score;
	else
		return min_score;
}

int main()
{
	printf("Enter the current board config\n");
	printf("Fill With X/O and - for blan\n");
	printf("Assume that player X have the next chance\n");

	char** board = input_board();
	print_board(&board);

	printf("\nNext Move ----> \n\n");
	TTT_PlayerX(board,0);

	return 0;
}