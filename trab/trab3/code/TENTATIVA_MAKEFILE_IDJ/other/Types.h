typedef struct {} Dummy;
#define struct struct
typedef char Error;



typedef struct {
  union {
    Dummy op0;  //i: int
    Dummy op1;  //i: f: float
    Dummy op2;  //i: c: char
  }u;
  int tag;
} MatType;

typedef struct {
  union {
    Dummy op0;
    Dummy op1;
  }u;
  int tag;
} Addop;

typedef struct {
  union {
    Dummy op0;
    Dummy op1;
    Dummy op2;
  }u;
  int tag;
} Mulop;

typedef struct {
  union {
    Dummy op0;
    Dummy op1;
    Dummy op2;
    Dummy op3;
    Dummy op4;
    Dummy op5;
  }u;
  int tag;
} Relop;

typedef struct {
  union {
    Dummy op0;
    Dummy op1;
  }u;
  int tag;
} UnaryOp;

typedef struct {
  union {
    Dummy op0;
    Dummy op1;
  }u;
  int tag;
} BinLogi;

typedef struct {
  int size;
  char* sval;
} Id;

typedef struct {
  union {
    struct {float fval;} op0;
    struct {int ival;} op1;
  }u;
  int tag;
} Num;

typedef struct {
  union {
    struct {Num* num;} op0;
    struct {char* id;} op1;
  }u;
  int tag;
} NumId;

typedef struct {
  union {
    struct {char ival;} op0;  // um caractere para diferenciar int/float/char
  }u;
  int tag;
} BaseType;

typedef struct {
  union {
    struct {char cval;} op0;
  }u;
  int tag;
} Ascii;

typedef struct {
  union {
    struct {char* id; int int0; int int1;} op0;
  }u;
  int tag;
} MatArg;

typedef struct {
  union {
    struct {MatArg* matArg;} op0;
    struct {void* aux;} op1;
  }u;
  int tag;
} Arg;

typedef struct {
  union {
    struct {void* argList; Arg* arg;} op0;
    struct {Arg* arg;} op1;
  }u;
  int tag;
} ArgList;

typedef struct {
  union {
    struct {char* id; ArgList* argList;} op0;
    struct {char* id;} op1;
  }u;
  int tag;
} Call;


