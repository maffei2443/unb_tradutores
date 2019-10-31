%{


%}

%left EQ NEQ GE LE
%left '<' '>'
%left '+' '-'
%left '*' '/'
%left '@'
%right MAT_POT
%left '!'

%token AHEAD BASETYPE WHILE V_INT V_FLOAT
%token MAT_TYPE IF ID ICAST FCAST ELSE

%token RETURN PRINT READ
%%

program: globalStmtList

globalStmtList : globalStmtList globalStmt
| globalStmt

globalStmt : defFun
| declFun ';'
| param ';'

declFun : BASETYPE ID '(' paramListVoid ')'

param : BASETYPE ID 
| BASETYPE ID '[' V_INT ']' 
| MAT_TYPE BASETYPE ID '['V_INT ']' '[' V_INT ']'

declOrdeclInitVar : param ';'
| param '=' rvalue ';'

paramListVoid : paramList
| 

paramList : paramList ',' param
| param

locStmtList : locStmtList locStmt 
| 

locStmt : call ';'
| lvalue '=' rvalue ';'
| flowControl
| loop
| RETURN expr ';'
| READ '(' lvalue ')' ';'
| PRINT '(' lvalue ')' ';'
| ';'
flowControl : IF '(' expr ')' block ELSE flowControl 
flowControl : IF '(' expr ')' block ELSE block 

loop : WHILE '(' expr ')' block

defFun : BASETYPE ID '(' paramListVoid ')' '{' declList locStmtList '}'

numListList :  numListList '{' numList '}'
|

numList : numList ',' num
| num


block : '{' locStmtList '}'

declList : declList declOrdeclInitVar
| 

expr : expr '+' expr
| expr '-' expr
| expr '*' expr
| expr '/' expr
| expr '@' expr
| expr MAT_POT expr
| expr EQ expr
| expr NEQ expr
| expr GE expr
| expr LE expr
| expr '>' expr
| expr '<' expr
| '!' expr
| '(' expr ')'
| ICAST '(' expr ')'
| FCAST '(' expr ')'
| lvalue
| call
| num

call : ID '(' arglist ')'
| ID '('  ')'

arglist : arglist ',' arg
| arg

arg : lvalue
| ID '(' expr ')' '(' expr ')' 

num: V_INT
| V_FLOAT


lvalue: ID
| ID '[' expr ']'
| ID '[' expr ']' '[' expr ']'

rvalue : expr
| '{' numList '}'
| '[' numListList ']'

flowControl : IF '(' error ')' block ELSE block 
flowControl : IF '(' expr error block ELSE block 

%%

int main(){

}