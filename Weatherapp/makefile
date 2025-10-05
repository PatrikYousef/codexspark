# Kompilator
CC = gcc

# Standardflaggor
CFLAGS = -Wall -Wextra -Iinclude

# Försök hitta curl via pkg-config
CURL_CFLAGS := $(shell pkg-config --cflags libcurl 2>/dev/null)
CURL_LIBS   := $(shell pkg-config --libs libcurl 2>/dev/null)

# Om pkg-config misslyckas, använd Homebrew path som fallback
ifeq ($(CURL_LIBS),)
    CURL_CFLAGS = -I/opt/homebrew/opt/curl/include
    CURL_LIBS = -L/opt/homebrew/opt/curl/lib -lcurl
endif

CFLAGS += $(CURL_CFLAGS)
LDFLAGS = $(CURL_LIBS)

# Källkodsfiler
SRC = src/main.c src/login.c src/utils.c src/weather.c src/cache.c src/cities.c src/cJSON.c


# Objektfiler
OBJ = $(SRC:src/%.c=build/%.o)

# Körbar fil
BIN = bin/weatherapp

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p bin
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build bin

run: all
	./bin/weatherapp
