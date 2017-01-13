//Plot the data 
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

int main()
{
	string mat, name;
	cin >> mat ;
	cout << "Plotting graph for matrix : " << mat << endl;

	int n,nnz,threads,scheduling;
	double p ;
	vector<double> perf(3);
	
	FILE *fp;
    fp = fopen(("tmp/plot"+mat+".dat").c_str(), "w");
	fr(i,0,24)
	{
		fr(j,0,3)
		{
			cin >> name >> n >> nnz >> threads >> scheduling >> p ;
			perf[j] = p ; 
		}
		fprintf(fp, "%d %f %f %f\n", i+1 , perf[0], perf[1], perf[2]);
	}
	fclose(fp);

	string exec = "gnuplot -p -e \"set term png;set output 'results/file"+mat+".png';";
	string title = "set title 'Results on "+mat+"';set xlabel 'No. of threads';set ylabel 'Performance';";
	string plotter1 = "plot 'tmp/plot"+mat+".dat' using 1:2 title 'Static' with lp,";
	string plotter2 = "'tmp/plot"+mat+".dat' using 1:3 title 'Dynamic' with lp,";
	string plotter3 = "'tmp/plot"+mat+".dat' using 1:4 title 'Guided' with lp\"";
	
	system((exec + title + plotter1 + plotter2 + plotter3).c_str());
	cout << "Graph Stored at : file" << mat << ".png" << endl ;   
	return 0;
}