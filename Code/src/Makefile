SOURCES = MainSFML.cpp Personnage.cpp formes.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
CXX = g++

%.o: %.cpp
	$(CXX) -std=c++0x -o $@ -c $< -Wall 

all: $(OBJECTS)
	$(CXX) -std=c++0x -o $(TARGET) $(OBJECTS) $(LIBS) -Wall

x: all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean: clean
	rm -rf $(TARGET)
