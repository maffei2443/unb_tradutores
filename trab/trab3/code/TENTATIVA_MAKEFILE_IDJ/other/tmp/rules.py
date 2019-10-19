# Esse script deve gerar o código boilerplate do tipo:;
# regra = make<nº Regra>_regra(token1, token2, ...)
import re
tokens= ['ERRU',
 'CHAR_TYPE',
 'INT_TYPE',
 'FLOAT_TYPE',
 'MAT_TYPE',
 'VOID',
 'CHAR',
 'INT',
 'FLOAT',
 'ID',
 'AHEAD',
 'LP',
 'RP',
 'LS',
 'RS',
 'LC',
 'RC',
 'EQ',
 'LT',
 'GT',
 'LE',
 'GE',
 'NEQ',
 'ADD',
 'SUB',
 'MUL',
 'DIV',
 'MAT_MUL',
 'MAT_POW',
 'AND',
 'OR',
 'NOT',
 'ADDR',
 'IF',
 'ELSE',
 'WHILE',
 'RETURN',
 'COPY',
 'PRINT',
 'READ',
 'ASCII',
 'SEMI_COLON',
 'COMMA',
 'ATTR'
]
heads = ["program",
  "global-stmt-list",
  "global-stmt-list",
  "global-stmt",
  "global-stmt",
  "global-stmt",
  "global-stmt",
  "global-stmt",
  "global-stmt",
  "global-stmt",
  "def-fun",
  "decl-fun",
  "decl-var",
  "decl-var",
  "id-arr",
  "id-arr",
  "attr-var",
  "attr-var",
  "attr-var",
  "simple-attr",
  "index-attr",
  "mat-attr",
  "mat-attr",
  "mat-attr",
  "num-list-list",
  "num-list-list",
  "num-list",
  "num-list",
  "num-list",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "stmt",
  "param-list-void",
  "param-list-void",
  "param-list",
  "param-list",
  "param",
  "param",
  "loop",
  "flow-control",
  "flow-control",
  "flow-control",
  "flow-control",
  "block",
  "block",
  "stmt-list",
  "stmt-list",
  "expr",
  "expr",
  "relop",
  "relop",
  "relop",
  "relop",
  "relop",
  "relop",
  "add-expr",
  "add-expr",
  "addop",
  "addop",
  "term",
  "term",
  "mulop",
  "mulop",
  "mulop",
  "bin",
  "bin",
  "bin-logi",
  "bin-logi",
  "unary",
  "unary",
  "unary-op",
  "unary-op",
  "factor",
  "factor",
  "factor",
  "factor",
  "aux",
  "aux",
  "aux",
  "num-id",
  "num-id",
  "num-id",
  "call",
  "call",
  "arg-list",
  "arg-list",
  "arg",
  "arg",
  "mat-arg",
  "ascii",
  "base-type",
  "base-type",
  "base-type",
  "num",
  "num",
]

rules = [
  "program : global-stmt-list",
  "global-stmt-list : global-stmt-list global-stmt ",
  "global-stmt-list : global-stmt ",
  "global-stmt : decl-fun ",
  "global-stmt : def-fun error",
  "global-stmt : def-fun ",
  "global-stmt : decl-var SEMI_COLON ",
  "global-stmt : decl-var error ",
  "global-stmt : attr-var SEMI_COLON",
  "global-stmt : block",
  "def-fun : base-type ID LP param-list-void RP block ",
  "decl-fun : AHEAD base-type ID LP param-list-void RP SEMI_COLON ",
  "decl-var : MAT_TYPE base-type ID LS num RS LS num RS ",
  "decl-var : base-type id-arr",
  "id-arr : ID LS num-id RS ",
  "id-arr : ID",
  "attr-var : mat-attr ",
  "attr-var : index-attr ",
  "attr-var : simple-attr",
  "simple-attr : ID ATTR expr SEMI_COLON",
  "index-attr : ID LS num-id RS ATTR expr SEMI_COLON",
  "mat-attr : ID ATTR LS num-list-list RS ",
  "mat-attr : ID LS num-id RS ATTR LC num-list RC ",
  "mat-attr : ID LS num-id RS LS num-id RS ATTR expr",
  "num-list-list :  num-list-list LC num-list RC",
  "num-list-list :  num-list",
  "num-list : num-list num ",
  "num-list : num ",
  "num-list : ID",
  "stmt : RETURN expr SEMI_COLON ",
  "stmt : COPY LP ID ID RP SEMI_COLON ",
  "stmt : READ LP ID LS num-id RS LS num-id RS RP SEMI_COLON ",
  "stmt : READ LP ID LS num-id RS RP SEMI_COLON ",
  "stmt : READ LP ID RP SEMI_COLON ",
  "stmt : PRINT expr SEMI_COLON 	",
  "stmt : call SEMI_COLON ",
  "stmt : decl-var SEMI_COLON",
  "stmt : attr-var SEMI_COLON",
  "stmt : flow-control ",
  "stmt : loop ",
  "param-list-void : VOID ",
  "param-list-void : param-list",
  "param-list : param-list param ",
  "param-list : param",
  "param : base-type ID ",
  "param : MAT_TYPE base-type ID",
  "loop : WHILE LP expr RP block",
  "flow-control : IF LP expr RP block ELSE flow-control ",
  "flow-control : IF LP expr RP block ELSE block ",
  "flow-control : IF LP error RP block ELSE block",
  "flow-control : IF LP expr error block ELSE block",
  "block : LC stmt-list RC ",
  "block : LC RC ",
  "stmt-list : stmt-list stmt ",
  "stmt-list : stmt",
  "expr : add-expr relop add-expr ",
  "expr : add-expr",
  "relop : LE ",
  "relop : GE ",
  "relop : NEQ",
  "relop : EQ ",
  "relop : GT",
  "relop : LT ",
  "add-expr : add-expr addop term ",
  "add-expr : term",
  "addop : ADD",
  "addop : SUB",
  "term : term mulop bin ",
  "term : bin",
  "mulop : MAT_MUL",
  "mulop : MUL",
  "mulop : DIV",
  "mulop : MAT_POW",
  "bin : bin bin-logi unary ",
  "bin : unary",
  "bin-logi : AND",
  "bin-logi : OR",
  "unary : unary-op factor ",
  "unary : factor ",
  "unary-op : NOT",
  "unary-op : ADDR",
  "factor : LP expr RP ",
  "factor : aux",
  "factor : call",
  "factor : '\''ascii'\''",
  "aux : ID LS expr RS LS expr RS ",
  "aux : ID LS expr RS ",
  "aux : num-id",
  "num-id : INT ",
  "num-id : FLOAT",
  "num-id : ID",
  "call : ID LP arg-list RP",
  "call : ID LP VOID RP",
  "arg-list : arg-list COMMA arg ",
  "arg-list : arg",
  "arg : mat-arg ",
  "arg : aux",
  "mat-arg : ID num-id num-id",
  "ascii : '\'' ASCII '\''",
  "base-type : CHAR_TYPE ",
  "base-type : INT_TYPE",
  "base-type : FLOAT_TYPE",
  "num : FLOAT",
  "num : INT",
]

def GetLastRules(fileName = 'grammar.y'):
  """
  Gera lista das regras de produção da gramática.
  """
  lis = [] 
  for l in open(fileName): 
    if re.findall(' : ', l):  
      head = re.findall(r'(.+ : )', l)[0] 
      lis.append(re.findall(r'([^{\n]+)', l)[0].strip()) 
    elif l.startswith('|'): 
      lis.append(head + re.findall(r'([^{\n]+)', l)[0][2:].strip()) 
  return lis

