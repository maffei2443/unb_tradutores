#include "unions.h"

#define str struct
typedef char Error;
typedef str {
  union {
    struct {} op0;  //i: int
    struct {} op1;  //i: f: float
    struct {} op2;  //i: c: char
  }u;
  int tag;
}MatType;

typedef str {
  union {
    str {str GlobalStmtList* globalStmtList;} op0;
  }u;
  int tag;
} Program;
typedef str {
  union {
    str {str GlobalStmtList* globalStmtList; str GlobalStmt* globalStmt;} op0;
    str {str GlobalStmt* globalStmt;} op1;
  }u;
  int tag;
} GlobalStmtList;
typedef str {
  union {
    str {str DeclFun* declFun;} op0;
    str {str DefFun* defFun; str Error* error;} op1;
    str {str DefFun* defFun;} op2;
    str {str DeclVar* declVar; } op3;
    str {str DeclVar* declVar; str Error* error;} op4;
    str {str AttrVar* attrVar;} op5;
    str {str Block* block;} op6;
  }u;
  int tag;
} GlobalStmt;
typedef str {
  union {
    str {str BaseType* baseType; str Id* id;  str ParamListVoid* paramListVoid; str Block* block;} op0;
  }u;
  int tag;
} DefFun;
typedef str {
  union {
    str {str BaseType* baseType; str Id* id;  str ParamListVoid* paramListVoid; ;} op0;
  }u;
  int tag;
} DeclFun;
typedef str {
  union {
    str {str MatType* mat_type; str BaseType* baseType; str Id* id;  str Num* num0;   str Num* num1; } op0;
    str {str BaseType* baseType; str IdArr* idArr;} op1;
  }u;
  int tag;
} DeclVar;
typedef str {
  union {
    str {str Id* id;  str NumId* numId; } op0;
    str {str Id* id;} op1;
  }u;
  int tag;
} IdArr;
typedef str {
  union {
    str {str MatAttr* matAttr;} op0;
    str {str IndexAttr* indexAttr;} op1;
    str {str SimpleAttr* simpleAttr;} op2;
  }u;
  int tag;
} AttrVar;
typedef str {
  union {
    str {str Id* id;  str Expr* expr; ;} op0;
  }u;
  int tag;
} SimpleAttr;
typedef str {
  union {
    str {str Id* id;  str NumId* numId;   str Expr* expr; ;} op0;
  }u;
  int tag;
} IndexAttr;
typedef str {
  union {
    str {str Id* id;   str NumListList* numListList; } op0;
    str {str Id* id;  str NumId* numId;   ; str NumList* numList; } op1;
    str {str Id* id;  str NumId* numId0;   str NumId* numId1;   str Expr* expr;} op2;
  }u;
  int tag;
} MatAttr;
typedef str {
  union {
    str {str NumListList* numListList; ; str NumList* numList; } op0;
    str {str NumList* numList;} op1;
  }u;
  int tag;
} NumListList;
typedef str {
  union {
    str {str NumList* numList; str Num* num;} op0;
    str {str Num* num;} op1;
    str {str Id* id;} op2;
  }u;
  int tag;
} NumList;
typedef str {
  union {
    str {str Expr* expr; ;} op0;
    str { str Id* id0; str Id* id1; ;} op1;
    str {  str Id* id;  str NumId* numId0;   str NumId* numId1;  ;} op2;
    str {  str Id* id;  str NumId* numId;  ;} op3;
    str {  str Id* id; ;} op4;
    str {str Expr* expr; ;} op5;
    str {str Call* call; ;} op6;
    str {str DeclVar* declVar; ;} op7;
    str {str AttrVar* attrVar; ;} op8;
    str {str FlowControl* flowControl;} op9;
    str {str Loop* loop;} op10;
  }u;
  int tag;
} Stmt;
typedef str {
  union {
    str {} op0;
    str {str ParamList* paramList;} op1;
  }u;
  int tag;
} ParamListVoid;
typedef str {
  union {
    str {str ParamList* paramList; str Param* param;} op0;
    str {str Param* param;} op1;
  }u;
  int tag;
} ParamList;
typedef str {
  union {
    str {str BaseType* baseType; str Id* id;} op0;
    str {str MatType* mat_type; str BaseType* baseType; str Id* id;} op1;
  }u;
  int tag;
} Param;
typedef str {
  union {
    str {str Expr* expr; str Block* block;} op0;
  }u;
  int tag;
} Loop;
typedef str {
  union {
    str {str Expr* expr; str Block* block;  str FlowControl* flowControl;} op0;
    str {str Expr* expr; str Block* block0;  str Block* block1;} op1;
    str {str Error* error; str Block* block0;  str Block* block1;} op2;
    str {str Expr* expr; str Error* error; str Block* block0;  str Block* block1;} op3;
  }u;
  int tag;
} FlowControl;
typedef str {
  union {
    str { str StmtList* stmtList; } op0;
    str {} op1;
  }u;
  int tag;
} Block;
typedef str {
  union {
    str {str StmtList* stmtList; str Stmt* stmt;} op0;
    str {str Stmt* stmt;} op1;
  }u;
  int tag;
} StmtList;
typedef str {
  union {
    str {str AddExpr* addExpr0; str Relop* relop; str AddExpr* addExpr1;} op0;
    str {str AddExpr* addExpr;} op1;
  }u;
  int tag;
} Expr;
typedef str {
  union {
    str {} op0;
    str {} op1;
    str {} op2;
    str {} op3;
    str {} op4;
    str {} op5;
  }u;
  int tag;
} Relop;
typedef str {
  union {
    str {str AddExpr* addExpr; str Addop* addop; str Term* term;} op0;
    str {str Term* term;} op1;
  }u;
  int tag;
} AddExpr;
typedef str {
  union {
    str {} op0;
    str {} op1;
  }u;
  int tag;
} Addop;
typedef str {
  union {
    str {str Term* term; str Mulop* mulop; str Bin* bin;} op0;
    str {str Bin* bin;} op1;
  }u;
  int tag;
} Term;
typedef str {
  union {
    str {} op0;
    str {} op1;
    str {} op2;
  }u;
  int tag;
} Mulop;
typedef str {
  union {
    str {str Bin* bin; str BinLogi* binLogi; str Unary* unary;} op0;
    str {str Unary* unary;} op1;
  }u;
  int tag;
} Bin;
typedef str {
  union {
    str {} op0;
    str {} op1;
  }u;
  int tag;
} BinLogi;
typedef str {
  union {
    str {str UnaryOp* unaryOp; str Factor* factor;} op0;
    str {str Factor* factor;} op1;
  }u;
  int tag;
} Unary;
typedef str {
  union {
    str {} op0;
    str {} op1;
  }u;
  int tag;
} UnaryOp;
typedef str {
  union {
    str {str Expr* expr;} op0;
    str {str Aux* aux;} op1;
    str {str Call* call;} op2;
    str {str Ascii* ascii;} op3;
  }u;
  int tag;
} Factor;
typedef str {
  union {
    str {str Id* id; str Expr* expr0; str Expr* expr1;} op0;
    str {str Id* id; str Expr* expr;} op1;
    str {str NumId* numId;} op2;
  }u;
  int tag;
} Aux;
typedef str {
  union {
    str {int ival;} op0;
    str {float fval;} op1;
    str {str Id* id;} op2;
  }u;
  int tag;
} NumId;
typedef str {
  union {
    str {str Id* id;str ArgList* argList;} op0;
    str {str Id* id;} op1;
  }u;
  int tag;
} Call;
typedef str {
  union {
    str {str ArgList* argList; str Arg* arg;} op0;
    str {str Arg* arg;} op1;
  }u;
  int tag;
} ArgList;
typedef str {
  union {
    str {str MatArg* matArg;} op0;
    str {str Aux* aux;} op1;
  }u;
  int tag;
} Arg;
typedef str {
  union {
    str {str Id* id; str NumId* numId0; str NumId* numId1;} op0;
  }u;
  int tag;
} MatArg;
typedef str {
  union {
    str {char cval;} op0;
  }u;
  int tag;
} Ascii;
typedef str {
  union {
    str {char ival;} op0;  // um caractere para diferenciar int/float/char
  }u;
  int tag;
} BaseType;
typedef str {
  union {
    str {float fval;} op0;
    str {int ival;} op1;
  }u;
  int tag;
} Num;

typedef str {
  int size;
  char* sval;
} Id;