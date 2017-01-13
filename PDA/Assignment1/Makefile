#!make

build: 12EC35006.cc plotter.cpp
	g++ -std=c++11 -O3 12EC35006.cc -fopenmp -o spmv
	g++ plotter.cpp -o plotter
run: ./spmv ./plotter
	for i in `seq 1 4` ; do \
		echo "Mat$$i" > tmp/result_"$$i".txt ; \
		for numThreads in `seq 1 24` ; do \
			echo "Running $$numThreads threads" ; \
			./spmv matrices/mat"$$i".bin "$$numThreads" 100 1 >> tmp/result_"$$i".txt ; \
			./spmv matrices/mat"$$i".bin "$$numThreads" 100 2 >> tmp/result_"$$i".txt ; \
			./spmv matrices/mat"$$i".bin "$$numThreads" 100 3 >> tmp/result_"$$i".txt ; \
		done ; \
		./plotter < tmp/result_"$$i".txt ; \
	done

