SOURCES = formes.cpp Personnage.cpp MainSFML.cpp

OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
CXX = g++

%.o: %.cpp
	$(CXX) -std=c++14 -o $@ -c $< -Wall 

all: $(OBJECTS)
	$(CXX) -std=c++14 -o $(TARGET) $(OBJECTS) $(LIBS) -Wall

x: all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS)

superclean: clean
	rm -rf $(TARGET)
