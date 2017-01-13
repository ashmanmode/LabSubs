//Plot the data 
#include <bits/stdc++.h>
#include <string>
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

int main(const int argc, char ** argv)
{
    if(argc < 2)
        return 1;
    const int n = atoi(argv[1]); //Number of elements
    const int m = atoi(argv[2]); //Number of times sort is run
	// cout << "Plotting results " << endl;

	string exec = "gnuplot -p -e \"set term png;set output 'results/graph"+to_string(n)+"-"+to_string(m)+".png';";
	string title = "set title 'Results with mergeSort & alt-mergerSort\nNo of Elements = "+ std::to_string(n) +" and M = " + std::to_string(m) + "';set xlabel 'No. of threads';set ylabel 'Execution Time';";
	string plotter1 = "plot 'tmp/result.txt' using 1:2 title 'mergeSort' with lp,";
	string plotter2 = "'tmp/result.txt' using 1:3 title 'alt-mergerSort' with lp\"";
	
	system((exec + title + plotter1 + plotter2).c_str());
	// cout << "Graph Stored" << endl ;   
	return 0;
}