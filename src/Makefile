CC = g++ #-g
FLAGS = -Wall -Werror -Wextra --std=c++17 # -pedantic  -fsanitize=address
FLAGS_COV = -lgtest -pthread -lgcov -fprofile-arcs -ftest-coverage

.PHONY: all
all: gcov_report

.PHONY: lint
lint:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc
	clang-format -n *.h
	clang-format -n ./tests/*.cc
	rm .clang-format

.PHONY: gcov_report
gcov_report: test
	lcov --no-external -o ./coverage.info -c -d .
	lcov --remove ./coverage.info '*src/tests*' -o ./coverage.info
	genhtml -o ./report ./coverage.info
	open ./report/index.html
	rm coverage.info *.gcda *.gcno *.a *.o test

.PHONY: test
test: s21_matrix_oop.a
	$(CC) $(FLAGS) s21_matrix_oop.a s21_matrix_oop.cc ./tests/s21_matrix_oop_test.cc -o test $(FLAGS_COV)
	./test

.PHONY: s21_matrix_oop.a
s21_matrix_oop.a: o_files
	ar rcs ./s21_matrix_oop.a ./*.o
	ranlib ./s21_matrix_oop.a

.PHONY: o_files
o_files:
	$(CC) $(FLAGS) -c ./s21_matrix_oop.cc -o s21_matrix_oop.o

.PHONY: clean
clean:
	rm -fr ./report coverage.info *.gcda *.gcno *.a *.o test test.dSYM s21_matrix_oop
