CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra
OBJS := brick_game/tetris/out/frontend.o brick_game/tetris/out/main.o  brick_game/tetris/out/fsm_matrix.o brick_game/tetris/out/logic.o 
TESTS:= s21_tests/*.c
LOGIC:= brick_game/tetris/src/logic.c brick_game/tetris/src/fsm_matrix.c
LDFLAGS:= -lcheck -lcheck_pic -pthread -lm -lsubunit 
OBJL:= out/fsm_matrix.o out/logic.o 
OBJL_COV:= out/fsm_matrix_coverage.o out/logic_coverage.o 
OBJSEL:= out/frontend.o out/main.o
TTRSPATH := ./brick_game/tetris
GCOV_FLAGS := -fprofile-arcs -ftest-coverage -lgcov
all: clean tetris

install: tetris


# Создание дистрибутива
dist:
	tar -czvf tetris_game.tar.gz ./brick_game ./gui makefile README.md Doxyfile


run: clean tetris
	./build/tetris

tetris: out_folder build_folder build 

s21_tetris.a: $(OBJL)
	@echo "$(TTRSPATH)/$@ $^"
	ar rcs $(TTRSPATH)/$@ $^

build: $(OBJSEL) s21_tetris.a
	$(CC) $(CFLAGS) $(OBJSEL) -o build/tetris -lncurses -L./brick_game/tetris -l:s21_tetris.a 


out/%.o: gui/cli/%.c
	$(out_folder)
	$(CC) $(CFLAGS) -c $^ -o $@

out/%.o: brick_game/tetris/src/%.c  
	$(out_folder)
	$(CC) $(CFLAGS) -c $< -o $@

build_folder:
	mkdir -p build	

out_folder:
	mkdir -p out

out/%_coverage.o: brick_game/tetris/src/%.c  
	$(out_folder)
	$(CC) $(CFLAGS) -c $< -o $@ --coverage

test: $(TESTS) $(LOGIC)
	$(CC) $(CFLAGS) -o s21_tests.out $^ $(LDFLAGS) 

test_cov.out: $(TESTS) $(OBJL_COV)
	$(CC) $(CFLAGS) -o test_cov.out $^ $(LDFLAGS) $(GCOV_FLAGS)

dvi:
	doxygen Doxyfile
	open docs/rtf/refman.rtf

valgrind: 
	valgrind --tool=memcheck --leak-check=yes ./build/tetris

clang:
	cp ../materials/linters/.clang-format .
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \;
	
clang_check:
	cp ../materials/linters/.clang-format .
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -n {} \;

gcov_report: test_cov.out
	./$<
	-lcov --directory $(shell pwd) -c -o coverage.info 
	mkdir -p html
	genhtml -o html coverage.info
	open html/index.html

dependencies:
	sudo apt-get install doxygen
	sudo apt-get install graphviz
	sudo apt-get install check
clean: uninstall
	rm -rf tetris_game.tar.gz
uninstall:
	rm -rf ./out docs brick_game/tetris/s21_tetris.a build ./out *.out *.gcda *.gcno high_score.txt coverage.info html

