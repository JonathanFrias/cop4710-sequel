# output directory
COMPILE_DIR := out

.PHONY: test clean

# compile the entire codebase.
all:
	mkdir -p $(COMPILE_DIR)
	cc src/sql.c   src/assert.c src/store.c src/commandHelpers.c src/retrieve.c -pedantic -Wall -Wno-unused-parameter -Wno-missing-braces -Wextra -Wuninitialized -g -std=gnu99 -o $(COMPILE_DIR)/sql

# Run this with 'make test', then './out/test'
test: src/test.c
	mkdir -p $(COMPILE_DIR)
	cc src/test.c src/assert.c src/store.c src/commandHelpers.c src/retrieve.c  -pedantic -Wall -Wno-unused-parameter -Wno-missing-braces -Wextra -Wuninitialized -g -std=gnu99 -o $(COMPILE_DIR)/test

clean:
	rm -rf out
