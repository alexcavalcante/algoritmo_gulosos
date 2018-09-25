ifeq ($(OS), Windows_NT)
	TARGET = kruskal.exe
else
	TARGET = kruskal
endif

all: $(TARGET)

$(TARGET): kruskal.o
	 g++ -o $(TARGET) kruskal.o

kruskal.o: kruskal.cpp
	 g++ -std=c++14 -c ordenacao.cp

clean:
rm kruskal.o $(TARGET)