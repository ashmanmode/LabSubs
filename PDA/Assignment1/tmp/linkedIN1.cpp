#include <bits/stdc++.h>
using namespace std;

int sol(vector<int> boy,vector<int> girl,int m)
{
	int max_index_boy = 0 ;
	int max_index_girl = 0 ;
	int sum = 0 ;
	for(int i=0;i<boy.size();i++)
	{
		sum += boy[i]*girl[i];
		if(abs(boy[i]) > abs(boy[max_index_boy]))
			max_index_boy = i;
		if(abs(girl[i]) > abs(boy[max_index_girl]))
			max_index_girl = i;
	}
	return sum+ m*max(abs(boy[max_index_boy]),abs(girl[max_index_girl]));
}

int main()
{
	int n,m;
	cin >> n ;
	vector<int> boy(n);
	vector<int> girl(n);
	for(int i=0;i<n;i++)
		cin >> boy[i];
	for(int i=0;i<n;i++)
		cin >> girl[i];
	cin >> m ;
	sol(boy,girl,m); 
	return 0;
}