CC = gcc
LDFLAGS = -lunp -lpthread
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
CFLAGS = -Wall -pthread

all: cli svr badcnt

cli: $(OBJ_DIR)/cli.o
	$(CC) $(OBJ_DIR)/cli.o -o $(BIN_DIR)/cli $(LDFLAGS)

svr: $(OBJ_DIR)/echoserver.o $(OBJ_DIR)/Utility.o
	$(CC) $(OBJ_DIR)/echoserver.o $(OBJ_DIR)/Utility.o -o $(BIN_DIR)/svr $(LDFLAGS)

badcnt: $(OBJ_DIR)/badcnt.o 
	$(CC) $(OBJ_DIR)/badcnt.o -o $(BIN_DIR)/badcnt $(LDFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -r $(BIN_DIR)/* 
