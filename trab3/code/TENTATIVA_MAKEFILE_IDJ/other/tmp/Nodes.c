typedef struct {} Dummy;
typedef Dummy _Erru;
typedef Dummy _Char_type;
typedef Dummy _Int_type;
typedef Dummy _Float_type;
typedef Dummy _Mat_type;
typedef Dummy _Void;
typedef struct {/*PREENCHE MANUALMENTE*/} _V_char;
typedef struct {/*PREENCHE MANUALMENTE*/} _V_int;
typedef struct {/*PREENCHE MANUALMENTE*/} _V_float;
typedef struct {/*PREENCHE MANUALMENTE*/} _V_id;
typedef Dummy _Ahead;
typedef Dummy _Lp;
typedef Dummy _Rp;
typedef Dummy _Ls;
typedef Dummy _Rs;
typedef Dummy _Lc;
typedef Dummy _Rc;
typedef Dummy _Eq;
typedef Dummy _Lt;
typedef Dummy _Gt;
typedef Dummy _Le;
typedef Dummy _Ge;
typedef Dummy _Neq;
typedef Dummy _Add;
typedef Dummy _Sub;
typedef Dummy _Mul;
typedef Dummy _Div;
typedef Dummy _Mat_mul;
typedef Dummy _Mat_pow;
typedef Dummy _And;
typedef Dummy _Or;
typedef Dummy _Not;
typedef Dummy _Addr;
typedef Dummy _If;
typedef Dummy _Else;
typedef Dummy _While;
typedef Dummy _Return;
typedef Dummy _Copy;
typedef Dummy _Print;
typedef Dummy _Read;
typedef struct {/*PREENCHE MANUALMENTE*/} _V_ascii;
typedef Dummy _Semi_colon;
typedef Dummy _Dot;
typedef Dummy _Comma;
typedef Dummy _Attr;

