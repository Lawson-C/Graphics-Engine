all: clean src/app.cpp Engine.o Window.o  Main.o Mesh.o Polygon.o
	g++ Main.o Engine.o Window.o -o main.exe -lgdi32
	./main.exe
	make clean

Main.o: src/app.cpp
	g++ -o Main.o -c src/app.cpp -lgdi32

Engine.o: src/Engine.cpp
	g++ -o Engine.o -c src/Engine.cpp -lgdi32

Window.o: src/display/Window.cpp
	g++ -o Window.o -c src/display/Window.cpp -lgdi32

Polygon.o: src/geometry/Polygon.cpp
	g++ -o Polygon.o -c src/geometry/Polygon.cpp

Mesh.o: src/geometry/Mesh.cpp
	g++ -o Mesh.o -c src/geometry/Mesh.cpp

clean:
	rm -f *.o