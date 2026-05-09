all: clean src/app.cpp Engine.o Window.o Main.o
	g++ Main.o Engine.o Window.o -o main.exe -lgdi32
	./main.exe
	make clean

Main.o: src/app.cpp
	g++ -o Main.o -c src/app.cpp -lgdi32

Engine.o: src/Engine.cpp
	g++ -o Engine.o -c src/Engine.cpp -lgdi32

Window.o: src/Window.cpp
	g++ -o Window.o -c src/Window.cpp -lgdi32

clean:
	rm -f Engine.o
	rm -f Window.o
	rm -f Main.o