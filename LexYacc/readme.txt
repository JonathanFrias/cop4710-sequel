TO TEST:

You'll need to upload these to a location on your personal osprey.unf.edu 
account using SSH Secure Shell in order to take advantage of the Flex and Bison compilers.

After that, you may have to 'chmod 777 makefile', then just type 'make' 
(should compile just fine) and run with 'SQL'.

Lex/Yacc can now be successfully called from the C program 'test.c', they also make function calls while parsing.
Currently only "CREATE DATABASE ID;" will make a function call to 'sql.c' and print the ID providied in the query.

This will be completed soon!
