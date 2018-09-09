PROG_NAME = howdy
LIBS      = -lm
SRC_DIR   = src
LIB_DIR   = lib
BIN_DIR   = bin
OBJ_DIR   = obj
INC_DIR   = $(SRC_DIR)/include

CC        = gcc
CFLAGS    = -I$(INC_DIR)

DEPS = $(wildcard $(INC_DIR)/*.h)

_OBJ = main.o func.o
#_OBJ = $(wildcard $(SRC_DIR)/*.c) 
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
#OBJS = $(OBJ_DIR)/$(notdir $(_OBJ:.c=.o))

.PHONY: all clean $(PROG_NAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PROG_NAME): $(OBJS)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(BIN_DIR)/* $(OBJ_DIR)/*.o $(SRC_DIR)/*~ core $(INC_DIR)/*~
