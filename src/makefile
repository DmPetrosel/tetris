CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra -g
OBJS := brick_game/tetris/out/frontend.o brick_game/tetris/out/fsm_matrix.o brick_game/tetris/out/logic.o  brick_game/tetris/out/main.o
TESTS:= s21_tests/*.c
LOGIC:= brick_game/tetris/src/logic.c brick_game/tetris/src/fsm_matrix.c
LDFLAGS:= -lcheck -lcheck_pic -pthread -lm -lsubunit 

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

test: $(TESTS) $(LOGIC)
	$(CC) $(CFLAGS) -o s21_tests.out $^ $(LDFLAGS) 

valgrind: 
	valgrind --tool=memcheck --leak-check=yes ./build/tetris

clang:
	cp ../materials/linters/.clang-format .
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \;
	
clang_check:
	cp ../materials/linters/.clang-format .
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -n {} \;

clean:
	rm -rf build brick_game/tetris/out