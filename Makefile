WARNING = -Wall -Wextra -Wpedantic -Wno-unused-result -Wno-all
CFLAGS = -std=c99 -O2 $(WARNING) -pipe -ggdb
LDLIBS = -lraylib -lGL -lm -lX11 -lpthread -ldl -lrt

LDFLAGS = #-static
PREFIX = /usr/local/bin
NAME = war
OUTDIR = .build
OBJ = \
      $(OUTDIR)/main.o \
      $(OUTDIR)/card.o \

all: $(NAME)

debug:
	tmux new-window "gdbserver :12345 $(OUTDIR)/$(NAME)"
	tmux selectw -t 1
	~/opt/gf/gf2 -x debug.gdb -c core

checkleak:
	valgrind --leak-check=full --show-leak-kinds=all --log-file=log $(OUTDIR)/$(NAME)

run: $(NAME)
	$(OUTDIR)/$(NAME) feeds


$(OUTDIR)/%.o: src/%.c
	@mkdir -p $(OUTDIR)
	$(CC) -c $(CFLAGS) -o $@ $<


$(NAME): $(OBJ)
	@echo "linking"
	@$(CC) -o $(OUTDIR)/$@ $^ $(LDLIBS) $(LDFLAGS)

release: $(NAME)
	strip $(OUTDIR)/$(NAME)

install: $(release)
	cp .build/$(NAME) $(PREFIX)/$(NAME)

uninstall:
	rm $(PREFIX)/$(NAME)

clean:
	rm -rf .build/ log core
