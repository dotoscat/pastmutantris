ALLEGRO5 = `pkg-config allegro-5 allegro_ttf-5 allegro_font-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 --libs --cflags`

SRC = src/*.cpp

clean-main-mingw:
	rm main-mingw

main-mingw:
	g++ -std=c++17 $(SRC) -mwindows -O2 -o main-mingw $(ALLEGRO5)

main-linux:
	g++ -std=c++17 $(SRC) -O2 -o main-linux $(ALLEGRO5)

main-debug:
	g++ -g $(SRC) $(ALLEGRO5) -o main-debug
