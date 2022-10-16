CC = g++

CPPFLAGS = -c -g -Wall
LDFLAGS = -o
SVFLAGS = -v --tool=memcheck --leak-check=full --show-reachable=yes --log-file=$(BIN)/valserver
CVFLAGS = -v --tool=memcheck --leak-check=full --show-reachable=yes --log-file=$(BIN)/valclient


INC = ../inc
SRC = ../src
BIN = ../bin
OBJ = ../obj


all: $(BIN)/Server $(BIN)/Client

$(BIN)/Server: $(OBJ)/MainServer.o $(OBJ)/common.o $(OBJ)/logger.o
	$(CC) $(LDFLAGS) $(BIN)/Server $(OBJ)/MainServer.o $(OBJ)/common.o $(OBJ)/logger.o

$(OBJ)/MainServer.o: $(SRC)/MainServer.cpp
	$(CC) $(CPPFLAGS) $(SRC)/MainServer.cpp -I $(INC)
	mv *.o $(OBJ)/

$(OBJ)/common.o: $(SRC)/common.cpp
	$(CC) $(CPPFLAGS) $(SRC)/common.cpp -I $(INC)
	mv *.o $(OBJ)/

$(BIN)/Client: $(OBJ)/MainClient.o $(OBJ)/common.o $(OBJ)/logger.o
	$(CC) $(LDFLAGS) $(BIN)/Client $(OBJ)/MainClient.o $(OBJ)/common.o $(OBJ)/logger.o

$(OBJ)/MainClient.o: $(SRC)/MainClient.cpp
	$(CC) $(CPPFLAGS) $(SRC)/MainClient.cpp -I $(INC)
	mv *.o $(OBJ)/

$(OBJ)/logger.o: $(SRC)/logger.cpp
	$(CC) $(CPPFLAGS) $(SRC)/logger.cpp -I $(INC)
	mv *.o $(OBJ)/

valgrindserver:
	valgrind $(SVFLAGS) $(BIN)/Server 127.0.0.1 4005 
	mv valserver $(BIN)/
valgrindclient:
	valgrind $(CVFLAGS) $(BIN)/Client 127.0.0.1 4005 
	mv valclient $(BIN)/


clean:
	rm -f a.out Server Client
	rm -f $(BIN)/Server $(BIN)/Client
	rm -f $(OBJ)/*.o
	@echo "Cleaning Done!"