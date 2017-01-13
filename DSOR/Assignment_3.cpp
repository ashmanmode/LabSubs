//Tic Tac Toe
/*
INPUT Sample : 
O-X
X--
XOO
OUTPUT SAMPLE:
Enter the current board config
Fill With X/O and - for blank
Assume that player X have the next chance

O - X 
X - - 
X O O 

Next Move ----> 

O - X 
X X - 
X O O 

RUN AS : ./a.out < inp.txt > out.txt
*/
#include <bits/stdc++.h>
using namespace std;

#define maxsiz 1000000
#define F first
#define S second
#define fr(i,k,n) for(int i = k ; i < n ; i++ )
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
#define printvect(a,n) fr(i,0,n) cout << a[i] << " " ;
#define point pair<int,int>
#define pii pair<int,int>
#define pib pair<int,bool>
#define arr vector<int> 
#define vectin(a,n) fr(i,0,n) { cin >> a[i] ; }
typedef unsigned long long int ull;

int TTT_PlayerY(vector< vector<char> > , int );
int TTT_PlayerX(vector< vector<char> > , int );

int size_TT = 3 ;

vector< vector<char> > input_board()
{
	vector< vector<char> > board;
	char x ;
	fr(i,0,size_TT)
	{
		vector<char> tmp(size_TT);
		fr(j,0,size_TT)
			cin >> tmp[j];
		board.pb(tmp);
	}
	return board;
}

void print_board(vector< vector<char> > board)
{
	fr(i,0,size_TT)
	{
		fr(j,0,size_TT)
			cout << board[i][j] << " " ;
		cout << endl; 
	}
}

int if_win(vector< vector<char> > board, char mark)
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

bool if_over(vector< vector<char> > board)
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

int TTT_score(vector< vector<char> > board, int depth)
{
	if(if_win(board,'X'))
		return 10-depth;
	if(if_win(board,'O'))
		return depth-10;
	return 0;
}

vector< vector<char> > make_board(vector< vector<char> > board,int x,int y,char mark)
{
	vector< vector<char> > new_board;
	fr(i,0,size_TT)
	{
		vector<char> tmp(size_TT);
		fr(j,0,size_TT)
		{
			tmp[j] = board[i][j];
			if(i==x && j==y)
				tmp[j] = mark ;
		}
		new_board.pb(tmp);
	}
	return new_board;
}

int TTT_PlayerX(vector< vector<char> > board, int depth)
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
					vector< vector<char> > new_board = make_board(board,i,j,'X');
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
					vector< vector<char> > new_board = make_board(board,i,j,'O');
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
	cout << "Enter the current board config" << endl;
	cout << "Fill With X/O and - for blank" << endl;
	cout << "Assume that player X have the next chance" << endl << endl;

	vector< vector<char> > board = input_board();
	print_board(board);

	cout << endl << "Next Move ----> " << endl << endl;
	TTT_PlayerX(board,0);

	return 0;
}