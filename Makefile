CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

TARGET = rowtate_solver
OBJS = main.o Grid.o Solver.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Grid.h Solver.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Grid.o: Grid.cpp Grid.h
	$(CXX) $(CXXFLAGS) -c Grid.cpp

Solver.o: Solver.cpp Solver.h Grid.h
	$(CXX) $(CXXFLAGS) -c Solver.cpp

clean:
	rm -f $(OBJS) $(TARGET)
