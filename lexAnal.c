// Lexical Analysis wSQLx
// Nick Jones
// 11/18/15

// includes
#include "nick.h"
#include <ctype.h>

// defines
#define     BUFSIZE    200

// Structs
typedef struct token {              // token link list node
    char    type[10];               // can be NUM, ID, KW, SYM
    char    value[17];              // holds the actual number or integer
    char    numType[6];             // INT | FLOAT | NULL(if not a NUM)
    struct  token *next;            // ptr to the next token
}token;



// Prototypes

// Check to see if the given string is one of the keywords in C- or not.
// Returns a 1 if it is a valid keyword or a 0 if it is not a keyword.
int isKeyWord (char* word);

// Check to see if the given character is an upper or lowercase letter.
// Returns 1 if true and 0 if false.
int isLetter (char character);

// Check to see if the given character is a number.
// Returns 1 if true and 0 if false.
int isNum (char character);

// Check to see if the given character is a one-character special symbol.
// Returns 1 if true and 0 if false.
int isSymbol1 (char character);

// Check to see if the given string of two characters is a two-character special symbol.
// Returns 1 if true and 0 if false.
int isSymbol2 (char* characters);

// Check to see if the character is a tab character, new line character or space.
// Returns 1 if true and 0 if false.
int isWhiteSpace (char character);

// A separate function that handles the situation when a number is initially read.
// This function will read numbers from the input until a non-number is read at which
// point the funciton will print the number as a NUM. If a decimal is read after the numbers
// then the NUM will become a float as long as the proper conditions are met.
// Returns the integer placeholder (i) of how far into the line the number segment stopped.
token *handleNum (int *i, char* buffer, char* tempBuffer, token *head);

// A separate function that handles the situation when a letter is initially read.
// This function will read letters from the input until a non-letter is read a which
// point the function will print the string as an ID or if is a keyword it will print
// the string as a KEYWORD.
// Returns the integer placeholder (i) to show how far into the line the string of letters ends.
token *handleLetter (int* i, char* buffer, char* tempBuffer, token *head);

// A separate function to handle characters that are not allowed including ! by itself.
// Prints out ERROR: followed by the string of consecuative non-allowed characters.
// Returns the integer placeholder (i) to show how far into the line the error string ends.
int handleError(int i, char* buffer, char* tempBuffer);

// This function allocates space for a token and initializes it with the
// parameters passed to it. The newly initialized token is then returned.
token *createToken(char *type, char *value, char *retType);

// This function iterates to the end of the linked list of token and inserts a newly created
// token initialized with the values of the parameters at the end. The head node is returned.
token *insert(token *head, char *type, char *value, char *retType);

// This function takes in the head node of the linked list and prints the type, value, and
// depth of each element in the linked list. This is just for debugging.
void print(token *head);

void printHelp();



