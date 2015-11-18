# output directory
COMPILE_DIR := out

# this is a variable that represents source files
# Files starting with 'test' are excluded from
# this list.
SRC := $(wildcard *[^test*].c)

# compile the entire codebase.
all: $(SRC)
	mkdir -p $(COMPILE_DIR) #=> mkdir -p out
	cc $(SRC) -g -std=gnu99 -o $(COMPILE_DIR)/sql #=> cc test.c -std=gnu99 -o out/test

# Run this with 'make test', then './out/test'
test:
	cc test.c -g -std=gnu99 -o $(COMPILE_DIR)/test
