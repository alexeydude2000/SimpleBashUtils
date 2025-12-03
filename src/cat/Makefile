CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TARGET = s21_cat
SOURCES = s21_cat.c s21_cat_func.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all

style:
	clang-format --style=Google -n *.c *.h

stylef:
	clang-format --style=Google -i *.c *.h


e_test:
	@echo "=============================== flag e ==============================="
	@cat -e test/files/features.txt > test/result/cat_result_e
	@./s21_cat -e test/files/features.txt > test/result/s21_cat_result_e
	@diff -s test/result/cat_result_e test/result/s21_cat_result_e

b_test:
	@echo "=============================== flag b ==============================="
	@cat -b test/files/legacy.txt > test/result/cat_result_b
	@./s21_cat -b test/files/legacy.txt > test/result/s21_cat_result_b
	@diff -s test/result/cat_result_b test/result/s21_cat_result_b

n_test:
	@echo "=============================== flag n ==============================="
	@cat -n test/files/legacy.txt > test/result/cat_result_n
	@./s21_cat -n test/files/legacy.txt > test/result/s21_cat_result_n
	@diff -s test/result/cat_result_n test/result/s21_cat_result_n

s_test:
	@echo "=============================== flag s ==============================="
	@cat -s test/files/legacy.txt > test/result/cat_result_s
	@./s21_cat -s test/files/legacy.txt > test/result/s21_cat_result_s
	@diff -s test/result/cat_result_s test/result/s21_cat_result_s

t_test:
	@echo "=============================== flag t ==============================="
	@cat -t test/files/legacy.txt > test/result/cat_result_t
	@./s21_cat -t test/files/legacy.txt > test/result/s21_cat_result_t
	@diff -s test/result/cat_result_t test/result/s21_cat_result_t

combo:
	@echo "=============================== combo! ==============================="
	@cat test/files/features.txt test/files/legacy.txt > test/result/cat_result_combo
	@./s21_cat test/files/features.txt test/files/legacy.txt > test/result/s21_cat_result_combo
	@diff -s test/result/cat_result_combo test/result/s21_cat_result_combo

combo+s:
	@echo "============================= combo + s =============================="
	@cat -s test/files/features.txt test/files/legacy.txt > test/result/cat_result_combo+s
	@./s21_cat -s test/files/features.txt test/files/legacy.txt > test/result/s21_cat_result_combo+s
	@diff -s test/result/cat_result_combo+s test/result/s21_cat_result_combo+s

combo+e:
	@echo "============================= combo + e =============================="
	@cat -e test/files/features.txt test/files/legacy.txt > test/result/cat_result_combo+e
	@./s21_cat -e test/files/features.txt test/files/legacy.txt > test/result/s21_cat_result_combo+e
	@diff -s test/result/cat_result_combo+e test/result/s21_cat_result_combo+e

combo+b:
	@echo "============================= combo + b =============================="
	@cat -b test/files/features.txt test/files/legacy.txt > test/result/cat_result_combo+b
	@./s21_cat -b test/files/features.txt test/files/legacy.txt > test/result/s21_cat_result_combo+b
	@diff -s test/result/cat_result_combo+b test/result/s21_cat_result_combo+b

combo+n:
	@echo "============================= combo + n =============================="
	@cat -n test/files/features.txt test/files/legacy.txt > test/result/cat_result_combo+n
	@./s21_cat -n test/files/features.txt test/files/legacy.txt > test/result/s21_cat_result_combo+n
	@diff -s test/result/cat_result_combo+n test/result/s21_cat_result_combo+n

combo+t:
	@echo "============================= combo + t =============================="
	@cat -t test/files/features.txt test/files/legacy.txt > test/result/cat_result_combo+t
	@./s21_cat -t test/files/features.txt test/files/legacy.txt > test/result/s21_cat_result_combo+t
	@diff -s test/result/cat_result_combo+t test/result/s21_cat_result_combo+t

all_test: b_test e_test n_test s_test t_test combo combo+e combo+s combo+t