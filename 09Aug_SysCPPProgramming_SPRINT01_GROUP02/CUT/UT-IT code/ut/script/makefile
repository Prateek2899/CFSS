CC = g++
CPPFLAGS = -c -g -Wall -lcppunit
LDFLAGS = -o
INC = ../inc
SRC = ../src
BIN = ../bin
OBJ = ../obj

all: $(BIN)/CFSSUT

$(BIN)/CFSSUT: $(OBJ)/Main.o $(OBJ)/CFSS_UT.o
		$(CC) $(LDFLAGS) $(BIN)/CFSSUT $(OBJ)/Main.o $(OBJ)/CFSS_UT.o -lcppunit

$(OBJ)/Main.o: $(SRC)/Main.cpp
		$(CC) $(CPPFLAGS) $(SRC)/Main.cpp -I $(INC) -lcppunit
		mv *.o $(OBJ)/

$(OBJ)/CFSS_UT.o: $(SRC)/CFSS_UT.cpp
		$(CC) $(CPPFLAGS) $(SRC)/CFSS_UT.cpp -I $(INC) -lcppunit
		mv *.o $(OBJ)/
				
clean:
		rm -f a.out Server Client
		rm -f $(BIN)/Server $(BIN)/Client
		rm -f $(OBJ)/*.o
		@echo "Cleaning Done!"
