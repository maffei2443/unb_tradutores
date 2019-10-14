
program : global-stmt-list

global-stmt-list : global-stmt-list, global-stmt 
| global-stmt

global-stmt : decl-fun 
| def-fun 
| decl-var; 
| attr-var;

def-fun : fn id (param-list-void) base-type block

decl-fun : AHEAD fn id (param-list-void) base-type;

decl-var : mat base-type id [num] [num] 
| base-type id-ARR

id-ARR : id [num-id] 
| id

attr-var : mat-attr 
| index-attr 
| simple-attr

var : id [num-id] [num-id] 
| id [num-id] 
| id

simple-attr : id = simple-expr;

index-attr : id [num-id] = simple-expr;

mat-attr : id = [num-list-list] 

| id [num-id] = {num-list} 

| id [num-id] [num-id] = simple-expr

num-list-list :  num-list-list, num-list 
| num-list

num-list : num-list num 
| num 
| id

stmt : return simple-expr;
	
	| COPY( id id)
	
	| READ( id [num-id] [num-id]);
	
	| READ( id [num-id] );
	
	| READ( id );
	
	| PRint( id [num-id] [num-id] );
	
	| PRint( id [num-id] );
	
	| PRint( id );
	
	| call;
	
	| decl-var;
	
	| attr-var;
	
	| flux-control
	
	| loop

param-list-void : void 
| param-list

param-list : param-list, param 
| param

param : base-type id 
| mat <base-type>> id

loop : while( simple-expr ) block

flux-control : if( simple-expr ) block else flux-control 
| if(simple-expr) block else block

block : { stmt-list }

stmt-list : stmt-list, stmt 
| stmt

simple-expr : add-expr relop add-expr 
| add-expr

relop : \textless= 
| \textless\ 
|  
| = 
| == 
| !=

add-expr : add-expr addop term 
| term

addop : [+-] 

term : term mulop bin 
| bin

mulop : @@ 
| [*/@]

bin : bin bin-logi unary 
| unary

bin-logi : \&\& 
| ||

unary : unary-op factor 
| factor 

unary-op : [!\&]

factor : ( simple-expr ) 
| num-id 
| id [num-id] 
| id[num-id][num-id] 
| call

num-id : num 
| id

call : id(arg-list) 
| id()

arg-list : arg-list, arg 
| arg

arg : mat-arg 
| id[num-id][num-id] 
| id[num-id] 
| num-id 
| 

mat-arg : id num-id num-id

id-ascii : id 
| 'ascii'

base-type : CHAR 
| INT
| FLOAT






letter_ : [a-zA-Z_]

digit : [0-9]

id : letter\_ (letter\_ 
| digit)$^*$

num : int 
| FLOAT

int : digit$^+$

char : 'ascii'

float : digit$^+$. 
| digit$^+$
