# Make file variable
COMPILE_DIR := out

SRC := $(wildcard *.c)

# Run this with 'make test', then './out/test'
test: test.c
	mkdir -p $(COMPILE_DIR) #=> mkdir -p out
	cc $(SRC) -g -std=gnu99 -o $(COMPILE_DIR)/test #=> cc test.c -std=gnu99 -o out/test
