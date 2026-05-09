all: clean src/app.cpp Engine.o Window.o Main.o
	g++ Main.o Engine.o Window.o -o main.exe -ld3d11 -ldxgi -ld3dcompiler
	./main.exe
	make clean

Main.o: src/app.cpp
	g++ -o Main.o -c src/app.cpp -ld3d11 -ldxgi -ld3dcompiler

Engine.o: src/Engine.cpp
	g++ -o Engine.o -c src/Engine.cpp

Window.o: src/Window.cpp
	g++ -o Window.o -c src/Window.cpp -ld3d11 -ldxgi -ld3dcompiler

clean:
	rm -f Engine.o
	rm -f Window.o
	rm -f Main.o