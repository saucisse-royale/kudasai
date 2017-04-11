CC = clang++ $(INCLUDES) $(STD) $(CPPFLAGS)
SHADERCC = ./bin/glslangValidator -V
STD = -std=c++1z
CPPFLAGS =

# include flags
INCLUDES = -I ./include/

# link flags
LINKS = `pkg-config --libs glfw3` -lpthread -ldl -L ./include
LD_LIBRARY_PATH= .

SRC = $(wildcard */*.cpp) $(wildcard */*/*.cpp)
SHADERSRC = $(wildcard src/shaders/*.frag) $(wildcard src/shaders/*.vert)
OBJ = $(SRC:.c = .o)

EXEC = kudasai

debug: CPPFLAGS += -Wall -g -O3
debug : all

release: CPPFLAGS += -O3
release: clean
release: all

install: release
	mv $(EXEC) bin

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LINKS)

%.o: %.c
	$(CC) $(STD) $(CPPFLAGS)  -c $< -o $@

shaders:
	rm -rf $(wildcard src/shaders/*.spv)
	$(SHADERCC) -c $(SHADERSRC)
	mv *.spv src/shaders

clean:
	rm -rf *.o $(EXEC)
