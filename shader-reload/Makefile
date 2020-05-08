src = $(wildcard src/*.c) $(wildcard src/**/*.c)
obj = $(src:.c=.o)

CFLAGS = -Ofast -march=native -mtune=native -Iinclude
LDFLAGS = -lSDL2 -lGL -ldl

reload-demo: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) reload-demo
