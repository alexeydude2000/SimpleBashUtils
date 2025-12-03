CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror
TARGET = s21_grep
SOURCES = s21_grep.c s21_grep_func.c

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


tests:
	@echo "======================+======= flag nan =============================="
	@grep Temple test/files/features.txt > test/result/grep_res
	@./s21_grep Temple test/files/features.txt > test/result/s21_grep_res
	@diff -s test/result/grep_res test/result/s21_grep_res

test_v: 
	@echo "=============================== flag v ==============================="
	@grep -v Temple test/files/features.txt test/files/legacy.txt > test/result/grep_res_v
	@./s21_grep -v Temple test/files/features.txt test/files/legacy.txt > test/result/s21_grep_res_v
	@diff -s test/result/grep_res_v test/result/s21_grep_res_v

test_n: 
	@echo "=============================== flag n ==============================="
	@grep -n Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/grep_res_n
	@./s21_grep -n Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/s21_grep_res_n
	@diff -s test/result/grep_res_n test/result/s21_grep_res_n

test_i: 
	@echo "=============================== flag i ==============================="
	@grep -i TEMPLE test/files/features.txt test/files/terry_davis.txt > test/result/grep_res_i
	@./s21_grep -i TEMPLE test/files/features.txt test/files/terry_davis.txt > test/result/s21_grep_res_i
	@diff -s test/result/grep_res_i test/result/s21_grep_res_i

test_c: 
	@echo "=============================== flag c ==============================="
	@grep -c Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/grep_res_c
	@./s21_grep -c Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/s21_grep_res_c
	@diff -s test/result/grep_res_c test/result/s21_grep_res_c

test_l: 
	@echo "=============================== flag l ==============================="
	@grep -l Terry test/files/features.txt test/files/legacy.txt test/files/terry_davis.txt > test/result/grep_res_l
	@./s21_grep -l Terry test/files/features.txt test/files/legacy.txt test/files/terry_davis.txt > test/result/s21_grep_res_l
	@diff -s test/result/grep_res_l test/result/s21_grep_res_l

test_e: 
	@echo "=============================== flag e ==============================="
	@grep -e Terry -e Temple test/files/features.txt test/files/terry_davis.txt > test/result/grep_res_e
	@./s21_grep -e Terry -e Temple test/files/features.txt test/files/terry_davis.txt > test/result/s21_grep_res_e
	@diff -s test/result/grep_res_e test/result/s21_grep_res_e

test_h: 
	@echo "=============================== flag h ==============================="
	@grep -h Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/grep_res_h
	@./s21_grep -h Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/s21_grep_res_h
	@diff -s test/result/grep_res_h test/result/s21_grep_res_h

test_s: 
	@echo "=============================== flag s ==============================="
	@grep -s qwerty test/files/features.txt > test/result/grep_res_s 2>/dev/null || true
	@./s21_grep -s qwerty test/files/features.txt > test/result/s21_grep_res_s 2>/dev/null || true
	@diff -s test/result/grep_res_s test/result/s21_grep_res_s

test_f: 
	@echo "=============================== flag f ==============================="
	@grep -f test/files/1.ptrn test/files/features.txt test/files/terry_davis.txt > test/result/grep_res_f
	@./s21_grep -f test/files/1.ptrn test/files/features.txt test/files/terry_davis.txt > test/result/s21_grep_res_f
	@diff -s test/result/grep_res_f test/result/s21_grep_res_f

test_o: 
	@echo "=============================== flag o ==============================="
	@grep -o T test/files/features.txt test/files/terry_davis.txt > test/result/grep_res_o
	@./s21_grep -o T test/files/features.txt test/files/terry_davis.txt > test/result/s21_grep_res_o
	@diff -s test/result/grep_res_o test/result/s21_grep_res_o

combo_iv: 
	@echo "============================= flags iv ==============================="
	@grep -iv Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/grep_res_iv
	@./s21_grep -iv Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/s21_grep_res_iv
	@diff -s test/result/grep_res_iv test/result/s21_grep_res_iv

combo_in: 
	@echo "============================= flags in ==============================="
	@grep -in Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/grep_res_in
	@./s21_grep -in Terry test/files/legacy.txt test/files/terry_davis.txt > test/result/s21_grep_res_in
	@diff -s test/result/grep_res_in test/result/s21_grep_res_in

all_test: tests test_v test_n test_i test_c test_l test_e test_h test_s test_f test_o combo_iv combo_in