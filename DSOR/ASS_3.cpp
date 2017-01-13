//INFIX to POSTFIX
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

class Graph
{
	public:
		Graph(int n);
		void printAL();    //prints adjancency list
		void addEgde(int v, int w, bool directed); //for directed edge put directed = 1 
	private:
		vector< vector<int> > graph;
};

Graph::Graph(int n)
{
	vector<int> list;
	fr(i,0,n)
		graph.pb(list);
}

void Graph::printAL()
{
	cout << "printing the Adjacency list " << endl ;
	for(int i = 0 ; i < graph.size() ;i++ )
	{
		cout << "v" << i << " - " ;
		for(int j = 0 ; j < graph[i].size() ; j++ )
			cout << graph[i][j] << " " ;
		cout << endl ;
	}
}

void Graph::addEgde(int v,int w,bool directed)
{
	if(directed == true)
		graph[v].pb(w);
	else
	{
		graph[v].pb(w);
		graph[w].pb(v);
	}
} 

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
	// cout << "Player A " << depth <<  endl ;
	// print_board(board);
	if(if_win(board,'X'))
	{
		cout << "A won " <<  10 - depth << endl ;
		return 10 - depth;
	}

	//If game is already over
	if(if_over(board))
	{
		cout << "Over at A " << TTT_score(board,depth) << endl;
		return TTT_score(board,depth) ;
	}

	//Iterating through all possible states
	int max_score = 0  ;
	vector< vector<char> > max_board ; 
	fr(i,0,size_TT)
	{
		fr(j,0,size_TT)
		{
			if(board[i][j]=='-')
			{
				// cout << "Types" << endl ;
				vector< vector<char> > new_board = make_board(board,i,j,'X');
				int score = TTT_PlayerY(new_board,depth+1);
				if(score > max_score)
				{
					max_score = score ;
					max_board.clear();
					max_board = make_board(board,i,j,'X');
				}
			}

		}
	}
	cout << "Max score " << max_score << endl ;
	print_board(max_board);
	return max_score;
}

int TTT_PlayerY(vector< vector<char> > board, int depth)
{
	// cout << "Player B " << depth << endl ;
	// print_board(board);
	if(if_win(board,'O'))
	{
		cout << "B won " <<  depth-10 << endl ;
		return depth-10;
	}

	//If game is already over
	if(if_over(board))
	{
		cout << "Over at B " << TTT_score(board,depth) <<  endl;
		return TTT_score(board,depth) ;
	}

	//Iterating through all possible states
	int min_score = INT_MAX  ;
	vector< vector<char> > min_board ;  
	fr(i,0,size_TT)
	{
		fr(j,0,size_TT)
		{
			if(board[i][j]=='-')
			{
				vector< vector<char> > new_board = make_board(board,i,j,'O');
				int score = TTT_PlayerX(new_board,depth+1);
				if(score < min_score)
				{
					min_score = score ;
					min_board.clear();
					min_board = make_board(board,i,j,'O');
				}
			}

		}
	}
	// print_board(min_board);
	return min_score;
}

int main()
{
	cout << "Enter the current board config" << endl;
	cout << "Fill With X/O and - for blank" << endl;
	cout << "Assume that player X have the next chance" << endl;

	vector< vector<char> > board = input_board();
	TTT_PlayerX(board,0);

	return 0;
}