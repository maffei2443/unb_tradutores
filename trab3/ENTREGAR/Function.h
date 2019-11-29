#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Types.h"
#include <stdlib.h>
#define STR struct

typedef struct {
  void * prev;
} List;
List* InitList();
// void FreeList(List* last);
Program* make_Program_op0(GlobalStmtList* globalStmtList) ;
GlobalStmtList* make_GlobalStmtList_op0(GlobalStmtList* globalStmtList, GlobalStmt* globalStmt);
GlobalStmtList* make_GlobalStmtList_op1(GlobalStmt* globalStmt);
GlobalStmt* make_GlobalStmt_op0(DeclFun* declFun);
GlobalStmt* make_GlobalStmt_op1(DefFun* defFun, Error* error);
GlobalStmt* make_GlobalStmt_op2(DefFun* defFun);
GlobalStmt* make_GlobalStmt_op3(DeclVar* declVar);
GlobalStmt* make_GlobalStmt_op4(DeclVar* declVar, Error* error);
GlobalStmt* make_GlobalStmt_op5(AttrVar* attrVar);
GlobalStmt* make_GlobalStmt_op6(Block* block);
DefFun* make_DefFun_op0(BaseType* baseType, char* id, ParamListVoid* paramListVoid, Block* block);
DeclFun* make_DeclFun_op0( BaseType* baseType, char* id, ParamListVoid* paramListVoid);
DeclVar* make_DeclVar_op0(BaseType* baseType, char* id,  Num* num0,  Num* num1);
DeclVar* make_DeclVar_op1(BaseType* baseType, IdArr* idArr);
IdArr* make_IdArr_op0(char* id,  NumId* numId);
IdArr* make_IdArr_op1(char* id);
AttrVar* make_AttrVar_op0(MatAttr* matAttr);
AttrVar* make_AttrVar_op1(IndexAttr* indexAttr);
AttrVar* make_AttrVar_op2(SimpleAttr* simpleAttr);
SimpleAttr* make_SimpleAttr_op0(char* id, Expr* expr);
IndexAttr* make_IndexAttr_op0(char* id,  NumId* numId, Expr* expr);
MatAttr* make_MatAttr_op0(char* id,  NumListList* numListList);
MatAttr* make_MatAttr_op1(char* id,  NumId* numId,  NumList* numList);
MatAttr* make_MatAttr_op2(char* id,  NumId* numId0,  NumId* numId1, Expr* expr);
NumListList* make_NumListList_op0(NumListList* numListList,  NumList* numList);
NumListList* make_NumListList_op1(NumList* numList);
NumList* make_NumList_op0(NumList* numList, Num* num);
NumList* make_NumList_op1(Num* num);
NumList* make_NumList_op2(char* id);
Stmt* make_Stmt_op0(Expr* expr);
Stmt* make_Stmt_op1(char* id0, char* id1);
Stmt* make_Stmt_op2( char* id,  NumId* numId0,  NumId* numId1);
Stmt* make_Stmt_op3( char* id,  NumId* numId);
Stmt* make_Stmt_op4( char* id);
Stmt* make_Stmt_op5(Expr* expr);
Stmt* make_Stmt_op6(Call* call);
Stmt* make_Stmt_op7(DeclVar* declVar);
Stmt* make_Stmt_op8(AttrVar* attrVar);
Stmt* make_Stmt_op9(FlowControl* flowControl);
Stmt* make_Stmt_op10(Loop* loop);
ParamListVoid* make_ParamListVoid_op0();
ParamListVoid* make_ParamListVoid_op1(ParamList* paramList);
ParamList* make_ParamList_op0(ParamList* paramList, Param* param);
ParamList* make_ParamList_op1(Param* param);
Param* make_Param_op0(BaseType* baseType, char* id);
Param* make_Param_op1(BaseType* baseType, char* id);
Loop* make_Loop_op0( Expr* expr, Block* block);
FlowControl* make_FlowControl_op0(Expr* expr, Block* block,  FlowControl* flowControl);
FlowControl* make_FlowControl_op1(Expr* expr, Block* block0,  Block* block1);
FlowControl* make_FlowControl_op2(Error* error, Block* block0,  Block* block1);
FlowControl* make_FlowControl_op3(Expr* expr, Error* error, Block* block0,  Block* block1);
Block* make_Block_op0( StmtList* stmtList);
Block* make_Block_op1();
StmtList* make_StmtList_op0(StmtList* stmtList, Stmt* stmt);
StmtList* make_StmtList_op1(Stmt* stmt);
Expr* make_Expr_op0(AddExpr* addExpr0, Relop* relop, AddExpr* addExpr1);
Expr* make_Expr_op1(AddExpr* addExpr);
Relop* make_Relop_op0();
Relop* make_Relop_op1();
Relop* make_Relop_op2();
Relop* make_Relop_op3();
Relop* make_Relop_op4();
Relop* make_Relop_op5();
AddExpr* make_AddExpr_op0(AddExpr* addExpr, Addop* addop, Term* term);
AddExpr* make_AddExpr_op1(Term* term);
Addop* make_Addop_op0();
Addop* make_Addop_op1();
Term* make_Term_op0(Term* term, Mulop* mulop, Bin* bin);
Term* make_Term_op1(Bin* bin);
Mulop* make_Mulop_op0();
Mulop* make_Mulop_op1();
Mulop* make_Mulop_op2();
Mulop* make_Mulop_op3();
Bin* make_Bin_op0(Bin* bin, BinLogi* binLogi, Unary* unary);
Bin* make_Bin_op1(Unary* unary);
BinLogi* make_BinLogi_op0();
BinLogi* make_BinLogi_op1();
Unary* make_Unary_op0(UnaryOp* unaryOp, Factor* factor);
Unary* make_Unary_op1(Factor* factor);
UnaryOp* make_UnaryOp_op0();
UnaryOp* make_UnaryOp_op1();
Factor* make_Factor_op0(Expr* expr);
Factor* make_Factor_op1(Aux* aux);
Factor* make_Factor_op2(Call* call);
Factor* make_Factor_op3(Ascii* ascii);
Aux* make_Aux_op0(char* id,  Expr* expr0,  Expr* expr1);
Aux* make_Aux_op1(char* id,  Expr* expr);
Aux* make_Aux_op2(NumId* numId);
NumId* make_NumId_op0(Num* num);
NumId* make_NumId_op1(char* id);
Call* make_Call_op0(char* id, ArgList* argList);
Call* make_Call_op1(char* id);
ArgList* make_ArgList_op0(ArgList* argList, Arg* arg);
ArgList* make_ArgList_op1(Arg* arg);
Arg* make_Arg_op0(MatArg* matArg);
Arg* make_Arg_op1(Aux* aux);
MatArg* make_MatArg_op0(char* id, int int0, int int1);
Ascii* make_Ascii_op0(char ascii);
BaseType* make_BaseType_op0();
BaseType* make_BaseType_op1();
BaseType* make_BaseType_op2();
Num* make_Num_op0(float fval);
Num* make_Num_op1(int ival);

#endif