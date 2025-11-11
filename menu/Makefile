CC=g++

VPATH=../libraries/fssimplewindow/glx:../libraries/ysglfontdata

TARGET= menu_test_script

OBJECTS = menu_test_script.o menu.o fsglxkeymap.o fsglxwrapper.o ysglfontdata.o ysglusefontbitmap.o

CFLAGS = -DGLX -I ../libraries/fssimplewindow -I ../libraries/ysglfontdata

LFLAGS =  -lGLU -lGL -lm -lX11 -lXext

.DEFAULT_GOAL:= $(TARGET)

.PHONY: clean

clean:
	rm *.o
	rm $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@  $^ $(LFLAGS)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@