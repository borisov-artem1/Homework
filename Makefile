TARGET = ./main.out
TEST_TARGET = ./test_case.out
HDRS_DIR = project/include

SRCS = project/src/main.c \
	   project/src/read_write_data.c \
	   project/src/manage_data.c \
	   project/src/logic.c
TEST_SRCS = project/test/rw_case.c \
			project/test/test_case.c
.PHONY: all build rebuild check test memtest clean

all: clean check test memtest

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

build: $(TARGET)

rebuild: clean build

$(TEST_TARGET): $(TEST_SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TEST_TARGET) $(CFLAGS) $(TEST_SRCS)

test_build: $(TEST_TARGET)

test_case: $(TEST_TARGET)
	$(TEST_TARGET)

check:
	./run_linters.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) *.dat
