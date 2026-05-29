all:
	make clean
	make main.exe
	./main.exe
	make clean

main.exe: src/app.cpp Texture.o Polygon.o PolygonList.o Mesh.o Engine.o Window.o
	g++ src/app.cpp Texture.o Polygon.o PolygonList.o Mesh.o Engine.o Window.o -o main.exe -lgdi32

Polygon.o: src/geometry/Polygon.cpp
	g++ -o Polygon.o -c src/geometry/Polygon.cpp

PolygonList.o: src/geometry/PolygonList.cpp
	g++ -o PolygonList.o -c src/geometry/PolygonList.cpp

Mesh.o: src/geometry/Mesh.cpp
	g++ -o Mesh.o -c src/geometry/Mesh.cpp

Engine.o: src/Engine.cpp
	g++ -o Engine.o -c src/Engine.cpp
	
Texture.o: src/display/Texture.cpp
	g++ -I C:/msys64/mingw64/include/stb -o Texture.o -c src/display/Texture.cpp

Window.o: src/display/Window.cpp
	g++ -o Window.o -c src/display/Window.cpp -lgdi32

clean:
	rm -f *.o