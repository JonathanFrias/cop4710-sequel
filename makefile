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

trial: lex.yy.o sql.tab.o sql.o
	cc -o $(COMPILE_DIR)/trial $(COMPILE_DIR)/lex.yy.o $(COMPILE_DIR)/sql.tab.o $(COMPILE_DIR)/sql.o -std=gnu99

sql.o: sql.c 
	cc -c sql.c -o $(COMPILE_DIR)/sql.o

sql.tab.o: sql.tab.c
	cc -c $(COMPILE_DIR)/sql.tab.c -o $(COMPILE_DIR)/sql.tab.o

sql.tab.c: sql.y
	bison -d sql.y -b $(COMPILE_DIR)/sql

lex.yy.o: lex.yy.c 
	cc -c $(COMPILE_DIR)/lex.yy.c -o $(COMPILE_DIR)/lex.yy.o

lex.yy.c: sql.l sql.tab.c
	flex --header-file=$(COMPILE_DIR)/lexer.h --outfile=out/lex.yy.c  sql.l
