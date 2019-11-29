typedef struct {
  union {
    struct {
      GlobalStmtList globalStmtList;
    }op1;
  } u;
}Program;

typedef struct {
  union {
    struct {GlobalStmtList globalStmtList; GlobalStmt globalStmt;}op1;
    struct {GlobalStmt globalStmt;}op2;
  } u;
}GlobalStmtList;

typedef struct {
  union {
    struct { DeclFun declFun;}op1;
    struct { DefFun defFun; char* error;}op2;
    struct { DefFun defFun;} op3;
    struct { DeclVar declVal;}op4;
    struct { DeclVar declVal; char* error;}op5;
    struct { AttrVar attrVar;}op6;
    struct { Block block;}op7;
  } u;
}GlobalStmt;

typedef struct {
  union {
    struct {
      BaseType baseType;
      ParamListVoid paramListVoid;
      Block block;
    }op1;
  } u;
}DefFun;

typedef struct {
  union {
    struct {
      BaseType baseType;
      ParamListVoid paramListVoid;
    }op1;
  } u;
}DeclFun;

typedef struct {
  union {
    struct {BaseType baseType; Num num[2];}op1;
    struct {BaseType baseType; IdArr idArr;}op2;
  } u;
}DeclVar;

typedef struct {
  union {
    struct {char* id; NumId numId;}op1;
    struct {char* id;}op2;
  } u;
}IdArr;

typedef struct {
  union {
    struct {MatAttr matAttr;}op1;
    struct {IndexAttr indexAttr;}op2;
    struct {SimpleAttr simpleAttr;}op3;
  } u;
}AttrVar;

typedef struct {
  union {
    struct {Expr expr;}op1;
  } u;
}SimpleAttr;

typedef struct {
  union {
    struct {char* id; NumId numId;}op1;
  } u;
}IndexAttr;

typedef struct {
  union {
    struct {char* id; NumListList numListList;}op1;
    struct {char* id; NumId numId; NumList numList;}op2;
    struct {char* id; NumId numId[2]; Expr expr;}op3;
  } u;
}MatAttr;

typedef struct {
  union {
    struct {struct NumListList * numListList; NumList numList;}op1;
    struct {NumList numList;}op2;
  } u;
}NumListList;

typedef struct {
  union {
    struct {struct NumList* numList; Num num;}op1;
    struct {Num num;}op2;
    struct {char id;}op3;
  } u;
}NumList;

typedef struct {
  union {
    struct {Expr expr;}op1;
    struct {char* id[2];}op2; // COPY
    struct {char* id; NumId numId[2];}op3;  // READ
    struct {char* id; NumId numId;}op4;  // READ 2
    
    struct {char* id;}op5;  // READ LP ID RP SEMI_COLON
    struct {Expr expr;}op6;  // PRINT expr ;
    struct {Call call}op7; // call
  } u;
}Stmt;

typedef struct {
  union {
    struct {
    }op1;
  } u;
}ParamListVoid;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}ParamList;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Param;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Loop;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}FlowControl;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Block;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}StmtList;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Expr;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Relop;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}AddExpr;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Addop;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Term;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Mulop;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Bin;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}BinLogi;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Unary;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}UnaryOp;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Factor;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Aux;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}NumId;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Call;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}ArgList;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Arg;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}MatArg;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}Ascii;

typedef struct {
  union {
    struct {

    }op1;
  } u;
}BaseType;

  union {
    struct {

    }op1;
  } u;typedef struct {

}Num;
