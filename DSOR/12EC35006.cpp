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

struct node
{
	char info;
	struct node *next;
};

class myStack
{
public:
	myStack();
	void push(int);
    char pop();
    bool isEmpty();
    char getTop();
private:
	node *top;
};

myStack::myStack()
{
	top = NULL ;
}

void myStack::push(int item)
{
    node *tmp;
    tmp = new (struct node);
    tmp->info = item;
    tmp->next = top;
    top = tmp;
}

char myStack::pop()
{
    node *tmp;
    char ret = 'a';
    if (top == NULL)
        cout<<"Stack is Empty"<<endl;
    else
    {       
        tmp = top;
        ret = tmp->info;
        top = top->next;
        free(tmp);
    }
    return ret;
}

bool myStack::isEmpty()
{
	if(top == NULL)
		return true;
	return false;
}

char myStack::getTop()
{
	return top->info;
}

int precedance(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
 
    case '^':
        return 3;
    }
    return -1;
}

bool operand(char c)
{
	if(c >= '0' && c <= '9')
		return true;
	if(c >= 'A' && c <= 'Z')
		return true;
	if(c >= 'a' && c <= 'z')
		return true;
	return false;
}

int main()
{
	string s;
	cin >> s ;

	myStack st;
	string out = "";
	fr(i,0,s.length())
	{
		if(operand(s[i]))
			out += s[i] ;
		else if(s[i] == '(')
			st.push(s[i]);
		else if(s[i] == ')')
		{
			while(!st.isEmpty() && st.getTop() != '(')
				out += st.pop();
			if(!st.isEmpty() && st.getTop() != '(')
				return -1;
			else
				st.pop();
		}
		else
		{
			while(!st.isEmpty() && precedance(st.getTop()) >= precedance(s[i]))
				out += st.pop();
			st.push(s[i]);
		}
	}
	while(!st.isEmpty())
		out += st.pop();
	cout  << out << endl ;
}