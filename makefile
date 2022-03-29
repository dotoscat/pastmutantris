ALLEGRO5 = `pkg-config allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5 --libs --cflags`

SRC = src/*.cpp

main:
	g++ $(SRC) $(ALLEGRO5) -o main

main-debug:
	g++ -g $(SRC) $(ALLEGRO5) -o main-debug

clean:
	rm main
