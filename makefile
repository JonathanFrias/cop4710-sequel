# Make file variable
COMPILE_DIR := out

# Run this with 'make test'
test: test.c
	mkdir -p $(COMPILE_DIR) #=> mkdir -p out
	cc test.c -g -std=gnu99 -o $(COMPILE_DIR)/test #=> cc test.c -std=gnu99 -o out/test
