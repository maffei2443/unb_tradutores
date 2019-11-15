#ifndef _TREE_H_
#define _TREE_H_
#include "Types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum tMULOP {  tMAT_MUL = 0, tMUL, tDIV};
enum tRELOP {tLE = 0, tGE, tNEQ, tEQ, tGT, tLT };
enum tBIN_LOGI {tAND = 0, tOR};
enum tADDOP {tADD = 0, tSUB};
enum tUNARYOP {tNOT = 0, tADDR};
void t_nSpaces(int qtd);

void t_showNodeProgram(Program* no, int lvl);
void t_showNodeGlobalStmtList(GlobalStmtList* no, int lvl);
void t_showNodeGlobalStmt(GlobalStmt* no, int lvl);
void t_showNodeMatType(MatType* no, int lvl);
void t_showNodeDefFun(DefFun* no, int lvl);
void t_showNodeDeclFun(DeclFun* no, int lvl);
void t_showNodeDeclVar(DeclVar* no, int lvl);
void t_showNodeIdArr(IdArr* no, int lvl);
void t_showNodeAttrVar(AttrVar* no, int lvl);
void t_showNodeSimpleAttr(SimpleAttr* no, int lvl);
void t_showNodeIndexAttr(IndexAttr* no, int lvl);
void t_showNodeMatAttr(MatAttr* no, int lvl);
void t_showNodeNumListList(NumListList* no, int lvl);
void t_showNodeNumList(NumList* no, int lvl);
void t_showNodeStmt(Stmt* no, int lvl);
void t_showNodeParamListVoid(ParamListVoid* no, int lvl);
void t_showNodeParamList(ParamList* no, int lvl);
void t_showNodeParam(Param* no, int lvl);
void t_showNodeLoop(Loop* no, int lvl);
void t_showNodeFlowControl(FlowControl* no, int lvl);
void t_showNodeBlock(Block* no, int lvl);
void t_showNodeStmtList(StmtList* no, int lvl);
void t_showNodeExpr(Expr* no, int lvl);
void t_showNodeRelop(Relop* no, int lvl);
void t_showNodeAddExpr(AddExpr* no, int lvl);
void t_showNodeAddop(Addop* no, int lvl);
void t_showNodeTerm(Term* no, int lvl);
void t_showNodeMulop(Mulop* no, int lvl);
void t_showNodeBin(Bin* no, int lvl);
void t_showNodeBinLogi(BinLogi* no, int lvl);
void t_showNodeUnary(Unary* no, int lvl);
void t_showNodeUnaryOp(UnaryOp* no, int lvl);
void t_showNodeFactor(Factor* no, int lvl);
void t_showNodeAux(Aux* no, int lvl);
void t_showNodeNumId(NumId* no, int lvl);
void t_showNodeCall(Call* no, int lvl);
void t_showNodeArgList(ArgList* no, int lvl);
void t_showNodeArg(Arg* no, int lvl);
void t_showNodeMatArg(MatArg* no, int lvl);
void t_showNodeAscii(Ascii* no, int lvl);
void t_showNodeBaseType(BaseType* no, int lvl);
void t_showNodeNum(Num* no, int lvl);

// Daqui para baixo, coisas que sao terminais como ID
void t_showNodeId(Id* id, int lvl);
void t_showNodeBaseType();
void t_showId(char* sval);
void t_showError(char* e);
void t_showMulOp(int op);
void t_showAddOp(int op);
void t_showRelOp(int op);
void t_showInt(int num);
void t_showFloat(float num);
void t_showChar(char c);
void t_showBaseType(char c);  // demultiplexar entre 'int', 'float' e 'char'. Pelo primeiro caractere
void t_showBinLogi(int op);
void t_showUnaryOp(int op);

#endif