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
    struct {Id* id;} op1;
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
    struct {Id* id; int int0; int int1;} op0;
  }u;
  int tag;
} MatArg;

typedef struct {
  union {
    struct {MatArg* matArg;} op0;
    struct {struct Aux* aux;} op1;
  }u;
  int tag;
} Arg;

typedef struct {
  union {
    struct {struct ArgList* argList; Arg* arg;} op0;
    struct {Arg* arg;} op1;
  }u;
  int tag;
} ArgList;

typedef struct {
  union {
    struct {Id* id; ArgList* argList;} op0;
    struct {Id* id;} op1;
  }u;
  int tag;
} Call;


typedef struct {
  union {
    struct {struct GlobalStmtList* globalStmtList;} op0;
  }u;
  int tag;
} Program;
typedef struct {
  union {
    struct {struct GlobalStmtList* globalStmtList; struct GlobalStmt* globalStmt;} op0;
    struct {struct GlobalStmt* globalStmt;} op1;
  }u;
  int tag;
} GlobalStmtList;
typedef struct {
  union {
    struct {struct DeclFun* declFun;} op0;
    struct {struct DefFun* defFun; Error* error;} op1;
    struct {struct DefFun* defFun;} op2;
    struct {struct DeclVar* declVar; } op3;
    struct {struct DeclVar* declVar; Error* error;} op4;
    struct {struct AttrVar* attrVar;} op5;
    struct {struct Block* block;} op6;
  }u;
  int tag;
} GlobalStmt;
typedef struct {
  union {
    struct {BaseType* baseType; Id* id;  struct ParamListVoid* paramListVoid; struct Block* block;} op0;
  }u;
  int tag;
} DefFun;
typedef struct {
  union {
    struct {BaseType* baseType; Id* id;  struct ParamListVoid* paramListVoid; ;} op0;
  }u;
  int tag;
} DeclFun;
typedef struct {
  union {
    struct {MatType* mat_type; BaseType* baseType; Id* id;  Num* num0;  Num* num1; } op0;
    struct {BaseType* baseType; struct IdArr* idArr;} op1;
  }u;
  int tag;
} DeclVar;
typedef struct {
  union {
    struct {Id* id; NumId* numId; } op0;
    struct {Id* id;} op1;
  }u;
  int tag;
} IdArr;
typedef struct {
  union {
    struct {struct MatAttr* matAttr;} op0;
    struct {struct IndexAttr* indexAttr;} op1;
    struct {struct SimpleAttr* simpleAttr;} op2;
  }u;
  int tag;
} AttrVar;
typedef struct {
  union {
    struct {Id* id;  struct Expr* expr; ;} op0;
  }u;
  int tag;
} SimpleAttr;
typedef struct {
  union {
    struct {Id* id;  NumId* numId;   struct Expr* expr; ;} op0;
  }u;
  int tag;
} IndexAttr;
typedef struct {
  union {
    struct {Id* id;   struct NumListList* numListList; } op0;
    struct {Id* id;  NumId* numId;   ; struct NumList* numList; } op1;
    struct {Id* id;  NumId* numId0; NumId* numId1;   struct Expr* expr;} op2;
  }u;
  int tag;
} MatAttr;
typedef struct {
  union {
    struct {struct NumListList* numListList; ; struct NumList* numList; } op0;
    struct {struct NumList* numList;} op1;
  }u;
  int tag;
} NumListList;
typedef struct {
  union {
    struct {struct NumList* numList; Num* num;} op0;
    struct {Num* num;} op1;
    struct {Id* id;} op2;
  }u;
  int tag;
} NumList;
typedef struct {
  union {
    struct {struct Expr* expr; ;} op0;
    struct { Id* id0; Id* id1; ;} op1;
    struct {  Id* id;  NumId* numId0;   NumId* numId1;  ;} op2;
    struct {  Id* id;  NumId* numId;  ;} op3;
    struct {  Id* id; ;} op4;
    struct {struct Expr* expr; ;} op5;
    struct {Call* call; ;} op6;
    struct {struct DeclVar* declVar; ;} op7;
    struct {struct AttrVar* attrVar; ;} op8;
    struct {struct FlowControl* flowControl;} op9;
    struct {struct Loop* loop;} op10;
  }u;
  int tag;
} Stmt;
typedef struct {
  union {
    Dummy op0;
    struct {struct ParamList* paramList;} op1;
  }u;
  int tag;
} ParamListVoid;
typedef struct {
  union {
    struct {struct ParamList* paramList; struct Param* param;} op0;
    struct {struct Param* param;} op1;
  }u;
  int tag;
} ParamList;
typedef struct {
  union {
    struct {BaseType* baseType; Id* id;} op0;
    struct {MatType* mat_type; BaseType* baseType; Id* id;} op1;
  }u;
  int tag;
} Param;
typedef struct {
  union {
    struct {struct Expr* expr; struct Block* block;} op0;
  }u;
  int tag;
} Loop;
typedef struct {
  union {
    struct {struct Expr* expr; struct Block* block;  struct FlowControl* flowControl;} op0;
    struct {struct Expr* expr; struct Block* block0;  struct Block* block1;} op1;
    struct {Error* error; struct Block* block0;  struct Block* block1;} op2;
    struct {struct Expr* expr; Error* error; struct Block* block0;  struct Block* block1;} op3;
  }u;
  int tag;
} FlowControl;

typedef struct{
  union {
    struct {struct StmtList* stmtList; Stmt* stmt;} op0;
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
    struct {struct AddExpr* addExpr; Addop* addop; struct Term* term;} op0;
    struct {struct Term* term;} op1;
  }u;
  int tag;
} AddExpr;

typedef struct {
  union {
    struct {AddExpr* addExpr0; Relop* relop; AddExpr* addExpr1;} op0;
    struct {struct AddExpr* addExpr;} op1;
  }u;
  int tag;
} Expr;



typedef struct{
  union {
    struct {struct Term* term; Mulop* mulop; struct Bin* bin;} op0;
    struct {struct Bin* bin;} op1;
  }u;
  int tag;
} Term;

typedef struct {
  union {
    struct {struct Bin* bin; BinLogi* binLogi; struct Unary* unary;} op0;
    struct {struct Unary* unary;} op1;
  }u;
  int tag;
} Bin;

typedef struct {
  union {
    struct {UnaryOp* unaryOp; struct Factor* factor;} op0;
    struct {struct Factor* factor;} op1;
  }u;
  int tag;
} Unary;

typedef struct {
  union {
    struct {Expr* expr;} op0;
    struct {struct Aux* aux;} op1;
    struct {Call* call;} op2;
    struct {Ascii* ascii;} op3;
  }u;
  int tag;
} Factor;
typedef struct {
  union {
    struct {Id* id; Expr* expr0; Expr* expr1;} op0;
    struct {Id* id; Expr* expr;} op1;
    struct {NumId* numId;} op2;
  }u;
  int tag;
} Aux;
