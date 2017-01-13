#!make

build: msort-assignment.cc alt-msort-assignment.cc
	g++ -std=c++11 -O3 msort-assignment.cc -fopenmp -o msort
	g++ -std=c++11 -O3 alt-msort-assignment.cc -fopenmp -o alt-msort
	g++ -std=c++11 plotter.cpp -o plotter

run: ./msort ./alt-msort ./plotter
	for N in 1000 10000 100000 1000000 10000000 ; do \
		for M in 1 10 ; do \
			echo "N $$N M $$M" ;\
			echo > tmp/result.txt ; \
			for numThreads in `seq 1 24` ; do \
				./msort "$$N" "$$M" "$$numThreads" >> tmp/result.txt; \
				./alt-msort "$$N" "$$M" "$$numThreads" >> tmp/result.txt; \
			done ; \
			./plotter "$$N" "$$M" ;\
		done ;\
	done ;\
	