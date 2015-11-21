%{
void free();
%}
Delimiter    [ \t\n]
WhiteSpace   {Delimiter}+
Letter       [A-Za-z]
Digit        [0-9]
%%
"CREATE"                 {return(CREATE);}
"DROP"                   {return(DROP);}
"LOAD"                   {return(LOAD);}
"SAVE"                   {return(SAVE);}
"COMMIT"                 {return(COMMIT);}
"DATABASE"               {return(DATABASE);}
"TABLE"                  {return(TABLE);}
"INSERT"                 {return(INSERT);}
"INTO"                   {return(INTO);}
"FROM"                   {return(FROM);}
"WHERE"                  {return(WHERE);}
"SET"                    {return(SET);}
"DELETE"                 {return(DELETE);}
"UPDATE"                 {return(UPDATE);}
"WUPDATE"                {return(WUPDATE);}
"SELECT"                 {return(SELECT);}
"WSELECT"                {return(WSELECT);}
"VALUES"                 {return(VALUES);}
"INTEGER"                {return(INTEGER);}
"NUMBER"                 {return(NUMBER);}
"CHARACTER"              {return(CHARACTER);}
"*"                      {return('*');}
"("                      {return('(');}
")"                      {return(')');}
"["                      {return('[');}
"]"                      {return(']');}
","                      {return(',');}
"<"                      {return(LT);}
">"                      {return(GT);}
"<="                     {return(LTEQ);}
">="                     {return(GTEQ);}
"="                      {return(EQ);}
";"                      {return(';');}
":"                      {return(':');}
{Letter}({Digit}|{Letter})*                  {return(ID);}
{Digit}+'.'{Digit}+                        {return(DEC);}
'-'{Digit}+'.'{Digit}+                   {return(DEC);}
{Digit}+                                     {return(INT);}
'-'{Digit}+                                {return(INT);}
"'"({Letter}|{Digit}|{WhiteSpace})+"'"   {return(STR);}
"'"{Digit}{Digit}"/"{Digit}{Digit}"/"{Digit}{Digit}{Digit}{Digit}"'"   {return(DATEL);}
"'"{Digit}{Digit}"/"{Digit}{Digit}"/"{Digit}{Digit}"'"                 {return(DATESH);}
"'"{Digit}{Digit}':'{Digit}{Digit}':'{Digit}{Digit}"'"                 {return(TIME);}
{WhiteSpace}             ;
.	                 {printf("REJECT\n");exit(0);}
%%
