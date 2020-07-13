quirkle:	main.o	config.o	acoes.o	cores.o
	gcc	-o	quirkle	main.o		config.o	acoes.o	cores.o

main.o:	main.c
	gcc	-o	main.o	-c	main.c

config.o:	config.c
	gcc	-o	config.o	-c	config.c

acoes.o:	acoes.c
	gcc	-o	acoes.o	-c	acoes.c

cores.o:	cores.c
	gcc	-o	cores.o	-c	cores.c

all:	quirkle

run:	all
	./quirkle

clean:
	rm quirkle *.o

#clean:
#	rm main main.o config.o acoes.o cores.o

#run:	quirkle
#	./quirkle
