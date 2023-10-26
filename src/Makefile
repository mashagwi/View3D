PROJECT_NAME= s21_3dviewer
FLAGS= -Wall -Wextra -Werror
CHECKFL = $(shell pkg-config --cflags --libs check)
SRC = $(PROJECT_NAME)_parser.c $(PROJECT_NAME)_matrix.c
OS = $(shell uname)
ifeq ($(OS), Linux)
OPEN_CMD = xdg-open
else
OPEN_CMD = open
endif

all: $(PROJECT_NAME).a

install:
	mkdir ../build
	cd ../build; qmake ../src/S21_3D_View.pro && make 
	cp -r objects ../build

uninstall:
	rm -rf ../build* 

$(PROJECT_NAME).a: clean
	gcc -c $(FLAGS) $(PROJECT_NAME)_parser.c -o $(PROJECT_NAME).o
	gcc -c $(FLAGS) $(PROJECT_NAME)_matrix.c -o $(PROJECT_NAME)_matrix.o
	
	ar rc $(PROJECT_NAME).a $(PROJECT_NAME).o $(PROJECT_NAME)_matrix.o
	ranlib $(PROJECT_NAME).a


tests: $(PROJECT_NAME).a
	checkmk $(PROJECT_NAME).check > $(PROJECT_NAME)_test.c
	gcc $(FLAGS) $(SRC) $(PROJECT_NAME)_test.c $(PROJECT_NAME).a -o s21_test $(CHECKFL)
	./s21_test


gcov_report:
	checkmk $(PROJECT_NAME).check > $(PROJECT_NAME)_test.c
	gcc -c $(FLAGS) $(PROJECT_NAME)_test.c -o $(PROJECT_NAME)_test.o
	gcc $(FLAGS) --coverage $(PROJECT_NAME)_test.o $(SRC) -o s21_test $(CHECKFL)
	./s21_test
	lcov --no-external -d ./ --capture --output-file s21_test.info
	
	genhtml s21_test.info --output-directory report
	$(OPEN_CMD) ./report/index.html
	
dvi:
	cd docs/ && doxygen Doxyfile && open html/index.html & cd ..

dist: clean
	tar -zcf s21_smartcalc.tgz ./*
	
clean:
	rm -rf *.o *.a *.out s21_test $(PROJECT_NAME)_test.c *.gcda *.gcno report *.info *.gz *.tgz html latex ../build
	cd docs; rm -rf html latex

format: 
	clang-format -style=Google -i *.c *.h *.cpp 

style: 
	clang-format -style=Google -n *.c *.h *.cpp 
