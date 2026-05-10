all:
	make clean
	make main.exe
	./main.exe
	make clean

main.exe: src/app.cpp Polygon.o PolygonList.o Mesh.o Engine.o Window.o
	g++ src/app.cpp Polygon.o PolygonList.o Mesh.o Engine.o Window.o -o main.exe -lgdi32

Polygon.o: src/geometry/Polygon.cpp
	g++ -I. -I'C:/msys64/ucrt64/include/' -o Polygon.o -c src/geometry/Polygon.cpp

PolygonList.o: src/geometry/PolygonList.cpp
	g++ -I. -I'C:/msys64/ucrt64/include/' -o PolygonList.o -c src/geometry/PolygonList.cpp

Mesh.o: src/geometry/Mesh.cpp
	g++ -I. -I'C:/msys64/ucrt64/include/' -o Mesh.o -c src/geometry/Mesh.cpp

Engine.o: src/Engine.cpp
	g++ -I. -I'C:/msys64/ucrt64/include/' -o Engine.o -c src/Engine.cpp

Window.o: src/display/Window.cpp
	g++ -o Window.o -c src/display/Window.cpp -lgdi32

clean:
	rm -f *.o