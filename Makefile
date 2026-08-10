main.o:
	gcc main.c -c

game: main.o util.o
	gcc main.o util.o -o game

run: game
	./game

util.o:
	gcc util.c -c

clean:
	rm main.o util.o game