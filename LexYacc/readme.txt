TO TEST:

You'll need to upload these to a location on your personal osprey.unf.edu 
account using SSH Secure Shell in order to take advantage of the Flex and Bison compilers.

After that, you may have to 'chmod 777 makefile', then just type 'make' 
(should compile just fine) and run with 'SQL < data.txt' where 'data.txt' is the text file I
included containing sample SQL queries. You may test as many queries as you'd like within one file,
just be sure to terminate each query properly (;).

'ACCEPT' = All queries are valid
'REJECT' = Nope.

Please test this out and make sure it follows the grammar defined in the grammar.txt file!

Currently this is a stand-alone compiler, but this can easily be incorporated into any C file
once we decide how exactly we would like to structure our final program.
Also, it doesn't exactly return/store any tokens or create a parse tree (YET), but both of these
can be done if needed. (I may need assitance with parse tree creation)
