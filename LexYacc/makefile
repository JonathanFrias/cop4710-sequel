SQL: SQL.tab.c lex.yy.c
	cc SQL.tab.c -o SQL
SQL.tab.c:SQL.y
	bison SQL.y
lex.yy.c: SQL.l
	flex SQL.l
