.POSIX:

include config.mk

SRC = $(shell find . -name '*.c' | grep -v test_*.c | grep -v example.c)
OBJ = ${SRC:.c=.o}

EXTRAFLAGS =

# default to error
all: simple_hash

%.o: %.c
	@echo COMPILING CC $< with extra flags \"${EXTRAFLAGS}\"
	@${CC} -g -c ${CFLAGS} $< ${EXTRAFLAGS} -o $@

simple_hash: ${OBJ}
	@echo "ERROR: unable to compile simple_hash on it's own as it is a library"
	exit 1

cleanobj:
	@echo cleaning objects and temporary files
	@find . -iname '*.o' -delete

clean: cleanobj
	@echo cleaning tests
	@rm -f test_sh
	@echo cleaning gcov guff
	@find . -iname '*.gcda' -delete
	@find . -iname '*.gcov' -delete
	@find . -iname '*.gcno' -delete


test: run_tests

run_tests: compile_tests
	@echo "\n\nrunning test_sh"
	./test_sh
	@echo "\n"

compile_tests: clean ${OBJ}
	@echo "compiling tests"
	@${CC} test_simple_hash.c -o test_sh ${LDFLAGS} ${OBJ}
	@make -s cleanobj

.PHONY: all clean cleanobj simple_hash test

