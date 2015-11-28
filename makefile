# output directory
COMPILE_DIR := out
SRC_FIlES := src/assert.c src/store.c src/commandHelpers.c src/retrieve.c 

.PHONY: test clean parse

# compile the entire codebase.
all:
	mkdir -p $(COMPILE_DIR)
	cc src/sql.c   src/assert.c src/store.c src/commandHelpers.c src/retrieve.c -pedantic -Wall -Wno-unused-parameter -Wno-missing-braces -Wextra -Wuninitialized -g -std=gnu99 -o $(COMPILE_DIR)/sql

# Run this with 'make test', then './out/test'
test: src/test.c
	mkdir -p $(COMPILE_DIR)
	cc src/test.c src/assert.c src/store.c src/commandHelpers.c src/retrieve.c  -pedantic -Wall -Wno-unused-parameter -Wno-missing-braces -Wextra -Wuninitialized -g -std=gnu99 -o $(COMPILE_DIR)/test

clean:
	rm -rf out/ sql.tab.h sql.tab.c lexer.h *.o  lex.yy.c trial
parse:
	mkdir -p $(COMPILE_DIR)
	
	bison -d sql.y -b $(COMPILE_DIR)/sql
	flex --header-file=$(COMPILE_DIR)/lexer.h --outfile=$(COMPILE_DIR)/lex.yy.c sql.l
	cc -o $(COMPILE_DIR)/trial $(COMPILE_DIR)/lex.yy.c sql.c -std=gnu99  $(SRC_FIlES)
