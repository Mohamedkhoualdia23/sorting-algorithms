CC = gcc
CFLAGS = -std=c11 -O2 -Wall -Wextra -Wpedantic
SRC = src/main.c src/sorting.c src/benchmark.c src/utils.c

ifeq ($(OS),Windows_NT)
    LDLIBS = -lpsapi
    EXE = sorting.exe
else
    LDLIBS =
    EXE = sorting
endif

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXE) $(LDLIBS)

test:
	$(CC) $(CFLAGS) tests/test_sorting.c src/sorting.c -o tests/test_sorting
	./tests/test_sorting

clean:
	rm -f sorting sorting.exe tests/test_sorting
