CXX=g++

build: gui.o
	$(CXX) -o gui gui.o `wx-config --libs`

gui.o: gui.cpp
	$(CXX) `wx-config --cxxflags` -c gui.cpp -o gui.o

clean:
	$(RM) program.o program

.PHONY: clean
