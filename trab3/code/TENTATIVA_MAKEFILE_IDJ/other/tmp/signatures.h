// Program* make_Program_op0(GlobalStmtList* _globalStmtList){}
// GlobalStmtList* make_GlobalStmtList_op0(GlobalStmtList* _globalStmtList, GlobalStmt* _globalStmt){}
// GlobalStmtList* make_GlobalStmtList_op1(GlobalStmt* _globalStmt){}
// GlobalStmt* make_GlobalStmt_op0(DeclFun* _declFun){}
// GlobalStmt* make_GlobalStmt_op1(DefFun* _defFun, Error* _error){}
// GlobalStmt* make_GlobalStmt_op2(DefFun* _defFun){}
// GlobalStmt* make_GlobalStmt_op3(DeclVar* _declVar, _Semi_colon* __semi_colon){}
// GlobalStmt* make_GlobalStmt_op4(DeclVar* _declVar, Error* _error){}
// GlobalStmt* make_GlobalStmt_op5(AttrVar* _attrVar, _Semi_colon* __semi_colon){}
// GlobalStmt* make_GlobalStmt_op6(Block* _block){}
// DefFun* make_DefFun_op0(BaseType* _baseType, _V_id* __v_id, _Lp* __lp, ParamListVoid* _paramListVoid, _Rp* __rp, Block* _block){}
// DeclFun* make_DeclFun_op0(_Ahead* __ahead, BaseType* _baseType, _V_id* __v_id, _Lp* __lp, ParamListVoid* _paramListVoid, _Rp* __rp, _Semi_colon* __semi_colon){}
// DeclVar* make_DeclVar_op0(_Mat_type* __mat_type, BaseType* _baseType, _V_id* __v_id, _Ls* __ls, Num* _num, _Rs* __rs, _Ls* __ls, Num* _num, _Rs* __rs){}
// DeclVar* make_DeclVar_op1(BaseType* _baseType, IdArr* _idArr){}
// IdArr* make_IdArr_op0(_V_id* __v_id, _Ls* __ls, NumId* _numId, _Rs* __rs){}
// IdArr* make_IdArr_op1(_V_id* __v_id){}
// AttrVar* make_AttrVar_op0(MatAttr* _matAttr){}
// AttrVar* make_AttrVar_op1(IndexAttr* _indexAttr){}
// AttrVar* make_AttrVar_op2(SimpleAttr* _simpleAttr){}
// SimpleAttr* make_SimpleAttr_op0(_V_id* __v_id, _Attr* __attr, Expr* _expr, _Semi_colon* __semi_colon){}
// IndexAttr* make_IndexAttr_op0(_V_id* __v_id, _Ls* __ls, NumId* _numId, _Rs* __rs, _Attr* __attr, Expr* _expr, _Semi_colon* __semi_colon){}
// MatAttr* make_MatAttr_op0(_V_id* __v_id, _Attr* __attr, _Ls* __ls, NumListList* _numListList, _Rs* __rs){}
// MatAttr* make_MatAttr_op1(_V_id* __v_id, _Ls* __ls, NumId* _numId, _Rs* __rs, _Attr* __attr, _Lc* __lc, NumList* _numList, _Rc* __rc){}
// MatAttr* make_MatAttr_op2(_V_id* __v_id, _Ls* __ls, NumId* _numId, _Rs* __rs, _Ls* __ls, NumId* _numId, _Rs* __rs, _Attr* __attr, Expr* _expr){}
// NumListList* make_NumListList_op0(NumListList* _numListList, _Lc* __lc, NumList* _numList, _Rc* __rc){}
// NumListList* make_NumListList_op1(NumList* _numList){}
// NumList* make_NumList_op0(NumList* _numList, Num* _num){}
// NumList* make_NumList_op1(Num* _num){}
// NumList* make_NumList_op2(_V_id* __v_id){}
// Stmt* make_Stmt_op0(_Return* __return, Expr* _expr, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op1(_Copy* __copy, _Lp* __lp, _V_id* __v_id, _V_id* __v_id, _Rp* __rp, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op2(_Read* __read, _Lp* __lp, _V_id* __v_id, _Ls* __ls, NumId* _numId, _Rs* __rs, _Ls* __ls, NumId* _numId, _Rs* __rs, _Rp* __rp, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op3(_Read* __read, _Lp* __lp, _V_id* __v_id, _Ls* __ls, NumId* _numId, _Rs* __rs, _Rp* __rp, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op4(_Read* __read, _Lp* __lp, _V_id* __v_id, _Rp* __rp, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op5(_Print* __print, Expr* _expr, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op6(Call* _call, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op7(DeclVar* _declVar, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op8(AttrVar* _attrVar, _Semi_colon* __semi_colon){}
// Stmt* make_Stmt_op9(FlowControl* _flowControl){}
// Stmt* make_Stmt_op10(Loop* _loop){}
// ParamListVoid* make_ParamListVoid_op0(_Void* __void){}
// ParamListVoid* make_ParamListVoid_op1(ParamList* _paramList){}
// ParamList* make_ParamList_op0(ParamList* _paramList, Param* _param){}
// ParamList* make_ParamList_op1(Param* _param){}
// Param* make_Param_op0(BaseType* _baseType, _V_id* __v_id){}
// Param* make_Param_op1(_Mat_type* __mat_type, BaseType* _baseType, _V_id* __v_id){}
// Loop* make_Loop_op0(_While* __while, _Lp* __lp, Expr* _expr, _Rp* __rp, Block* _block){}
// FlowControl* make_FlowControl_op0(_If* __if, _Lp* __lp, Expr* _expr, _Rp* __rp, Block* _block, _Else* __else, FlowControl* _flowControl){}
// FlowControl* make_FlowControl_op1(_If* __if, _Lp* __lp, Expr* _expr, _Rp* __rp, Block* _block, _Else* __else, Block* _block){}
// FlowControl* make_FlowControl_op2(_If* __if, _Lp* __lp, Error* _error, _Rp* __rp, Block* _block, _Else* __else, Block* _block){}
// FlowControl* make_FlowControl_op3(_If* __if, _Lp* __lp, Expr* _expr, Error* _error, Block* _block, _Else* __else, Block* _block){}
// Block* make_Block_op0(_Lc* __lc, StmtList* _stmtList, _Rc* __rc){}
// Block* make_Block_op1(_Lc* __lc, _Rc* __rc){}
// StmtList* make_StmtList_op0(StmtList* _stmtList, Stmt* _stmt){}
// StmtList* make_StmtList_op1(Stmt* _stmt){}
// Expr* make_Expr_op0(AddExpr* _addExpr, Relop* _relop, AddExpr* _addExpr){}
// Expr* make_Expr_op1(AddExpr* _addExpr){}
// Relop* make_Relop_op0(_Le* __le){}
// Relop* make_Relop_op1(_Ge* __ge){}
// Relop* make_Relop_op2(_Neq* __neq){}
// Relop* make_Relop_op3(_Eq* __eq){}
// Relop* make_Relop_op4(_Gt* __gt){}
// Relop* make_Relop_op5(_Lt* __lt){}
// AddExpr* make_AddExpr_op0(AddExpr* _addExpr, Addop* _addop, Term* _term){}
// AddExpr* make_AddExpr_op1(Term* _term){}
// Addop* make_Addop_op0(_Add* __add){}
// Addop* make_Addop_op1(_Sub* __sub){}
// Term* make_Term_op0(Term* _term, Mulop* _mulop, Bin* _bin){}
// Term* make_Term_op1(Bin* _bin){}
// Mulop* make_Mulop_op0(_Mat_mul* __mat_mul){}
// Mulop* make_Mulop_op1(_Mul* __mul){}
// Mulop* make_Mulop_op2(_Div* __div){}
// Mulop* make_Mulop_op3(_Mat_pow* __mat_pow){}
// Bin* make_Bin_op0(Bin* _bin, BinLogi* _binLogi, Unary* _unary){}
// Bin* make_Bin_op1(Unary* _unary){}
// BinLogi* make_BinLogi_op0(_And* __and){}
// BinLogi* make_BinLogi_op1(_Or* __or){}
// Unary* make_Unary_op0(UnaryOp* _unaryOp, Factor* _factor){}
// Unary* make_Unary_op1(Factor* _factor){}
// UnaryOp* make_UnaryOp_op0(_Not* __not){}
// UnaryOp* make_UnaryOp_op1(_Addr* __addr){}
// Factor* make_Factor_op0(_Lp* __lp, Expr* _expr, _Rp* __rp){}
// Factor* make_Factor_op1(Aux* _aux){}
// Factor* make_Factor_op2(Call* _call){}
// Factor* make_Factor_op3('\''ascii'\''* _'\''ascii'\''){}
// Aux* make_Aux_op0(_V_id* __v_id, _Ls* __ls, Expr* _expr, _Rs* __rs, _Ls* __ls, Expr* _expr, _Rs* __rs){}
// Aux* make_Aux_op1(_V_id* __v_id, _Ls* __ls, Expr* _expr, _Rs* __rs){}
// Aux* make_Aux_op2(NumId* _numId){}
// NumId* make_NumId_op0(Num* _num){}
// NumId* make_NumId_op1(_V_id* __v_id){}
// Call* make_Call_op0(_V_id* __v_id, _Lp* __lp, ArgList* _argList, _Rp* __rp){}
// Call* make_Call_op1(_V_id* __v_id, _Lp* __lp, _Void* __void, _Rp* __rp){}
// ArgList* make_ArgList_op0(ArgList* _argList, _Comma* __comma, Arg* _arg){}
// ArgList* make_ArgList_op1(Arg* _arg){}
// Arg* make_Arg_op0(MatArg* _matArg){}
// Arg* make_Arg_op1(Aux* _aux){}
// MatArg* make_MatArg_op0(_V_id* __v_id, NumId* _numId, NumId* _numId){}
// Ascii* make_Ascii_op0('\''* _'\'', _V_ascii* __v_ascii, '\''* _'\''){}
// BaseType* make_BaseType_op0(_Char_type* __char_type){}
// BaseType* make_BaseType_op1(_Int_type* __int_type){}
// BaseType* make_BaseType_op2(_Float_type* __float_type){}
// Num* make_Num_op0(_V_float* __v_float){}
// Num* make_Num_op1(_V_int* __v_int){}