int main (void) {
	// declarations
	char user_input[BUFSIZE];
	char tempBuffer[BUFSIZE];
	char time_stamp[26];
	char subBuf[6];
	char side[2];
	int i;
	int length;



    // Initial screen
    printf("                                                                      \n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("::******************************************************************::\n");
    printf("::**                                                              **::\n");
    printf("::**                   SSSSSS       QQQQQQQ     LL                **::\n");
    printf("::**                  SS     SS    QQ     QQ    LL                **::\n");
    printf("::**                  SS          QQ       QQ   LL                **::\n");
    printf("::**  ww       ww      SSSSSS     QQ       QQ   LL        xx  xx  **::\n");
    printf("::**   w       w            SS    QQ     Q QQ   LL          xx    **::\n");
    printf("::**    w  w  w      SS     SS     QQ     QQ    LL          xx    **::\n");
    printf("::**     ww ww         SSSSSS       QQQQQQQ Q   LLLLLLL   xx  xx  **::\n");
    printf("::**                                                              **::\n");
    printf("::******************************************************************::\n");
    printf("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("                                                                      \n");
    printf("Welcome to wSQLx!\n");



    // create the head node for the linked list of tokens
    token *head = NULL;
    token *tmp = NULL;

	timeStamp();

    while (1) {  // Loop for terminal entries
        printf("Enter a query, type HELP; for more options\n");
        printf("or enter SAVE; to exit wSQLx:\n\n");
        scanf("%[^\n]%*c", user_input);

        printf("the line is:\n%s\n", user_input); // debug
        length = strlen(user_input); // holds the num of chars in the user input
        if (user_input == NULL)
            continue;

        // check for HELP or EXIT
        for (i=0; i<5; i++) {
            subBuf[i] = toupper(user_input[i]);
        }
        subBuf[5] = '\0';
        if (strcmp(subBuf, "HELP;") == 0) {
            printHelp();
            continue;
        }
        else if (strcmp(subBuf, "SAVE;") == 0) {
            break;
        }

        // Loop for each character in the buffer line
        for (i = 0; i < length; i++) {
            // get the first two characters for LL(1) parsing
            tempBuffer[0] = user_input[i];
            tempBuffer[1] = user_input[i+1];
            tempBuffer[2] = '\0';

            if (isWhiteSpace(user_input[i]) == 1)       // Whitespace handler
                continue;
            else if (isNum(user_input[i]) == 1) {       // Number handler
                    head = handleNum(&i, user_input, tempBuffer, head);
            } // end else if number
            else if (isLetter(user_input[i]) == 1) {    // Letter handler
                if (isLetter(tempBuffer[1]) == 0) {     // if the letter string is of size 1
                    side[0] = user_input[i]; side[1] = '\0';
                    head = insert(head, "ID", side, "NULL");
                }
                else {                                  // if ther letter string is 2 or more
                    head = handleLetter(&i, user_input, tempBuffer, head);
                }
            } // end else if letter
            else if (isSymbol1(user_input[i]) >= 1) {   // Symbol handler
                if (isSymbol2(tempBuffer) == 1) {   // if two-char symbol
                    head = insert(head, "SYM", tempBuffer, "NULL");
                    i++;
                }
                else {
                    side[0] = user_input[i]; side[1] = '\0';
                    head = insert(head, "SYM", side, "NULL");
                }
            } // end else if symbol
            else if (user_input[i] == '!') {            // ! handler
                if (isSymbol2(tempBuffer) == 1) {
                    head = insert(head, "SYM", tempBuffer, "NULL");
                    i++;
                }
                else {
                    i = handleError(i, user_input, tempBuffer);
                }
            }
            else {                                  // Error handler
                i = handleError(i, user_input, tempBuffer);
            } // end else error
        } // end for
    } //  end while for terminal entries

    tmp = head;
    print(tmp);

    return 0;
} // end main()



int isKeyWord (char* word) {
    if (strcmp("create", word) == 0)
        return 1;
    else if (strcmp("drop", word) == 0)
        return 1;
    else if (strcmp("load", word) == 0)
        return 1;
    else if (strcmp("save", word) == 0)
        return 1;
    else if (strcmp("commit", word) == 0)
        return 1;
    else if (strcmp("database", word) == 0)
        return 1;
    else if (strcmp("table", word) == 0)
        return 1;
    else if (strcmp("insert", word) == 0)
        return 1;
    else if (strcmp("into", word) == 0)
        return 1;
    else if (strcmp("from", word) == 0)
        return 1;
    else if (strcmp("where", word) == 0)
        return 1;
    else if (strcmp("set", word) == 0)
        return 1;
    else if (strcmp("delete", word) == 0)
        return 1;
    else if (strcmp("integer", word) == 0)
        return 1;
    else if (strcmp("character", word) == 0)
        return 1;
    else if (strcmp("number", word) == 0)
        return 1;
    else if (strcmp("update", word) == 0)
        return 1;
    else if (strcmp("select", word) == 0)
        return 1;
    else if (strcmp("wselect", word) == 0)
        return 1;
    else
        return 0;
} // end isKeyWord()



int isLetter (char character) {
    //              UPPERCASE                               lowercase
    if ((character >= 65 && character <= 90) || (character >= 97 && character <= 122))
        return 1;
    else
        return 0;
} // end isLetter()



int isNum (char character) {
    //               0        -         9
    if (character >= 48 && character <= 57)
        return 1;
    else
        return 0;
} // end isNum()



int isSymbol1 (char character) {
    if (character == '=')
        return 1;
    else if (character == '<')
        return 1;
    else if (character == '>')
        return 1;
    else if (character == ';')
        return 1;
    else if (character == ',')
        return 1;
    else if (character == '(')
        return 1;
    else if (character == ')')
        return 1;
    else if (character == '*')
        return 1;
    else
        return 0;
} // end isSymbol1()



int isSymbol2(char* characters) {
    if (strcmp(characters, "<=") == 0)
        return 1;
    else if (strcmp(characters, ">=") == 0)
        return 1;
    else if (strcmp(characters, "==") == 0)
        return 1;
    else if (strcmp(characters, "!=") == 0)
        return 1;
    else
        return 0;
} // end isSymbol2()



int isWhiteSpace (char character) {
    if (character == 9)
        return 1;
    else if (character == 10)
        return 1;
    else if (character == 32)
        return 1;
    else
        return 0;
} // end isWhiteSpace()



token *handleNum (int *i, char* user_input, char* tempBuffer, token *head) {
    int count       = 1;
    char side[2];

    if (isNum(tempBuffer[count]) == 0 && tempBuffer[count] != '.') {
        //printf("NUM: %c\n", buffer[i]);             // handles case of single digit
        side[0] = user_input[(*i)];
        side[1] = '\0';
        head = insert(head, "NUM", side, "int");
        //printf("node inserted: type- NUM  value- %s\n", side);
        return head;
    }

    while (isNum(user_input[(*i)+1]) == 1) {        // read number to the temp buffer until
        tempBuffer[count] = user_input[(*i)+1];     // it reads a non-number
        (*i)++;
        count++;
    }

    if (user_input[(*i)+1] != '.') {    // if not a decimal
        tempBuffer[count] = '\0';                      // the number is complete
        //printf("NUM: %s\n", tempBuffer);
        head = insert(head, "NUM", tempBuffer, "int");
        //printf("node inserted: type- NUM value- %s\n", tempBuffer);
        return head;
    }
    else {     // if a decimal is next then the check for (.d+)? begins for floats
        if (isNum(user_input[(*i)+2]) == 1) {   // test for (.d+)?
            tempBuffer[count] = '.';
            tempBuffer[count+1] = user_input[(*i)+2];
            count += 2;
            (*i) += 2;
        }
        else if (isNum(user_input[(*i)+2]) == 0) {   // if not (.d+)?
            tempBuffer[count] = '\0';
            //printf("NUM: %s\n", tempBuffer);
            head = insert(head, "NUM", tempBuffer, "int");
            //printf("node inserted: type- NUM value- %s\n", tempBuffer);
            return head;
        }

        while (isNum(user_input[(*i)+1]) == 1) {           // read number to the temp Buffer until
            tempBuffer[count] = user_input[(*i)+1];        // it reads a non-number
            (*i)++;
            count++;
        }

        // final possible float without (E(+|-)?d+)? now finished
        tempBuffer[count] = '\0';
        //printf("NUM FLOAT: %s\n", tempBuffer);
        head = insert(head, "NUM", tempBuffer, "float");
        //printf("node inserted: type- NUM value- %s\n", tempBuffer);
        return head;
    } // end else float
} // end handleNum()



token *handleLetter (int *i, char* user_input, char* tempBuffer, token *head) {
    int j;
    int count = 2;
    int length;
    char lowBuf[BUFSIZE];
    (*i)++;

    while (isLetter(user_input[(*i)+1]) == 1) {        // reads letter to the temp buffer until
        tempBuffer[count] = user_input[(*i)+1];        // a non-letter is read
        (*i)++;
        count++;
    }
    tempBuffer[count] = '\0';

    // create a lowercase version for complearison
    length = strlen(tempBuffer);
    for (j=0; j<length; j++)
        lowBuf[j] = tolower(tempBuffer[j]);
    lowBuf[count] = '\0';

    if (isKeyWord(lowBuf) == 1) {
        head = insert(head, "KW", lowBuf, "NULL");
        return head;
    }

    while (isLetter(user_input[(*i)+1]) == 1 || user_input[(*i)+1] == '_' || isNum(user_input[(*i)+1]) == 1) {
        tempBuffer[count] = user_input[(*i)+1]; // a non-letter, non-number, or non-underscore is read
        (*i)++;
        count++;
    }
    tempBuffer[count] = '\0';

    head = insert(head, "ID", tempBuffer, "NULL");
    return head;
} // end handleLetter()



int handleError(int i, char* user_input, char* tempBuffer) {
    int count = 1;

    if (isWhiteSpace(tempBuffer[count]) == 1 || isNum(tempBuffer[count]) == 1
            || isLetter(tempBuffer[count]) == 1 || isSymbol1(tempBuffer[count]) >= 1) {
        tempBuffer[count] = '\0';
        printf("ERROR: %c is unrecognizable by wSQLx\n", tempBuffer[0]);
        return i;
    }

    while (isWhiteSpace(user_input[i+1]) == 0 && isNum(user_input[i+1]) == 0
            && isLetter(user_input[i+1]) == 0 && isSymbol1(user_input[i+1]) == 0) {
        tempBuffer[count] = user_input[i+1];
        i++;
        count++;
    }

    tempBuffer[count] = '\0';
    printf("ERROR: %s in unrecognizable by wSQLx\n", tempBuffer);

    return i;
} // end handleError()



token *createToken(char *type, char *value, char *retType) {
    token *t = malloc(sizeof(token));
    strcpy(t->type, type);
    strcpy(t->value, value);
    strcpy(t->numType, retType);
    t->next = NULL;

    return t;
} // end createToken()



token *insert(token *head, char *type, char *value, char *retType) {
    struct token *tmp;

    if (head == NULL)
        return createToken(type, value, retType);

    for (tmp = head; tmp->next != NULL; tmp = tmp->next)
        ;
    tmp->next = createToken(type, value, retType);

    return head;
} // end insert()



void print(token *head) {
    for( ; head != NULL; head = head->next)
        printf("%s\n%s\n\n", head->type, head->value);

    return;
} // end print()



void printHelp() {
    printf("\nEnter one of the following queries to get started:\n\n");
    printf("CREATE DATABASE db_name;\n\tto create a new database\n\n");
    printf("LOAD DATABASE db_name;\n\tto choose which database to work in\n\n");
    printf("DROP DATABASE db_name;\n\tto remove the database from memory\n\n");
    printf("CREATE TABLE tbl_name (field_type field_name [, field_type field_name]...);\n\t");
    printf("to create a table with the specified fields\n\n");
    printf("DROP TABLE tbl_name;\n\tto remove the specified table from the database\n\n");
    printf("INSERT INTO tbl_name [(field_name [, field_name]...)] VALUES (literal [, literal]...);\n\t");
    printf("to make an entry to the table with the specified values\n\n");
    printf("DELETE FROM tbl_name [WHERE condition];\n\tto delete a table entry\n\n");
    printf("UPDATE tbl_name SET field_name = literal [[, field_name = literal]...] [WHERE condition];\n\t");
    printf("to alter a previous entry\n\n");
    printf("SELECT * FROM tbl_name;\n\tto get all of the entries from a particular table\n\n");
    printf("wSELECT [*|(field [, field]...)] FROM tbl_name [WHERE condition]\n\t");
    printf("to select all entries or particular entried with their timestamp\n\n");
    printf("SAVE;\n\tto exit the wSQLx\n\n\n");
} // end printHelp()
