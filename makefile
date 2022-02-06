ALLEGRO5 = `pkg-config allegro-5 allegro_primitives-5 --libs --cflags`

SRC = src/*.cpp

main:
	g++ $(SRC) $(ALLEGRO5) -o main

clean:
	rm main
