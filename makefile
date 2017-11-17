all: program
sorter: sorter.c mergesort.c sorter.h
	gcc -g -Wall sorter.c mergesort.c sorter.h -o sorter
mergesort: mergesort.c sorter.c sorter.h
	gcc -g -Wall mergesort.c sorter.c sorter.h -o mergesort
clean:
	rm -rf sorter mergesort *.o
