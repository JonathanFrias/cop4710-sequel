
#output directory
OUT_DIR := out
SRC_DIR := src
SRC_FIlES := src/assert.c src/store.c src/commandHelpers.c src/retrieve.c
OUT_FILES := $(OUT_DIR)/lex.yy.o $(OUT_DIR)/sql.tab.o $(OUT_DIR)/sql.o $(OUT_DIR)/commandHelpers.o $(OUT_DIR)/assert.o $(OUT_DIR)/store.o $(OUT_DIR)/retrieve.o $(OUT_DIR)/drop.o

.PHONY: test clean parse

# Run this with 'make test', then './out/test'
test: src/test.c
	mkdir -p $(OUT_DIR)
	cc src/test.c src/assert.c src/store.c src/commandHelpers.c src/retrieve.c  -pedantic -Wall -Wno-unused-parameter -Wno-missing-braces -Wextra -Wuninitialized -g -std=gnu99 -o $(OUT_DIR)/test

clean:
	rm $(OUT_DIR)/sql.tab.h $(OUT_DIR)/sql.tab.c $(OUT_DIR)/lexer.h $(OUT_DIR)/*.o  $(OUT_DIR)/lex.yy.c $(OUT_DIR)/wSQLx


all: lex.yy.o sql.tab.o sql.o commandHelpers.o assert.o store.o retrieve.o drop.o
	cc -g  -std=gnu99 $(OUT_FILES) -o $(OUT_DIR)/wSQLx

sql.o: $(SRC_DIR)/sql.c 
	cc -g -c $(SRC_DIR)/sql.c -o $(OUT_DIR)/sql.o

sql.tab.o: $(OUT_DIR)/sql.tab.c
	cc -g -c $(OUT_DIR)/sql.tab.c -o $(OUT_DIR)/sql.tab.o 

$(OUT_DIR)/sql.tab.c: $(SRC_DIR)/sql.y
	bison -d $(SRC_DIR)/sql.y -b $(OUT_DIR)/sql

lex.yy.o: $(OUT_DIR)/lex.yy.c 
	cc -g -c $(OUT_DIR)/lex.yy.c -o $(OUT_DIR)/lex.yy.o

$(OUT_DIR)/lex.yy.c: $(SRC_DIR)/sql.l $(OUT_DIR)/sql.tab.c
	flex --header-file=$(OUT_DIR)/lexer.h --outfile=$(OUT_DIR)/lex.yy.c  $(SRC_DIR)/sql.l

commandHelpers.o: $(SRC_DIR)/commandHelpers.c
	cc -g -c $(SRC_DIR)/commandHelpers.c -o $(OUT_DIR)/commandHelpers.o -std=gnu99 

assert.o: $(SRC_DIR)/assert.c
	cc -g -c $(SRC_DIR)/assert.c -o $(OUT_DIR)/assert.o -std=gnu99

store.o: $(SRC_DIR)/store.c
	cc -g -c $(SRC_DIR)/store.c -o $(OUT_DIR)/store.o -std=gnu99

retrieve.o: $(SRC_DIR)/retrieve.c
	cc -g -c $(SRC_DIR)/retrieve.c -o $(OUT_DIR)/retrieve.o -std=gnu99

drop.o: $(SRC_DIR)/drop.c 
	cc -g -c $(SRC_DIR)/drop.c -o $(OUT_DIR)/drop.o -std=gnu99
