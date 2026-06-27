all:
	make clean
	make main.exe
	./main.exe
	make clean

main.exe: src/app.cpp Texture.o Polygon.o Mesh.o Engine.o Window.o Camera.o
	g++ src/app.cpp Texture.o Polygon.o Mesh.o Engine.o Window.o Camera.o -o main.exe -lgdi32

Polygon.o: src/geometry/Polygon.cpp
	g++ -o Polygon.o -c src/geometry/Polygon.cpp

Mesh.o: src/geometry/Mesh.cpp
	g++ -o Mesh.o -c src/geometry/Mesh.cpp

Engine.o: src/Engine.cpp
	g++ -o Engine.o -c src/Engine.cpp
	
Texture.o: src/display/Texture.cpp
	g++ -I C:/msys64/mingw64/include/stb -o Texture.o -c src/display/Texture.cpp

Window.o: src/display/Window.cpp
	g++ -o Window.o -c src/display/Window.cpp -lgdi32

Camera.o: src/Camera.cpp
	g++ -o Camera.o -c src/Camera.cpp

clean:
	rm -f *.o