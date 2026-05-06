CC = gcc
CFLAGS = -Iincludes -Wall
LIBS = -lsqlite3

SRC = src/main.c src/auth.c src/database.c src/country.c src/region.c src/utils.c
OBJ = build/main.o build/auth.o build/database.o build/country.o build/region.o build/utils.o
TARGET = bin/countryapp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

build/auth.o: src/auth.c
	$(CC) $(CFLAGS) -c $< -o $@

build/database.o: src/database.c
	$(CC) $(CFLAGS) -c $< -o $@

build/country.o: src/country.c
	$(CC) $(CFLAGS) -c $< -o $@

build/region.o: src/region.c
	$(CC) $(CFLAGS) -c $< -o $@

build/utils.o: src/utils.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*.o bin/countryapp
