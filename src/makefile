CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra -g
OBJS := brick_game/tetris/out/frontend.o brick_game/tetris/out/fsm_matrix.o 

all: clean tetris


build_folder:
	mkdir -p build	

out_folder:
	mkdir -p brick_game/tetris/out

tetris: out_folder build_folder build

build: $(OBJS) 
	$(CC) $(CFLAGS) $^ -o build/tetris -lncurses


brick_game/tetris/out/%.o: gui/cli/%.c
	$(out_folder)
	$(CC) $(CFLAGS) -c $^ -o $@

brick_game/tetris/out/%.o: brick_game/tetris/src/%.c  
	$(out_folder)
	$(CC) $(CFLAGS) -c $< -o $@






clean:
	rm -rf build brick_game/tetris/out