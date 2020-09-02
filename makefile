CC = g++
CFLAGS = -Wall -std=c++17 -O2
EXEC_NAME = brainfuck
INCLUDES = -I/usr/include/
LIBS = -L/usr/lib/
OBJ_FILES = main.o
INSTALL_DIR = /usr/bin

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm $(OBJ_FILES)
	rm $(EXEC_NAME)

install:
	cp $(EXEC_NAME) $(INSTALL_DIR)
