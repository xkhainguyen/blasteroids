CC=g++

VPATH=../libraries/fssimplewindow/glx:../libraries/ysglfontdata

TARGET= menu_test_script

BIN_DIR=../build/bin/

OBJ_DIR=../build/obj

OBJECTS = $(OBJ_DIR)/menu_test_script.o $(OBJ_DIR)/menu.o $(OBJ_DIR)/fsglxkeymap.o $(OBJ_DIR)/fsglxwrapper.o $(OBJ_DIR)/ysglfontdata.o ysglusefontbitmap.o

CFLAGS = -I ../libraries/fssimplewindow -I ../libraries/ysglfontdata

LFLAGS =  -lGLU -lGL -lm -lX11 -lXext

.DEFAULT_GOAL:= $(BIN_DIR)/$(TARGET)

.PHONY: clean

clean:
	rm -r ../build

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@  $^ $(LFLAGS)

$(OBJ_DIR)/%.o:%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@
