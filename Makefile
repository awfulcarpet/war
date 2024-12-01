WARNING = -Wall -Wextra -Wpedantic -Wno-unused-result -Wno-all
CFLAGS = -std=c99 -O2 $(WARNING) -pipe -ggdb -Iinclude
LDLIBS = -lraylib -lGL -lm -lX11 -lpthread -ldl -lrt
EMCCFLAGS = lib/libraylib.a -s USE_GLFW=3 --shell-file minshell.html
PLATFORM ?= PLATFORM_DESKTOP

ifeq ($(PLATFORM),PLATFORM_WEB)
	CC=emcc
	LDLIBS = $(EMCCFLAGS)
	EXT = .html
endif

LDFLAGS = #-static
PREFIX = /usr/local/bin
NAME = war
OUTDIR = .build
OBJ = \
      $(OUTDIR)/main.o \
      $(OUTDIR)/card.o \

all: $(NAME)

checkleak:
	valgrind --leak-check=full --show-leak-kinds=all --log-file=log $(OUTDIR)/$(NAME)

run: $(NAME)
	$(OUTDIR)/$(NAME)

$(OUTDIR)/%.o: src/%.c
	@mkdir -p $(OUTDIR)
	$(CC) -c $(CFLAGS) -o $@ $< -D$(PLATFORM)


$(NAME): $(OBJ)
	@echo "linking"
	@$(CC) -o $(OUTDIR)/$(NAME)$(EXT) $^ $(LDLIBS) $(LDFLAGS)

release: $(NAME)
	strip $(OUTDIR)/$(NAME)

web-release: $(NAME)
	@mkdir -p pub
	mv -f .build/war.* pub/
	sed 's/war.js/pub\/war.js/g' pub/war.html > index.html

install: $(release)
	cp .build/$(NAME) $(PREFIX)/$(NAME)

uninstall:
	rm $(PREFIX)/$(NAME)

clean:
	rm -rf .build/ log core pub/ index.html
