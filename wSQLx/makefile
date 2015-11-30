SQL: sql.l sql.y sql.c
	bison -d sql.y
	flex --header-file="lexer.h" sql.l
	gcc -o SQL sql.tab.c lex.yy.c sql.c assert.c store.c commandHelpers.c retrieve.c -pedantic -Wall -Wno-unused-parameter -Wno-missing-braces -Wextra -Wuninitialized -g -std=gnu99


# output directory
COMPILE_DIR := out
SRC_FIlES := assert.c store.c commandHelpers.c retrieve.c 

.PHONY: test clean parse


# Run this with 'make test', then './out/test'

