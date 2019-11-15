typedef struct {
  union {
    struct {GlobalStmtList* globalStmtList;} op0;
  }u;
} Program;
typedef struct {
  union {
    struct {GlobalStmtList* globalStmtList; GlobalStmt* globalStmt;} op0;
    struct {GlobalStmt* globalStmt;} op1;
  }u;
} GlobalStmtList;
typedef struct {
  union {
    struct {DeclFun* declFun;} op0;
    struct {DefFun* defFun; Error* error;} op1;
    struct {DefFun* defFun;} op2;
    struct {DeclVar* declVar; Semi_colon* semi_colon;} op3;
    struct {DeclVar* declVar; Error* error;} op4;
    struct {AttrVar* attrVar; Semi_colon* semi_colon;} op5;
    struct {Block* block;} op6;
  }u;
} GlobalStmt;
typedef struct {
  union {
    struct {BaseType* baseType; Id* id; Lp* lp; ParamListVoid* paramListVoid; Rp* rp; Block* block;} op0;
  }u;
} DefFun;
typedef struct {
  union {
    struct {Ahead* ahead; BaseType* baseType; Id* id; Lp* lp; ParamListVoid* paramListVoid; Rp* rp; Semi_colon* semi_colon;} op0;
  }u;
} DeclFun;
typedef struct {
  union {
    struct {Mat_type* mat_type; BaseType* baseType; Id* id; Ls* ls; Num* num; Rs* rs; Ls* ls; Num* num; Rs* rs;} op0;
    struct {BaseType* baseType; IdArr* idArr;} op1;
  }u;
} DeclVar;
typedef struct {
  union {
    struct {Id* id; Ls* ls; NumId* numId; Rs* rs;} op0;
    struct {Id* id;} op1;
  }u;
} IdArr;
typedef struct {
  union {
    struct {MatAttr* matAttr;} op0;
    struct {IndexAttr* indexAttr;} op1;
    struct {SimpleAttr* simpleAttr;} op2;
  }u;
} AttrVar;
typedef struct {
  union {
    struct {Id* id; Attr* attr; Expr* expr; Semi_colon* semi_colon;} op0;
  }u;
} SimpleAttr;
typedef struct {
  union {
    struct {Id* id; Ls* ls; NumId* numId; Rs* rs; Attr* attr; Expr* expr; Semi_colon* semi_colon;} op0;
  }u;
} IndexAttr;
typedef struct {
  union {
    struct {Id* id; Attr* attr; Ls* ls; NumListList* numListList; Rs* rs;} op0;
    struct {Id* id; Ls* ls; NumId* numId; Rs* rs; Attr* attr; Lc* lc; NumList* numList; Rc* rc;} op1;
    struct {Id* id; Ls* ls; NumId* numId; Rs* rs; Ls* ls; NumId* numId; Rs* rs; Attr* attr; Expr* expr;} op2;
  }u;
} MatAttr;
typedef struct {
  union {
    struct {NumListList* numListList; Lc* lc; NumList* numList; Rc* rc;} op0;
    struct {NumList* numList;} op1;
  }u;
} NumListList;
typedef struct {
  union {
    struct {NumList* numList; Num* num;} op0;
    struct {Num* num;} op1;
    struct {Id* id;} op2;
  }u;
} NumList;
typedef struct {
  union {
    struct {Return* return; Expr* expr; Semi_colon* semi_colon;} op0;
    struct {Copy* copy; Lp* lp; Id* id; Id* id; Rp* rp; Semi_colon* semi_colon;} op1;
    struct {Read* read; Lp* lp; Id* id; Ls* ls; NumId* numId; Rs* rs; Ls* ls; NumId* numId; Rs* rs; Rp* rp; Semi_colon* semi_colon;} op2;
    struct {Read* read; Lp* lp; Id* id; Ls* ls; NumId* numId; Rs* rs; Rp* rp; Semi_colon* semi_colon;} op3;
    struct {Read* read; Lp* lp; Id* id; Rp* rp; Semi_colon* semi_colon;} op4;
    struct {Print* print; Expr* expr; Semi_colon* semi_colon;} op5;
    struct {Call* call; Semi_colon* semi_colon;} op6;
    struct {DeclVar* declVar; Semi_colon* semi_colon;} op7;
    struct {AttrVar* attrVar; Semi_colon* semi_colon;} op8;
    struct {FlowControl* flowControl;} op9;
    struct {Loop* loop;} op10;
  }u;
} Stmt;
typedef struct {
  union {
    struct {Void* void;} op0;
    struct {ParamList* paramList;} op1;
  }u;
} ParamListVoid;
typedef struct {
  union {
    struct {ParamList* paramList; Param* param;} op0;
    struct {Param* param;} op1;
  }u;
} ParamList;
typedef struct {
  union {
    struct {BaseType* baseType; Id* id;} op0;
    struct {Mat_type* mat_type; BaseType* baseType; Id* id;} op1;
  }u;
} Param;
typedef struct {
  union {
    struct {While* while; Lp* lp; Expr* expr; Rp* rp; Block* block;} op0;
  }u;
} Loop;
typedef struct {
  union {
    struct {If* if; Lp* lp; Expr* expr; Rp* rp; Block* block; Else* else; FlowControl* flowControl;} op0;
    struct {If* if; Lp* lp; Expr* expr; Rp* rp; Block* block; Else* else; Block* block;} op1;
    struct {If* if; Lp* lp; Error* error; Rp* rp; Block* block; Else* else; Block* block;} op2;
    struct {If* if; Lp* lp; Expr* expr; Error* error; Block* block; Else* else; Block* block;} op3;
  }u;
} FlowControl;
typedef struct {
  union {
    struct {Lc* lc; StmtList* stmtList; Rc* rc;} op0;
    struct {Lc* lc; Rc* rc;} op1;
  }u;
} Block;
typedef struct {
  union {
    struct {StmtList* stmtList; Stmt* stmt;} op0;
    struct {Stmt* stmt;} op1;
  }u;
} StmtList;
typedef struct {
  union {
    struct {AddExpr* addExpr; Relop* relop; AddExpr* addExpr;} op0;
    struct {AddExpr* addExpr;} op1;
  }u;
} Expr;
typedef struct {
  union {
    struct {Le* le;} op0;
    struct {Ge* ge;} op1;
    struct {Neq* neq;} op2;
    struct {Eq* eq;} op3;
    struct {Gt* gt;} op4;
    struct {Lt* lt;} op5;
  }u;
} Relop;
typedef struct {
  union {
    struct {AddExpr* addExpr; Addop* addop; Term* term;} op0;
    struct {Term* term;} op1;
  }u;
} AddExpr;
typedef struct {
  union {
    struct {Add* add;} op0;
    struct {Sub* sub;} op1;
  }u;
} Addop;
typedef struct {
  union {
    struct {Term* term; Mulop* mulop; Bin* bin;} op0;
    struct {Bin* bin;} op1;
  }u;
} Term;
typedef struct {
  union {
    struct {Mat_mul* mat_mul;} op0;
    struct {Mul* mul;} op1;
    struct {Div* div;} op2;
    struct {Mat_pow* mat_pow;} op3;
  }u;
} Mulop;
typedef struct {
  union {
    struct {Bin* bin; BinLogi* binLogi; Unary* unary;} op0;
    struct {Unary* unary;} op1;
  }u;
} Bin;
typedef struct {
  union {
    struct {And* and;} op0;
    struct {Or* or;} op1;
  }u;
} BinLogi;
typedef struct {
  union {
    struct {UnaryOp* unaryOp; Factor* factor;} op0;
    struct {Factor* factor;} op1;
  }u;
} Unary;
typedef struct {
  union {
    struct {Not* not;} op0;
    struct {Addr* addr;} op1;
  }u;
} UnaryOp;
typedef struct {
  union {
    struct {Lp* lp; Expr* expr; Rp* rp;} op0;
    struct {Aux* aux;} op1;
    struct {Call* call;} op2;
    struct {'''ascii'''* '''ascii''';} op3;
  }u;
} Factor;
typedef struct {
  union {
    struct {Id* id; Ls* ls; Expr* expr; Rs* rs; Ls* ls; Expr* expr; Rs* rs;} op0;
    struct {Id* id; Ls* ls; Expr* expr; Rs* rs;} op1;
    struct {NumId* numId;} op2;
  }u;
} Aux;
typedef struct {
  union {
    struct {Int* int;} op0;
    struct {Float* float;} op1;
    struct {Id* id;} op2;
  }u;
} NumId;
typedef struct {
  union {
    struct {Id* id; Lp* lp; ArgList* argList; Rp* rp;} op0;
    struct {Id* id; Lp* lp; Void* void; Rp* rp;} op1;
  }u;
} Call;
typedef struct {
  union {
    struct {ArgList* argList; Comma* comma; Arg* arg;} op0;
    struct {Arg* arg;} op1;
  }u;
} ArgList;
typedef struct {
  union {
    struct {MatArg* matArg;} op0;
    struct {Aux* aux;} op1;
  }u;
} Arg;
typedef struct {
  union {
    struct {Id* id; NumId* numId; NumId* numId;} op0;
  }u;
} MatArg;
typedef struct {
  union {
    struct {'''* '''; Ascii* ascii; '''* ''';} op0;
  }u;
} Ascii;
typedef struct {
  union {
    struct {Char_type* char_type;} op0;
    struct {Int_type* int_type;} op1;
    struct {Float_type* float_type;} op2;
  }u;
} BaseType;
typedef struct {
  union {
    struct {Float* float;} op0;
    struct {Int* int;} op1;
  }u;
} Num;
