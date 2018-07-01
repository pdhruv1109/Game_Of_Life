Function's of Different Python Scripts (Same for every approach).

Wrapper.py - This script runs the ./a.out of serial code for 4 times with grid size 1000 x 1000 and 4 different step size like 256 , 512 , 1024 , 2048 and storing all this values in serial.txt file.

Parallel_Wrapper.py - This script runs the ./a.out of parallel code for 7 different cores (1,2,4,6,8,12,16) and for 4 different step size for every core (256 , 512 , 1024 , 2048 ) for fixed 1000 x 1000 grid and creating 7 .txt files for every core with each .txt file containing 4 execution time values for different step size (256 , 512 , 1024 , 2048 ).

plot_time.py - This script is used to plot execution time vs problem size graph for serial code and parallel code using different .txt files created earlier.

plot_speedup.py - This script is used to plot speedup vs problem size graph for parallel code (i.e. 1,2,4,6,8,12,16 core) using different .txt files created earlier.

karp_flatt.py - This script is used to plot karp flatt vs problem size graph for parallel code (i.e. 2,4,6,8,12,16 core) using different .txt files created earlier.

efficiency.py - This script is used to plot efficiency vs problem size graph for parallel code (i.e. 1,2,4,6,8,12,16 core) using different .txt files created earlier.


Order of Execution (Same for every approach) :-

gcc Serial_Naive.c -fopenmp  [Creates a.out file for serial code]

python2.7 Wrapper.py  [Uses a.out file and Creates serial.txt file]

gcc Parallel_Naive.c -fopenmp  [Creates a.out file for parallel code]

python2.7 Parallel_Wrapper.py  [Uses a.out file and creates 7 .txt file (1,2,4,6,8,12,16 cores)]

python2.7 plot_time.py  [plot the graph of execution time vs Problem size]

python2.7 plot_speedup.py  [plots the graph of speedup vs problem size]

python2.7 karp_flatt.py  [plots the graph of karp flatt vs problem size]

python2.7 efficiency.py  [plots the graph of efficiency vs problem size]
