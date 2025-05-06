CC         := gcc
CFLAGS     := -Wall -Wextra
FRAG_DIR   := fragments
FRAGMENTS  := $(wildcard $(FRAG_DIR)/*.html)
BUILDER    := build.out
INDEX      := index.html

.PHONY: all clean

all: $(INDEX)

$(BUILDER): build.c
	$(CC) $(CFLAGS) -o $(BUILDER) build.c

$(INDEX): $(BUILDER) $(FRAGMENTS)
	./$(BUILDER)

clean:
	rm -f $(BUILDER) $(INDEX)