#define STR struct
typedef struct {
  union {
    STR {STR GlobalStmtList* _globalStmtList;} op0;
  }u;
  int tag;
} Program;
typedef struct {
  union {
    STR {STR GlobalStmtList* _globalStmtList; STR GlobalStmt* _globalStmt;} op0;
    STR {STR GlobalStmt* _globalStmt;} op1;
  }u;
  int tag;
} GlobalStmtList;
typedef struct {
  union {
    STR {STR DeclFun* _declFun;} op0;
    STR {STR DefFun* _defFun; STR Error* _error;} op1;
    STR {STR DefFun* _defFun;} op2;
    STR {STR DeclVar* _declVar; _Semi_colon* __semi_colon;} op3;
    STR {STR DeclVar* _declVar; STR Error* _error;} op4;
    STR {STR AttrVar* _attrVar; _Semi_colon* __semi_colon;} op5;
    STR {STR Block* _block;} op6;
  }u;
  int tag;
} GlobalStmt;
typedef struct {
  union {
    STR {
      STR BaseType* _baseType; _V_id* __v_id; _Lp* __lp;
      STR ParamListVoid* _paramListVoid; _Rp* __rp; STR Block* _block;
    } op0;
  }u;
  int tag;
} DefFun;
typedef struct {
  union {
    STR {_Ahead* __ahead; STR BaseType* _baseType; _V_id* __v_id; _Lp* __lp; STR ParamListVoid* _paramListVoid; _Rp* __rp; _Semi_colon* __semi_colon;} op0;
  }u;
  int tag;
} DeclFun;
typedef struct {
  union {
    STR {_Mat_type* __mat_type; STR BaseType* _baseType; _V_id* __v_id; _Ls* __ls0; STR Num* _num0; _Rs* __rs0; _Ls* __ls1; STR Num* _num1; _Rs* __rs1;} op0;
    STR {STR BaseType* _baseType; STR IdArr* _idArr;} op1;
  }u;
  int tag;
} DeclVar;
typedef struct {
  union {
    STR {_V_id* __v_id; _Ls* __ls; STR NumId* _numId; _Rs* __rs;} op0;
    STR {_V_id* __v_id;} op1;
  }u;
  int tag;
} IdArr;
typedef struct {
  union {
    STR {STR MatAttr* _matAttr;} op0;
    STR {STR IndexAttr* _indexAttr;} op1;
    STR {STR SimpleAttr* _simpleAttr;} op2;
  }u;
  int tag;
} AttrVar;
typedef struct {
  union {
    STR {_V_id* __v_id; _Attr* __attr; STR Expr* _expr; _Semi_colon* __semi_colon;} op0;
  }u;
  int tag;
} SimpleAttr;
typedef struct {
  union {
    STR {_V_id* __v_id; _Ls* __ls; STR NumId* _numId; _Rs* __rs; _Attr* __attr; STR Expr* _expr; _Semi_colon* __semi_colon;} op0;
  }u;
  int tag;
} IndexAttr;
typedef struct {
  union {
    STR {_V_id* __v_id; _Attr* __attr; _Ls* __ls; STR NumListList* _numListList; _Rs* __rs;} op0;
    STR {_V_id* __v_id; _Ls* __ls; STR NumId* _numId; _Rs* __rs; _Attr* __attr; _Lc* __lc; STR NumList* _numList; _Rc* __rc;} op1;
    STR {_V_id* __v_id; _Ls* __ls0; STR NumId* _numId0; _Rs* __rs0; _Ls* __ls1; STR NumId* _numId1; _Rs* __rs1; _Attr* __attr; STR Expr* _expr;} op2;
  }u;
  int tag;
} MatAttr;
typedef struct {
  union {
    STR {STR NumListList* _numListList; _Lc* __lc; STR NumList* _numList; _Rc* __rc;} op0;
    STR {STR NumList* _numList;} op1;
  }u;
  int tag;
} NumListList;
typedef struct {
  union {
    STR {STR NumList* _numList; STR Num* _num;} op0;
    STR {STR Num* _num;} op1;
    STR {_V_id* __v_id;} op2;
  }u;
  int tag;
} NumList;
typedef struct {
  union {
    STR {_Return* __return; STR Expr* _expr; _Semi_colon* __semi_colon;} op0;
    STR {_Copy* __copy; _Lp* __lp; _V_id* __v_id0; _V_id* __v_id1; _Rp* __rp; _Semi_colon* __semi_colon;} op1;
    STR {_Read* __read; _Lp* __lp; _V_id* __v_id; _Ls* __ls0; STR NumId* _numId0; _Rs* __rs0; _Ls* __ls1; STR NumId* _numId1; _Rs* __rs1; _Rp* __rp; _Semi_colon* __semi_colon;} op2;
    STR {_Read* __read; _Lp* __lp; _V_id* __v_id; _Ls* __ls; STR NumId* _numId; _Rs* __rs; _Rp* __rp; _Semi_colon* __semi_colon;} op3;
    STR {_Read* __read; _Lp* __lp; _V_id* __v_id; _Rp* __rp; _Semi_colon* __semi_colon;} op4;
    STR {_Print* __print; STR Expr* _expr; _Semi_colon* __semi_colon;} op5;
    STR {STR Call* _call; _Semi_colon* __semi_colon;} op6;
    STR {STR DeclVar* _declVar; _Semi_colon* __semi_colon;} op7;
    STR {STR AttrVar* _attrVar; _Semi_colon* __semi_colon;} op8;
    STR {STR FlowControl* _flowControl;} op9;
    STR {STR Loop* _loop;} op10;
  }u;
  int tag;
} Stmt;
typedef struct {
  union {
    STR {_Void* __void;} op0;
    STR {STR ParamList* _paramList;} op1;
  }u;
  int tag;
} ParamListVoid;
typedef struct {
  union {
    STR {STR ParamList* _paramList; STR Param* _param;} op0;
    STR {STR Param* _param;} op1;
  }u;
  int tag;
} ParamList;
typedef struct {
  union {
    STR {STR BaseType* _baseType; _V_id* __v_id;} op0;
    STR {_Mat_type* __mat_type; STR BaseType* _baseType; _V_id* __v_id;} op1;
  }u;
  int tag;
} Param;
typedef struct {
  union {
    STR {_While* __while; _Lp* __lp; STR Expr* _expr; _Rp* __rp; STR Block* _block;} op0;
  }u;
  int tag;
} Loop;
typedef struct {
  union {
    STR {_If* __if; _Lp* __lp; STR Expr* _expr; _Rp* __rp; STR Block* _block; _Else* __else; STR FlowControl* _flowControl;} op0;
    STR {_If* __if; _Lp* __lp; STR Expr* _expr; _Rp* __rp; STR Block* _block0; _Else* __else; STR Block* _block1;} op1;
    STR {_If* __if; _Lp* __lp; STR Error* _error; _Rp* __rp; STR Block* _block0; _Else* __else; STR Block* _block1;} op2;
    STR {_If* __if; _Lp* __lp; STR Expr* _expr; STR Error* _error; STR Block* _block0; _Else* __else; STR Block* _block1;} op3;
  }u;
  int tag;
} FlowControl;
typedef struct {
  union {
    STR {_Lc* __lc; STR StmtList* _stmtList; _Rc* __rc;} op0;
    STR {_Lc* __lc; _Rc* __rc;} op1;
  }u;
  int tag;
} Block;
typedef struct {
  union {
    STR {STR StmtList* _stmtList; Stmt* _stmt;} op0;
    STR {Stmt* _stmt;} op1;
  }u;
  int tag;
} StmtList;
typedef struct {
  union {
    STR {STR AddExpr* _addExpr0; STR Relop* _relop; STR AddExpr* _addExpr1;} op0;
    STR {STR AddExpr* _addExpr;} op1;
  }u;
  int tag;
} Expr;
typedef struct {
  union {
    STR {_Le* __le;} op0;
    STR {_Ge* __ge;} op1;
    STR {_Neq* __neq;} op2;
    STR {_Eq* __eq;} op3;
    STR {_Gt* __gt;} op4;
    STR {_Lt* __lt;} op5;
  }u;
  int tag;
} Relop;
typedef struct {
  union {
    STR {STR AddExpr* _addExpr; STR Addop* _addop; STR Term* _term;} op0;
    STR {STR Term* _term;} op1;
  }u;
  int tag;
} AddExpr;
typedef struct {
  union {
    STR {_Add* __add;} op0;
    STR {_Sub* __sub;} op1;
  }u;
  int tag;
} Addop;
typedef struct {
  union {
    STR {STR Term* _term; STR Mulop* _mulop; STR Bin* _bin;} op0;
    STR {STR Bin* _bin;} op1;
  }u;
  int tag;
} Term;
typedef struct {
  union {
    STR {_Mat_mul* __mat_mul;} op0;
    STR {_Mul* __mul;} op1;
    STR {_Div* __div;} op2;
    STR {_Mat_pow* __mat_pow;} op3;
  }u;
  int tag;
} Mulop;
typedef struct {
  union {
    STR {STR Bin* _bin; STR BinLogi* _binLogi; STR Unary* _unary;} op0;
    STR {STR Unary* _unary;} op1;
  }u;
  int tag;
} Bin;
typedef struct {
  union {
    STR {_And* __and;} op0;
    STR {_Or* __or;} op1;
  }u;
  int tag;
} BinLogi;
typedef struct {
  union {
    STR {STR UnaryOp* _unaryOp; STR Factor* _factor;} op0;
    STR {STR Factor* _factor;} op1;
  }u;
  int tag;
} Unary;
typedef struct {
  union {
    STR {_Not* __not;} op0;
    STR {_Addr* __addr;} op1;
  }u;
  int tag;
} UnaryOp;
typedef struct {
  union {
    STR {_Lp* __lp; STR Expr* _expr; _Rp* __rp;} op0;
    STR {STR Aux* _aux;} op1;
    STR {STR Call* _call;} op2;
    STR {STR Ascii* ascii;} op3;
  }u;
  int tag;
} Factor;
typedef struct {
  union {
    STR {_V_id* __v_id; _Ls* __ls0; STR Expr* _expr0; _Rs* __rs0; _Ls* __ls1; STR Expr* _expr1; _Rs* __rs1;} op0;
    STR {_V_id* __v_id; _Ls* __ls; STR Expr* _expr; _Rs* __rs;} op1;
    STR {STR NumId* _numId;} op2;
  }u;
  int tag;
} Aux;
typedef struct {
  union {
    STR {STR Num* _num;} op0;
    STR {_V_id* __v_id;} op1;
  }u;
  int tag;
} NumId;
typedef struct {
  union {
    STR {_V_id* __v_id; _Lp* __lp; STR ArgList* _argList; _Rp* __rp;} op0;
    STR {_V_id* __v_id; _Lp* __lp; _Void* __void; _Rp* __rp;} op1;
  }u;
  int tag;
} Call;
typedef struct {
  union {
    STR {STR ArgList* _argList; _Comma* __comma; STR Arg* _arg;} op0;
    STR {STR Arg* _arg;} op1;
  }u;
  int tag;
} ArgList;
typedef struct {
  union {
    STR {STR MatArg* _matArg;} op0;
    STR {STR Aux* _aux;} op1;
  }u;
  int tag;
} Arg;
typedef struct {
  union {
    STR {_V_id* __v_id; STR NumId* _numId0; STR NumId* _numId1;} op0;
  }u;
  int tag;
} MatArg;
typedef struct {
  union {
    STR {_V_ascii* __v_ascii;} op0;
  }u;
  int tag;
} Ascii;
typedef struct {
  union {
    STR {_Char_type* __char_type;} op0;
    STR {_Int_type* __int_type;} op1;
    STR {_Float_type* __float_type;} op2;
  }u;
  int tag;
} BaseType;
typedef struct {
  union {
    STR {_V_float* __v_float;} op0;
    STR {_V_int* __v_int;} op1;
  }u;
  int tag;
} Num;
