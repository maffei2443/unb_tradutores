#include "Function.h"
#include <stdio.h>

// 

List * gLast;
void FreeList(){
  List* ptr = gLast->prev;
  while(ptr != NULL) {
    ptr = gLast->prev;
    free(gLast);
    gLast = NULL;
    gLast = ptr;
  }
}
void AddList(void** newLast) {
  void** tmp = &gLast->prev;
  gLast = *newLast;
  gLast->prev = *tmp;
}
Program* make_Program_op0(GlobalStmtList* globalStmtList) {
  Program* no = malloc(sizeof(Program)); no->tag = 0;
  printf("make_Program_op0(GlobalStmtList* globalStmtList)\n");
  no->u.op0.globalStmtList = (GlobalStmtList*) globalStmtList;
  return no;
}
GlobalStmtList* make_GlobalStmtList_op0(GlobalStmtList* globalStmtList, GlobalStmt* globalStmt){
  GlobalStmtList* no = malloc(sizeof(GlobalStmtList)); no->tag = 0;
  no->u.op0.globalStmtList = globalStmtList;
  no->u.op0.globalStmt = globalStmt;
  printf("GlobalStmtList* make_GlobalStmtList_op0(GlobalStmtList* globalStmtList, GlobalStmt* globalStmt)\n");
  return no;
}
GlobalStmtList* make_GlobalStmtList_op1(GlobalStmt* globalStmt){
  GlobalStmtList* no = malloc(sizeof(GlobalStmtList)); no->tag = 1;
  no->u.op1.globalStmt = globalStmt;
  printf("GlobalStmtList* make_GlobalStmtList_op1(GlobalStmt* globalStmt)\n");
  return no;
}
GlobalStmt* make_GlobalStmt_op0(DeclFun* declFun){
  GlobalStmt* no = malloc(sizeof(GlobalStmt)); no->tag = 0;
  no->u.op0.declFun = declFun;
  printf("GlobalStmt* make_GlobalStmt_op0(DeclFun* declFun)\n");
  return no;
}
GlobalStmt* make_GlobalStmt_op1(DefFun* defFun, Error* error){
  GlobalStmt* no = malloc(sizeof(GlobalStmt)); no->tag = 1;
  no->u.op1.defFun = defFun;
  no->u.op1.error = error;
  printf("GlobalStmt* make_GlobalStmt_op1(DefFun* defFun, Error* error)\n");
  return no;
}
GlobalStmt* make_GlobalStmt_op2(DefFun* defFun){
  GlobalStmt* no = malloc(sizeof(GlobalStmt)); no->tag = 2;
  no->u.op2.defFun = defFun;
  printf("GlobalStmt* make_GlobalStmt_op2(DefFun* defFun)\n");
  return no;
}
GlobalStmt* make_GlobalStmt_op3(DeclVar* declVar){
  GlobalStmt* no = malloc(sizeof(GlobalStmt)); no->tag = 3;
  no->u.op3.declVar = declVar;
  printf("GlobalStmt* make_GlobalStmt_op3(DeclVar* declVar)\n");
  return no;
}
GlobalStmt* make_GlobalStmt_op4(DeclVar* declVar, Error* error){
  GlobalStmt* no = malloc(sizeof(GlobalStmt)); no->tag = 4;
  no->u.op4.declVar = declVar;
  no->u.op4.error = error;
  printf("GlobalStmt* make_GlobalStmt_op4(DeclVar* declVar, Error* error)\n");
  return no;
}
GlobalStmt* make_GlobalStmt_op5(AttrVar* attrVar){
  GlobalStmt* no = malloc(sizeof(GlobalStmt)); no->tag = 5;
  no->u.op5.attrVar = attrVar;
  printf("GlobalStmt* make_GlobalStmt_op5(AttrVar* attrVar)\n");
  return no;
}
GlobalStmt* make_GlobalStmt_op6(Block* block){
  GlobalStmt* no = malloc(sizeof(GlobalStmt)); no->tag = 6;
  no->u.op6.block = block;
  printf("GlobalStmt* make_GlobalStmt_op6(Block* block)\n");
  return no;
}
DefFun* make_DefFun_op0(BaseType* baseType, char* id, ParamListVoid* paramListVoid, Block* block){
  DefFun* no = malloc(sizeof(DefFun)); no->tag = 0;
  no->u.op0.baseType = baseType;
  no->u.op0.id = id;
  no->u.op0.paramListVoid = paramListVoid;
  no->u.op0.block = block;
  printf("DefFun* make_DefFun_op0(BaseType* baseType, char* id, ParamListVoid* paramListVoid, Block* block)\n");
  return no;
}
DeclFun* make_DeclFun_op0( BaseType* baseType, char* id, ParamListVoid* paramListVoid){
  DeclFun* no = malloc(sizeof(DeclFun)); no->tag = 0;
  no->u.op0.baseType = baseType;
  no->u.op0.id = id;
  no->u.op0.paramListVoid = paramListVoid;
  printf("DeclFun* make_DeclFun_op0( BaseType* baseType, char* id, ParamListVoid* paramListVoid)\n");
  return no;
}
DeclVar* make_DeclVar_op0(BaseType* baseType, char* id,  Num* num0,  Num* num1){
  DeclVar* no = malloc(sizeof(DeclVar)); no->tag = 0;
  no->u.op0.baseType = baseType;
  no->u.op0.id = id;
  no->u.op0.num0 = num0;
  no->u.op0.num1 = num1;
  printf("DeclVar* make_DeclVar_op0(BaseType* baseType, char* id,  Num* num0,  Num* num1)\n");
  return no;
}
DeclVar* make_DeclVar_op1(BaseType* baseType, IdArr* idArr){
  DeclVar* no = malloc(sizeof(DeclVar)); no->tag = 1;
  no->u.op1.baseType = baseType;
  no->u.op1.idArr = idArr;
  printf("DeclVar* make_DeclVar_op1(BaseType* baseType, IdArr* idArr)\n");
  return no;
}
IdArr* make_IdArr_op0(char* id,  NumId* numId){
  IdArr* no = malloc(sizeof(IdArr)); no->tag = 0;
  no->u.op0.id = id;
  printf("IdArr* make_IdArr_op0(char* id,  NumId* numId)\n");
  return no;
}
IdArr* make_IdArr_op1(char* id){
  IdArr* no = malloc(sizeof(IdArr)); no->tag = 1;
  no->u.op1.id = id;
  printf("IdArr* make_IdArr_op1(char* id)\n");
  return no;
}
AttrVar* make_AttrVar_op0(MatAttr* matAttr){
  AttrVar* no = malloc(sizeof(AttrVar)); no->tag = 0;
  no->u.op0.matAttr = matAttr;
  printf("AttrVar* make_AttrVar_op0(MatAttr* matAttr)\n");
  return no;
}
AttrVar* make_AttrVar_op1(IndexAttr* indexAttr){
  AttrVar* no = malloc(sizeof(AttrVar)); no->tag = 1;
  no->u.op1.indexAttr = indexAttr;
  printf("AttrVar* make_AttrVar_op1(IndexAttr* indexAttr)\n");
  return no;
}
AttrVar* make_AttrVar_op2(SimpleAttr* simpleAttr){
  AttrVar* no = malloc(sizeof(AttrVar)); no->tag = 2;
  no->u.op2.simpleAttr = simpleAttr;
  printf("AttrVar* make_AttrVar_op2(SimpleAttr* simpleAttr)\n");
  return no;
}
SimpleAttr* make_SimpleAttr_op0(char* id, Expr* expr){
  SimpleAttr* no = malloc(sizeof(SimpleAttr)); no->tag = 0;
  no->u.op0.id = id;
  no->u.op0.expr = expr;
  printf("SimpleAttr* make_SimpleAttr_op0(char* id, Expr* expr)\n");
  return no;
}
IndexAttr* make_IndexAttr_op0(char* id,  NumId* numId, Expr* expr){
  IndexAttr* no = malloc(sizeof(IndexAttr)); no->tag = 0;
  no->u.op0.id = id;
  no->u.op0.numId = numId;
  printf("IndexAttr* make_IndexAttr_op0(char* id,  NumId* numId, Expr* expr)\n");
  return no;
}
MatAttr* make_MatAttr_op0(char* id,  NumListList* numListList){
  MatAttr* no = malloc(sizeof(MatAttr)); no->tag = 0;
  no->u.op0.id = id;
  no->u.op0.numListList = numListList;
  
  printf("MatAttr* make_MatAttr_op0(char* id,  NumListList* numListList)\n");
  return no;
}
MatAttr* make_MatAttr_op1(char* id,  NumId* numId,  NumList* numList){
  MatAttr* no = malloc(sizeof(MatAttr)); no->tag = 1;
  no->u.op1.id = id;
  no->u.op1.numId = numId;
  no->u.op1.numList = numList;
  printf("MatAttr* make_MatAttr_op1(char* id,  NumId* numId,  NumList* numList)\n");
  return no;
}
MatAttr* make_MatAttr_op2(char* id,  NumId* numId0,  NumId* numId1, Expr* expr){
  MatAttr* no = malloc(sizeof(MatAttr)); no->tag = 2;
  no->u.op2.id = id;
  no->u.op2.numId0 = numId0;
  no->u.op2.numId1 = numId1;
  no->u.op2.expr = expr;
  printf("MatAttr* make_MatAttr_op2(char* id,  NumId* numId0,  NumId* numId1, Expr* expr)\n");
  return no;
}
NumListList* make_NumListList_op0(NumListList* numListList,  NumList* numList){
  NumListList* no = malloc(sizeof(NumListList)); no->tag = 0;
  no->u.op0.numListList = numListList;
  no->u.op0.numList = numList;
  printf("NumListList* make_NumListList_op0(NumListList* numListList,  NumList* numList)\n");
  return no;
}
NumListList* make_NumListList_op1(NumList* numList){
  NumListList* no = malloc(sizeof(NumListList)); no->tag = 1;
  no->u.op1.numList = numList;
  printf("NumListList* make_NumListList_op1(NumList* numList)\n");
  return no;
}
NumList* make_NumList_op0(NumList* numList, Num* num){
  NumList* no = malloc(sizeof(NumList)); no->tag = 0;
  no->u.op0.numList = numList;
  no->u.op0.num = num;
  printf("NumList* make_NumList_op0(NumList* numList, Num* num)\n");
  return no;
}
NumList* make_NumList_op1(Num* num){
  NumList* no = malloc(sizeof(NumList)); no->tag = 1;
  no->u.op1.num = num;
  printf("NumList* make_NumList_op1(Num* num)\n");
  return no;
}
NumList* make_NumList_op2(char* id){
  NumList* no = malloc(sizeof(NumList)); no->tag = 2;
  no->u.op2.id = id;
  printf("NumList* make_NumList_op2(char* id)\n");
  return no;
}
Stmt* make_Stmt_op0(Expr* expr){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 0;
  no->u.op0.expr = expr;
  printf("Stmt* make_Stmt_op0(Expr* expr)\n");
  return no;
}
Stmt* make_Stmt_op1(char* id0, char* id1){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 1;
  no->u.op1.id0 = id0;
  no->u.op1.id1 = id1;
  printf("Stmt* make_Stmt_op1(char* id, char* id1)\n");
  return no;
}
Stmt* make_Stmt_op2( char* id,  NumId* numId0,  NumId* numId1){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 2;
  no->u.op2.id = id ;
  no->u.op2.numId0 = numId0;
  no->u.op2.numId0 = numId1;
  printf("Stmt* make_Stmt_op2( char* id,  NumId* numId0,  NumId* numId1)\n");
  return no;
}
Stmt* make_Stmt_op3( char* id,  NumId* numId){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 3;
  no->u.op3.id = id;
  no->u.op3.numId = numId;
  printf("Stmt* make_Stmt_op3( char* id,  NumId* numId)\n");
  return no;
}
Stmt* make_Stmt_op4( char* id){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 4;
  no->u.op4.id = id;
  printf("Stmt* make_Stmt_op4( char* id)\n");
  return no;
}
Stmt* make_Stmt_op5(Expr* expr){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 5;
  no->u.op5.expr = expr;
  printf("Stmt* make_Stmt_op5(Expr* expr)\n");
  return no;
}
Stmt* make_Stmt_op6(Call* call){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 6;
  no->u.op6.call = call;
  printf("Stmt* make_Stmt_op6(Call* call)\n");
  return no;
}
Stmt* make_Stmt_op7(DeclVar* declVar){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 7;
  no->u.op7.declVar = declVar;
  printf("Stmt* make_Stmt_op7(DeclVar* declVar)\n");
  return no;
}
Stmt* make_Stmt_op8(AttrVar* attrVar){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 8;
  no->u.op8.attrVar = attrVar;
  printf("Stmt* make_Stmt_op8(AttrVar* attrVar)\n");
  return no;
}
Stmt* make_Stmt_op9(FlowControl* flowControl){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 9;
  no->u.op9.flowControl = flowControl;
  printf("Stmt* make_Stmt_op9(FlowControl* flowControl)\n");
  return no;
}
Stmt* make_Stmt_op10(Loop* loop){
  Stmt* no = malloc(sizeof(Stmt)); no->tag = 10;
  no->u.op10.loop = loop;
  printf("Stmt* make_Stmt_op10(Loop* loop)\n");
  return no;
}
ParamListVoid* make_ParamListVoid_op0(){
  ParamListVoid* no = malloc(sizeof(ParamListVoid)); no->tag = 0;
  
  printf("ParamListVoid* make_ParamListVoid_op0()\n");
  return no;
}
ParamListVoid* make_ParamListVoid_op1(ParamList* paramList){
  ParamListVoid* no = malloc(sizeof(ParamListVoid)); no->tag = 1;
  no->u.op1.paramList = paramList;
  printf("ParamListVoid* make_ParamListVoid_op1(ParamList* paramList)\n");
  return no;
}
ParamList* make_ParamList_op0(ParamList* paramList, Param* param){
  ParamList* no = malloc(sizeof(ParamList)); no->tag = 0;
  no->u.op0.paramList = paramList;
  no->u.op0.param = param;
  printf("ParamList* make_ParamList_op0(ParamList* paramList, Param* param)\n");
  return no;
}
ParamList* make_ParamList_op1(Param* param){
  ParamList* no = malloc(sizeof(ParamList)); no->tag = 1;
  no->u.op1.param = param;
  printf("ParamList* make_ParamList_op1(Param* param)\n");
  return no;
}
Param* make_Param_op0(BaseType* baseType, char* id){
  Param* no = malloc(sizeof(Param)); no->tag = 0;
  no->u.op0.baseType = baseType;
  no->u.op0.id = id;
  printf("Param* make_Param_op0(BaseType* baseType, char* id)\n");
  return no;
}
Param* make_Param_op1(BaseType* baseType, char* id){
  Param* no = malloc(sizeof(Param)); no->tag = 1;
  no->u.op1.baseType = baseType;
  no->u.op1.id = id;
  printf("Param* make_Param_op1(BaseType* baseType, char* id)\n");
  return no;
}
Loop* make_Loop_op0( Expr* expr, Block* block){
  Loop* no = malloc(sizeof(Loop)); no->tag = 0;
  no->u.op0.expr = expr;
  no->u.op0.block = block;
  printf("Loop* make_Loop_op0( Expr* expr, Block* block)\n");
  return no;
}
FlowControl* make_FlowControl_op0(Expr* expr, Block* block,  FlowControl* flowControl){
  FlowControl* no = malloc(sizeof(FlowControl)); no->tag = 0;
  no->u.op0.expr = expr;
  no->u.op0.block = block;
  no->u.op0.flowControl = flowControl;
  printf("FlowControl* make_FlowControl_op0(Expr* expr, Block* block,  FlowControl* flowControl)\n");
  return no;
}
FlowControl* make_FlowControl_op1(Expr* expr, Block* block0,  Block* block1){
  FlowControl* no = malloc(sizeof(FlowControl)); no->tag = 1;
  no->u.op1.expr = expr;
  no->u.op1.block0 = block0;
  no->u.op1.block1 = block1;
  printf("FlowControl* make_FlowControl_op1(Expr* expr, Block* block0,  Block* block1)\n");
  return no;
}
FlowControl* make_FlowControl_op2(Error* error, Block* block0,  Block* block1){
  FlowControl* no = malloc(sizeof(FlowControl)); no->tag = 2;
  no->u.op2.error = error;
  no->u.op2.block0 = block0;
  no->u.op2.block1 = block1;
  printf("FlowControl* make_FlowControl_op2(Error* error, Block* block0,  Block* block1)\n");
  return no;
}
FlowControl* make_FlowControl_op3(Expr* expr, Error* error, Block* block0,  Block* block1){
  FlowControl* no = malloc(sizeof(FlowControl)); no->tag = 3;
  no->u.op3.expr = expr;
  no->u.op3.error = error;
  no->u.op3.block0 = block0;
  no->u.op3.block1 = block1;
  printf("FlowControl* make_FlowControl_op3(Expr* expr, Error* error, Block* block0,  Block* block1)\n");
  return no;
}
Block* make_Block_op0( StmtList* stmtList){
  Block* no = malloc(sizeof(Block)); no->tag = 0;
  no->u.op0.stmtList = stmtList;
  printf("Block* make_Block_op0( StmtList* stmtList)\n");
  return no;
}
Block* make_Block_op1(){
  Block* no = malloc(sizeof(Block)); no->tag = 1;
  
  printf("Block* make_Block_op1()\n");
  return no;
}
StmtList* make_StmtList_op0(StmtList* stmtList, Stmt* stmt){
  StmtList* no = malloc(sizeof(StmtList)); no->tag = 0;
  no->u.op0.stmtList = stmtList;
  no->u.op0.stmt = stmt;
  printf("StmtList* make_StmtList_op0(StmtList* stmtList, Stmt* stmt)\n");
  return no;
}
StmtList* make_StmtList_op1(Stmt* stmt){
  StmtList* no = malloc(sizeof(StmtList)); no->tag = 1;
  no->u.op1.stmt = stmt;
  printf("StmtList* make_StmtList_op1(Stmt* stmt)\n");
  return no;
}
Expr* make_Expr_op0(AddExpr* addExpr0, Relop* relop, AddExpr* addExpr1){
  Expr* no = malloc(sizeof(Expr)); no->tag = 0;
  no->u.op0.addExpr0 = addExpr0;
  no->u.op0.relop = relop;
  no->u.op0.addExpr1 = addExpr1;
  printf("Expr* make_Expr_op0(AddExpr* addExpr0, Relop* relop, AddExpr* addExpr1)\n");
  return no;
}
Expr* make_Expr_op1(AddExpr* addExpr){
  Expr* no = malloc(sizeof(Expr)); no->tag = 1;
  no->u.op1.addExpr = addExpr;
  printf("Expr* make_Expr_op1(AddExpr* addExpr)\n");
  return no;
}
Relop* make_Relop_op0(){
  Relop* no = malloc(sizeof(Relop)); no->tag = 0;
  
  printf("Relop* make_Relop_op0()\n");
  return no;
}
Relop* make_Relop_op1(){
  Relop* no = malloc(sizeof(Relop)); no->tag = 1;
  printf("Relop* make_Relop_op1()\n");
  return no;
}
Relop* make_Relop_op2(){
  Relop* no = malloc(sizeof(Relop)); no->tag = 2;
  
  printf("Relop* make_Relop_op2()\n");
  return no;
}
Relop* make_Relop_op3(){
  Relop* no = malloc(sizeof(Relop)); no->tag = 3;
  
  printf("Relop* make_Relop_op3()\n");
  return no;
}
Relop* make_Relop_op4(){
  Relop* no = malloc(sizeof(Relop)); no->tag = 4;
  
  printf("Relop* make_Relop_op4()\n");
  return no;
}
Relop* make_Relop_op5(){
  Relop* no = malloc(sizeof(Relop)); no->tag = 5;
  
  printf("Relop* make_Relop_op5()\n");
  return no;
}
AddExpr* make_AddExpr_op0(AddExpr* addExpr, Addop* addop, Term* term){
  AddExpr* no = malloc(sizeof(AddExpr)); no->tag = 0;
  no->u.op0.addExpr = addExpr;
  no->u.op0.addop = addop;
  no->u.op0.term = term;
  printf("AddExpr* make_AddExpr_op0(AddExpr* addExpr, Addop* addop, Term* term)\n");
  return no;
}
AddExpr* make_AddExpr_op1(Term* term){
  AddExpr* no = malloc(sizeof(AddExpr)); no->tag = 1;
  no->u.op1.term = term;
  printf("AddExpr* make_AddExpr_op1(Term* term)\n");
  return no;
}
Addop* make_Addop_op0(){
  Addop* no = malloc(sizeof(Addop)); no->tag = 0;
  
  printf("Addop* make_Addop_op0()\n");
  return no;
}
Addop* make_Addop_op1(){
  Addop* no = malloc(sizeof(Addop)); no->tag = 1;
  
  printf("Addop* make_Addop_op1()\n");
  return no;
}
Term* make_Term_op0(Term* term, Mulop* mulop, Bin* bin){
  Term* no = malloc(sizeof(Term)); no->tag = 0;
  no->u.op0.term = term;
  no->u.op0.mulop = mulop;
  no->u.op0.bin = bin;
  printf("Term* make_Term_op0(Term* term, Mulop* mulop, Bin* bin)\n");
  return no;
}
Term* make_Term_op1(Bin* bin){
  Term* no = malloc(sizeof(Term)); no->tag = 1;
  no->u.op1.bin = bin;
  printf("Term* make_Term_op1(Bin* bin)\n");
  return no;
}
Mulop* make_Mulop_op0(){
  Mulop* no = malloc(sizeof(Mulop)); no->tag = 0;
  
  printf("Mulop* make_Mulop_op0()\n");
  return no;
}
Mulop* make_Mulop_op1(){
  Mulop* no = malloc(sizeof(Mulop)); no->tag = 1;
  
  printf("Mulop* make_Mulop_op1()\n");
  return no;
}
Mulop* make_Mulop_op2(){
  Mulop* no = malloc(sizeof(Mulop)); no->tag = 2;
  printf("Mulop* make_Mulop_op2()\n");
  return no;
}
Mulop* make_Mulop_op3(){
  Mulop* no = malloc(sizeof(Mulop)); no->tag = 3;
  
  printf("Mulop* make_Mulop_op3()\n");
  return no;
}
Bin* make_Bin_op0(Bin* bin, BinLogi* binLogi, Unary* unary){
  Bin* no = malloc(sizeof(Bin)); no->tag = 0;
  no->u.op0.bin = bin;
  no->u.op0.binLogi = binLogi;
  no->u.op0.unary = unary;
  printf("Bin* make_Bin_op0(Bin* bin, BinLogi* binLogi, Unary* unary)\n");
  return no;
}
Bin* make_Bin_op1(Unary* unary){
  Bin* no = malloc(sizeof(Bin)); no->tag = 1;
  no->u.op1.unary = unary;
  printf("Bin* make_Bin_op1(Unary* unary)\n");
  return no;
}
BinLogi* make_BinLogi_op0(){
  BinLogi* no = malloc(sizeof(BinLogi)); no->tag = 0;

  printf("BinLogi* make_BinLogi_op0()\n");
  return no;
}
BinLogi* make_BinLogi_op1(){
  BinLogi* no = malloc(sizeof(BinLogi)); no->tag = 1;
  printf("BinLogi* make_BinLogi_op1()\n");
  return no;
}
Unary* make_Unary_op0(UnaryOp* unaryOp, Factor* factor){
  Unary* no = malloc(sizeof(Unary)); no->tag = 0;
  no->u.op0.unaryOp = unaryOp;
  no->u.op0.factor = factor;
  printf("Unary* make_Unary_op0(UnaryOp* unaryOp, Factor* factor)\n");
  return no;
}
Unary* make_Unary_op1(Factor* factor){
  Unary* no = malloc(sizeof(Unary)); no->tag = 1;
  no->u.op1.factor = factor;
  printf("Unary* make_Unary_op1(Factor* factor)\n");
  return no;
}
UnaryOp* make_UnaryOp_op0(){
  UnaryOp* no = malloc(sizeof(UnaryOp)); no->tag = 0;
  printf("UnaryOp* make_UnaryOp_op0()\n");
  return no;
}
UnaryOp* make_UnaryOp_op1(){
  UnaryOp* no = malloc(sizeof(UnaryOp)); no->tag = 1;
  printf("UnaryOp* make_UnaryOp_op1()\n");
  return no;
}
Factor* make_Factor_op0(Expr* expr){
  Factor* no = malloc(sizeof(Factor)); no->tag = 0;
  no->u.op0.expr = expr;
  printf("Factor* make_Factor_op0(Expr* expr)\n");
  return no;
}
Factor* make_Factor_op1(Aux* aux){
  Factor* no = malloc(sizeof(Factor)); no->tag = 1;
  no->u.op1.aux = aux;
  printf("Factor* make_Factor_op1(Aux* aux)\n");
  return no;
}
Factor* make_Factor_op2(Call* call){
  Factor* no = malloc(sizeof(Factor)); no->tag = 2;
  no->u.op2.call = call;
  printf("Factor* make_Factor_op2(Call* call)\n");
  return no;
}
Factor* make_Factor_op3(Ascii* ascii){
  Factor* no = malloc(sizeof(Factor)); no->tag = 3;
  no->u.op3.ascii = ascii;
  printf("Factor* make_Factor_op3(Ascii* ascii)\n");
  return no;
}
Aux* make_Aux_op0(char* id,  Expr* expr0,  Expr* expr1){
  Aux* no = malloc(sizeof(Aux)); no->tag = 0;
  no->u.op0.id = id;
  no->u.op0.expr0 = expr0;
  no->u.op0.expr1 = expr1;
  printf("Aux* make_Aux_op0(char* id,  Expr* expr0,  Expr* expr1)\n");
  return no;
}
Aux* make_Aux_op1(char* id,  Expr* expr){
  Aux* no = malloc(sizeof(Aux)); no->tag = 1;
  no->u.op1.id = id;
  no->u.op1.expr = expr;
  printf("Aux* make_Aux_op1(char* id,  Expr* expr)\n");
  return no;
}
Aux* make_Aux_op2(NumId* numId){
  Aux* no = malloc(sizeof(Aux)); no->tag = 2;
  no->u.op2.numId = numId;
  printf("Aux* make_Aux_op2(NumId* numId)\n");
  return no;
}
NumId* make_NumId_op0(Num* num){
  NumId* no = malloc(sizeof(NumId)); no->tag = 0;
  no->u.op0.num = num;
  printf("NumId* make_NumId_op0(Num* num)\n");
  return no;
}
NumId* make_NumId_op1(char* id){
  NumId* no = malloc(sizeof(NumId)); no->tag = 1;
  no->u.op1.id = id;
  printf("NumId* make_NumId_op1(char* id)\n");
  return no;
}
Call* make_Call_op0(char* id, ArgList* argList){
  Call* no = malloc(sizeof(Call)); no->tag = 0;
  no->u.op0.id = id;
  no->u.op0.argList= argList;
  printf("Call* make_Call_op0(char* id, ArgList* argList)\n");
  return no;
}
Call* make_Call_op1(char* id){
  Call* no = malloc(sizeof(Call)); no->tag = 1;
  no->u.op1.id = id;
  printf("Call* make_Call_op1(char* id)\n");
  return no;
} 
ArgList* make_ArgList_op0(ArgList* argList, Arg* arg){
  ArgList* no = malloc(sizeof(ArgList)); no->tag = 0;
  no->u.op0.arg = arg;
  no->u.op0.argList = argList;
  printf("ArgList* make_ArgList_op0(ArgList* argList, Arg* arg)\n");
  return no;
}
ArgList* make_ArgList_op1(Arg* arg){
  ArgList* no = malloc(sizeof(ArgList)); no->tag = 1;
  no->u.op1.arg = arg;
  printf("ArgList* make_ArgList_op1(Arg* arg)\n");
  return no;
}
Arg* make_Arg_op0(MatArg* matArg){
  Arg* no = malloc(sizeof(Arg)); no->tag = 0;
  no->u.op0.matArg = matArg;
  printf("Arg* make_Arg_op0(MatArg* matArg)\n");
  return no;
}
Arg* make_Arg_op1(Aux* aux){
  Arg* no = malloc(sizeof(Arg)); no->tag = 1;
  no->u.op1.aux = aux;
  printf("Arg* make_Arg_op1(Aux* aux)\n");
  return no;
}
MatArg* make_MatArg_op0(char* id, int int0, int int1){
  MatArg* no = malloc(sizeof(MatArg)); no->tag = 0;
  no->u.op0.id = id;
  no->u.op0.int0 = int0;
  no->u.op0.int1 = int1;
  printf("MatArg* make_MatArg_op0(char* id, int int0, int int1)\n");
  return no;
}
Ascii* make_Ascii_op0(char ascii){
  Ascii* no = malloc(sizeof(Ascii)); no->tag = 0;
  no->u.op0.cval = ascii;
  printf("Ascii* make_Ascii_op0(Ascii* ascii)\n");
  return no;
}
BaseType* make_BaseType_op0(){
  BaseType* no = malloc(sizeof(BaseType)); no->tag = 0;
  printf("BaseType* make_BaseType_op0()\n");
  return no;
}
BaseType* make_BaseType_op1(){
  BaseType* no = malloc(sizeof(BaseType)); no->tag = 1;
  printf("BaseType* make_BaseType_op1()\n");
  return no;
}
BaseType* make_BaseType_op2(){
  BaseType* no = malloc(sizeof(BaseType)); no->tag = 2;
  printf("BaseType* make_BaseType_op2()\n");
  return no;
}
Num* make_Num_op0(float fval){
  Num* no = malloc(sizeof(Num)); no->tag = 0;
  no->u.op0.fval = fval;
  printf("Num* make_Num_op0(float fval)\n");
  return no;
}
Num* make_Num_op1(int ival){
  Num* no = malloc(sizeof(Num)); no->tag = 1;
  no->u.op1.ival = ival;
  printf("Num* make_Num_op1(int ival)\n");
  return no;
}