typedef struct {
  union {
    struct {void* globalStmtList;} op0;
  }u;
  int tag;
} Program;
typedef struct {
  union {
    struct {void* globalStmtList; void* globalStmt;} op0;
    struct {void* globalStmt;} op1;
  }u;
  int tag;
} GlobalStmtList;
typedef struct {
  union {
    struct {void* declFun;} op0;
    struct {void* defFun; Error* error;} op1;
    struct {void* defFun;} op2;
    struct {void* declVar; } op3;
    struct {void* declVar; Error* error;} op4;
    struct {void* attrVar;} op5;
    struct {void* block;} op6;
  }u;
  int tag;
} GlobalStmt;
typedef struct {
  union {
    struct {BaseType* baseType; char* id;  void* paramListVoid; void* block;} op0;
  }u;
  int tag;
} DefFun;
typedef struct {
  union {
    struct {BaseType* baseType; char* id;  void* paramListVoid; ;} op0;
  }u;
  int tag;
} DeclFun;
typedef struct {
  union {
    struct {MatType* mat_type; BaseType* baseType; char* id;  Num* num0;  Num* num1; } op0;
    struct {BaseType* baseType; void* idArr;} op1;
  }u;
  int tag;
} DeclVar;
typedef struct {
  union {
    struct {char* id; NumId* numId; } op0;
    struct {char* id;} op1;
  }u;
  int tag;
} IdArr;
typedef struct {
  union {
    struct {void* matAttr;} op0;
    struct {void* indexAttr;} op1;
    struct {void* simpleAttr;} op2;
  }u;
  int tag;
} AttrVar;
typedef struct {
  union {
    struct {char* id;  void* expr; ;} op0;
  }u;
  int tag;
} SimpleAttr;
typedef struct {
  union {
    struct {char* id;  NumId* numId;   void* expr; ;} op0;
  }u;
  int tag;
} IndexAttr;
typedef struct {
  union {
    struct {char* id;   void* numListList; } op0;
    struct {char* id;  NumId* numId;   ; void* numList; } op1;
    struct {char* id;  NumId* numId0; NumId* numId1;   void* expr;} op2;
  }u;
  int tag;
} MatAttr;
typedef struct {
  union {
    struct {void* numListList; ; void* numList; } op0;
    struct {void* numList;} op1;
  }u;
  int tag;
} NumListList;
typedef struct {
  union {
    struct {void* numList; Num* num;} op0;
    struct {Num* num;} op1;
    struct {char* id;} op2;
  }u;
  int tag;
} NumList;
typedef struct {
  union {
    struct {void* expr; ;} op0;
    struct { char* id0; char* id1; ;} op1;
    struct {  char* id;  NumId* numId0;   NumId* numId1;  ;} op2;
    struct {  char* id;  NumId* numId;  ;} op3;
    struct {  char* id; ;} op4;
    struct {void* expr; ;} op5;
    struct {Call* call; ;} op6;
    struct {void* declVar; ;} op7;
    struct {void* attrVar; ;} op8;
    struct {void* flowControl;} op9;
    struct {void* loop;} op10;
  }u;
  int tag;
} Stmt;
typedef struct {
  union {
    Dummy op0;
    struct {void* paramList;} op1;
  }u;
  int tag;
} ParamListVoid;
typedef struct {
  union {
    struct {void* paramList; void* param;} op0;
    struct {void* param;} op1;
  }u;
  int tag;
} ParamList;
typedef struct {
  union {
    struct {BaseType* baseType; char* id;} op0;
    struct {MatType* mat_type; BaseType* baseType; char* id;} op1;
  }u;
  int tag;
} Param;
typedef struct {
  union {
    struct {void* expr; void* block;} op0;
  }u;
  int tag;
} Loop;
typedef struct {
  union {
    struct {void* expr; void* block;  void* flowControl;} op0;
    struct {void* expr; void* block0;  void* block1;} op1;
    struct {Error* error; void* block0;  void* block1;} op2;
    struct {void* expr; Error* error; void* block0;  void* block1;} op3;
  }u;
  int tag;
} FlowControl;

typedef struct{
  union {
    struct {void* stmtList; Stmt* stmt;} op0;
    struct {Stmt* stmt;} op1;
  }u;
  int tag;
} StmtList;

typedef struct {
  union {
    struct {StmtList* stmtList; } op0;
    Dummy op1;
  }u;
  int tag;
} Block;

typedef struct {
  union {
    struct {void* addExpr; Addop* addop; void* term;} op0;
    struct {void* term;} op1;
  }u;
  int tag;
} AddExpr;

typedef struct {
  union {
    struct {AddExpr* addExpr0; Relop* relop; AddExpr* addExpr1;} op0;
    struct {void* addExpr;} op1;
  }u;
  int tag;
} Expr;



typedef struct{
  union {
    struct {void* term; Mulop* mulop; void* bin;} op0;
    struct {void* bin;} op1;
  }u;
  int tag;
} Term;

typedef struct {
  union {
    struct {void* bin; BinLogi* binLogi; void* unary;} op0;
    struct {void* unary;} op1;
  }u;
  int tag;
} Bin;

typedef struct {
  union {
    struct {UnaryOp* unaryOp; void* factor;} op0;
    struct {void* factor;} op1;
  }u;
  int tag;
} Unary;

typedef struct {
  union {
    struct {Expr* expr;} op0;
    struct {void* aux;} op1;
    struct {Call* call;} op2;
    struct {Ascii* ascii;} op3;
  }u;
  int tag;
} Factor;
typedef struct {
  union {
    struct {char* id; Expr* expr0; Expr* expr1;} op0;
    struct {char* id; Expr* expr;} op1;
    struct {NumId* numId;} op2;
  }u;
  int tag;
} Aux;
