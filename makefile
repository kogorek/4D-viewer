NAME = Tesseract

SOURCES = *.cpp

LIBS =  -lSDL2 -lSDL2_ttf

FLAGS = -Wall

STD = --std=c++11

all:
	g++ $(FLAGS) $(STD) $(SOURCES) $(LIBS) -o $(NAME)