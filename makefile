all: program
sorter: sorter_thread.c mergesort.c sorter_thread.h
	gcc -g -Wall sorter_thread.c mergesort.c sorter_thread.h -o sorter -pthread
mergesort: mergesort.c sorter.c sorter.h
	gcc -g -Wall mergesort.c sorter.c sorter.h -o mergesort -pthread
d_sorter: sorter.c mergesort.c sorter.h
	gcc -g -Q -v -Wall sorter.c mergesort.c sorter.h -o sorter -pthread
clean:
	rm -rf sorter mergesort *.o
