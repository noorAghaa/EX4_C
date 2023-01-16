
Wall = -Wall
CC = gcc



.PHONY : all clean 




all : graph 



graph : edges.o algo.o nodes.o main.o
	${CC} ${Wall} -o graph edges.o algo.o nodes.o main.o



main.o : main.c graph.h
	${CC} ${Wall} -c main.c


edges.o : edges.c graph.h edges.h
	${CC} ${Wall} -c edges.c


algo.o : algo.c graph.h algo.h
	${CC} ${Wall} -c algo.c



nodes.o : nodes.c graph.h nodes.h
	${CC} ${Wall} -c nodes.c



clean :
	rm -rf *.o graph 