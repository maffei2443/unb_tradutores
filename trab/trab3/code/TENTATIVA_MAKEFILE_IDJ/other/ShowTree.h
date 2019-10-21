#include "Types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum MULOP {  MAT_MUL = 0, MUL, DIV};
enum RELOP {LE = 0, GE, NEQ, EQ, GT, LT };
enum BIN_LOGI {AND = 0, OR};
enum ADDOP {ADD = 0, SUB};
void nSpaces(int qtd);

void showNodeProgram(Program* no, int lvl);
void showNodeGlobalStmtList(GlobalStmtList* no, int lvl);
void showNodeGlobalStmt(GlobalStmt* no, int lvl);
void showNodeMatType(MatType* no, int lvl);
void showNodeDefFun(DefFun* no, int lvl);
void showNodeDeclFun(DeclFun* no, int lvl);
void showNodeDeclVar(DeclVar* no, int lvl);
void showNodeIdArr(IdArr* no, int lvl);
void showNodeAttrVar(AttrVar* no, int lvl);
void showNodeSimpleAttr(SimpleAttr* no, int lvl);
void showNodeIndexAttr(IndexAttr* no, int lvl);
void showNodeMatAttr(MatAttr* no, int lvl);
void showNodeNumListList(NumListList* no, int lvl);
void showNodeNumList(NumList* no, int lvl);
void showNodeStmt(Stmt* no, int lvl);
void showNodeParamListVoid(ParamListVoid* no, int lvl);
void showNodeParamList(ParamList* no, int lvl);
void showNodeParam(Param* no, int lvl);
void showNodeLoop(Loop* no, int lvl);
void showNodeFlowControl(FlowControl* no, int lvl);
void showNodeBlock(Block* no, int lvl);
void showNodeStmtList(StmtList* no, int lvl);
void showNodeExpr(Expr* no, int lvl);
void showNodeRelop(Relop* no, int lvl);
void showNodeAddExpr(AddExpr* no, int lvl);
void showNodeAddop(Addop* no, int lvl);
void showNodeTerm(Term* no, int lvl);
void showNodeMulop(Mulop* no, int lvl);
void showNodeBin(Bin* no, int lvl);
void showNodeBinLogi(BinLogi* no, int lvl);
void showNodeUnary(Unary* no, int lvl);
void showNodeUnaryOp(UnaryOp* no, int lvl);
void showNodeFactor(Factor* no, int lvl);
void showNodeAux(Aux* no, int lvl);
void showNodeNumId(NumId* no, int lvl);
void showNodeCall(Call* no, int lvl);
void showNodeArgList(ArgList* no, int lvl);
void showNodeArg(Arg* no, int lvl);
void showNodeMatArg(MatArg* no, int lvl);
void showNodeAscii(Ascii* no, int lvl);
void showNodeBaseType(BaseType* no, int lvl);
void showNodeNum(Num* no, int lvl);

// Daqui para baixo, coisas que sao terminais como ID
void showNodeId(Id* id, int lvl);
void showNodeBaseType();
void showId(char* sval);
void showError(char* e);
void showMulOp(int op);
void showAddOp(int op);
void showRelOp(int op);
void showInt(int num);
void showFloat(float num);
void showChar(char c);
void showBaseType(char c);  // demultiplexar entre 'int', 'float' e 'char'. Pelo primeiro caractere
void showBinLogi(int op);