//CCN Lab EXP1
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

double getE(double lambda)
{
	//Generate Random number between 0 and 1
	double u,E;
    u = (double)rand() / (double)RAND_MAX;
    E = (-1.0)*(log(u)/lambda) ;
    return E;
}

int main(int argc, char const *argv[])
{
	double lambda = 1.5 ;
	int n = 1000 ;

	//Get n values for E
	double E[n];
	fr(i,0,n)
		E[i] = getE(lambda) ;

	//Cumulative values for E
	double cumE[n];
	cumE[0] = E[0] ; 
	fr(i,1,n)
		cumE[i] = cumE[i-1]+E[i] ;
	cout << "TotalTime : " << cumE[n-1] << endl ;

	//Deviding this into slots
	int slots = 1000;
	double TimeSlot = cumE[n-1]/slots ;
	int packetsInSlot[slots];
	cout << "Length of TimeSlot : " << TimeSlot << endl ;
	int j = 0 ;
	fr(i,0,slots)
	{
		int count = 0 ;
		while(cumE[j] < (i+1)*TimeSlot)
		{
			j++ ;
			count++;
		}
		packetsInSlot[i] = count ;
	}

	//Finding packet frequency
	map<int,int> pdf;
	fr(i,0,slots)
	{
		if(pdf.find(packetsInSlot[i])==pdf.end())
			pdf[packetsInSlot[i]] = 1;
		else
			pdf[packetsInSlot[i]]++;
	}

	FILE *fp;
    fp = fopen("plot.txt", "w");
	for (std::map<int,int>::iterator it=pdf.begin(); it!=pdf.end(); ++it)
    	fprintf(fp, "%d %d \n", it->first,it->second);
    fclose(fp);
    
    system("gnuplot -p -e \"set term png;set output 'file.png';plot 'plot.txt' with lp\"");
	return 0;
}