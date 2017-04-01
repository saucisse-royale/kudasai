CC = clang++ $(INCLUDES) $(STD)
STD = -std=c++1z
CPPFLAGS =

# include flags
INCLUDES = -I ./include/

# link flags
LINKS = `pkg-config --libs glfw3` -lpthread -ldl -L ./include
LD_LIBRARY_PATH= .

SRC = $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJ = $(SRC:.c = .o)

EXEC = kudasai

debug: CPPFLAGS += -Wall -Wextra -pedantic -g -O2
debug : all

release: CPPFLAGS += -O2
release: clean
release: all

install: release
	mv $(EXEC) bin

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LINKS)

%.o: %.c
	$(CC) $(STD) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf *.o $(EXEC)
