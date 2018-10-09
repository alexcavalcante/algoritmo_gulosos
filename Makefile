ifeq ($(OS), Windows_NT)
	TARGET = kruskal.exe
	TARGET2 = Prim.exe
	TARGET3 = dijkstra.exe
else
	TARGET = kruskal
	TARGET2 = Prim
	TARGET3 = dijkstra
endif

all: $(TARGET) $(TARGET2) $(TARGET3)

$(TARGET3): dijkstra.o
	 g++ -o $(TARGET3) dijkstra.o

dijkstra.o: dijkstra.cpp
	 g++ -std=c++14 -c dijkstra.cpp

$(TARGET2): Prim.o
	 g++ -o $(TARGET2) Prim.o

Prim.o: Prim.cpp
	 g++ -std=c++14 -c Prim.cpp

$(TARGET): kruskal.o
	 g++ -o $(TARGET) kruskal.o

kruskal.o: kruskal.cpp
	 g++ -std=c++14 -c ordenacao.cpp

clean:
rm kruskal.o $(TARGET) Prim.o $(TARGET2) dijkstra.o $(TARGET3)
