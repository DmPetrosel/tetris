CC := gcc
CFLAGS := -I inc -std=c11 -Wall -Werror -Wextra -g
OBJS := out/fsm_matrix.o out/frontend.o

all: clean tetris
	
tetris: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) out/*.o tetris 	