#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

using namespace std;

double getWallTime()
{
    struct timeval time;
    if(gettimeofday(&time, NULL))
	return 0;
    double wallTime = (double)time.tv_sec + (double)time.tv_usec * 0.000001;
    return wallTime;
}

void setUpThreads(const int numThreads)
{
    omp_set_num_threads(numThreads);
}

// y = y + A * x
void multiply(const vector<int> & rowPtr,
	const vector<int> & colInd,
	const vector<double> & nnz,
	const vector<double> & x,
	vector<double> & y,
	const int numThreads,
    const int s)
{
    int n = x.size();    
    if(numThreads==1)
    {
        for(int i=0;i<n;i++)
            for(int j=rowPtr[i];j<rowPtr[i+1];j++)
                y[i] += nnz[j]*x[colInd[j]];
    }
    else
    {
        if(s==2) //Dynamic
        {
            #pragma omp parallel for schedule(dynamic) num_threads(numThreads) 
            for(int i=0;i<n;i++)
                for(int j=rowPtr[i];j<rowPtr[i+1];j++)
                    y[i] += nnz[j]*x[colInd[j]];
        }
        else if(s==3) //Guided
        {
            #pragma omp parallel for schedule(guided) num_threads(numThreads) 
            for(int i=0;i<n;i++)
                for(int j=rowPtr[i];j<rowPtr[i+1];j++)
                    y[i] += nnz[j]*x[colInd[j]];
        }
        else //Static
        {
            #pragma omp parallel for schedule(static) num_threads(numThreads) 
            for(int i=0;i<n;i++)
                for(int j=rowPtr[i];j<rowPtr[i+1];j++)
                    y[i] += nnz[j]*x[colInd[j]];
        }  
    } 
}


void populateVectors(const size_t numRows,
		const size_t numNnz,
		vector<double> & nnz,
		vector<double> & x)
{
    //Intialize random number generator
    random_device rd;
    mt19937 e2(rd());
    uniform_real_distribution<> dist(-1.0, 1.0);
    
    //Populate vector nnz with random numbers
    nnz.resize(numNnz);
    for(size_t i = 0; i < numNnz; ++i)
    {
	nnz[i] = dist(e2);
    }

    //Populate vector x with random numbers
    x.resize(numRows);
    for(size_t i = 0; i < numRows; ++i)
    {
	x[i] = dist(e2);
    }
    
    return;
}

bool testCorrectness(const vector<int> & rowPtr,
	const vector<int> & colInd,
	const vector<double> & nnz,
	const vector<double> & x,
	const int numThreads,
    const int schedule)
{
    bool correct(true);
    vector<double> y1(x.size(), 0.0);
    vector<double> y2(x.size(), 0.0);
    //Serial version
    multiply(rowPtr, colInd, nnz, x, y1, 1, schedule);
    //Parallel version
    multiply(rowPtr, colInd, nnz, x, y2, numThreads, schedule);
    //Compare
    const double reltol(1e-6), abstol(1e-9);
    for(size_t i = 0; i < y1.size(); ++i)
    {
    	if(fabs(y2[i] - y1[i]) > abstol + reltol * fabs(y1[i]))
    	{
    	    correct = false;
    	    break;
    	}
    }
    return correct;
}

double testPerformance(const vector<int> & rowPtr,
		const vector<int> & colInd,
		const vector<double> & nnz,
		const vector<double> & x,
		const int numSamples,
		const int numThreads,
        const int schedule)
{
    vector<double> y(x.size(), 0.0);
    //Start timer
    const double startTime = getWallTime();
    for(int i = 0; i < numSamples; ++i)
	multiply(rowPtr, colInd, nnz, x, y, numThreads, schedule);
    //End timer
    const double stopTime = getWallTime();
    const double timeElapsed = stopTime - startTime;
    return timeElapsed/(double)numSamples;
}


void read(istream & is,
	vector<int> & rowPtr,
	vector<int> & colInd)
{
    int rowPtrSize(0), colIndSize(0);
    
    is.read((char *)&rowPtrSize, sizeof(int));
    rowPtr.resize(rowPtrSize);
    for(int i = 0; i < rowPtrSize; ++i)
	is.read((char *)&rowPtr[i], sizeof(int));

    is.read((char *)&colIndSize, sizeof(int));
    colInd.resize(colIndSize);
    for(int i = 0; i < colIndSize; ++i)
	is.read((char *)&colInd[i], sizeof(int));
    
    return;
}

/* Usage :
   	Arg 1 :- Test Matrix location
	Arg 2 :- Number of threads
   	Arg 3 :- Number of samples
    Arg 4 :  Type of scheduling
   */
/* Scheduling Types :
    1: static
    2: dynamic
    3: guided
*/
int main(const int argc, const char ** argv)
{
    // Matrix A is stored in Row-Compressed Format
    vector<int> rowPtr; //Row Pointer array
    vector<int> colInd; //Column Index array
    vector<double> nnz; //Non Zeros
    vector<double> x; //Vector to be multiplied
    const int numThreads = argc > 2 ? atoi(argv[2]) : 1;
    const int numSamples = argc > 3 ? atoi(argv[3]) : 1000;
    const int schedule = argc > 4 ? atoi(argv[4]) : 3;

    //Read in the matrix A
    ifstream ifs(argv[1], ios::in | ios::binary);
    read(ifs, rowPtr, colInd);
    ifs.close();

    //Generate random numbers and populate nnz and x
    const size_t numRows(rowPtr.size() - 1);
    const size_t numNnz(colInd.size());
    populateVectors(numRows, numNnz, nnz, x); 

    if(numThreads > 1)  
    {
    	setUpThreads(numThreads);
    	//Results should match between serial and multi-threaded implementation
    	const bool correct = testCorrectness(rowPtr, colInd, nnz, x, numThreads, schedule);
    	if(!correct)
    	    cout << "Multi-threaded result does not match serial result" << endl;
    }
    
    const double perf = testPerformance(rowPtr, colInd, nnz, x, numSamples, numThreads, schedule);
    // cout << "File Name - N - NumNonZero - Threads - Performance" << endl ;
    cout << argv[1] << "\t" << rowPtr.size() << "\t" << colInd.size() << "\t" << numThreads << "\t" << schedule << "\t" << perf << endl;
    
    return 0;
}


//Try diferent scheduling algorithms for omp parallel for 