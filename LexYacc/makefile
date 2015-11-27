SQL: sql.l sql.y test.c
	bison -d sql.y 
	flex --header-file="lexheader.h" sql.l 
	gcc -o SQL sql.tab.c lex.yy.c sql.c 

clean:

	rm -rf *.o SQL
