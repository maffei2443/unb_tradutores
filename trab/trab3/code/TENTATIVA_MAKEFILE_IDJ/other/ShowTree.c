#include "ShowTree.h"

#include <stdio.h>
#include <stdlib.h>

void nSpaces(int qtd){
  char*  p = malloc(sizeof(char) * qtd+1);
  memset(p, ' ', qtd);
  p[qtd] = '\0';  
  printf(p);
  free(p);  p = NULL;
}

void showNodeProgram(Program* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      GlobalStmtList* s0 = no->u.op0.globalStmtList;
      showNodeGlobalStmtList(s0, lvl + 1);
      break;
    }
    default:{
      break;
    };
  }
  nSpaces(lvl * 2); printf("<Program>\n");

}
void showNodeGlobalStmtList(GlobalStmtList* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      GlobalStmtList* s0 = no->u.op0.globalStmtList; showNodeGlobalStmtList(s0, lvl + 1);
      GlobalStmt* s1 = no->u.op0.globalStmt; showNodeGlobalStmt(s1, lvl + 1);
      break;
    }
    default:{
      GlobalStmt* s1 = no->u.op0.globalStmt; showNodeGlobalStmt(s1, lvl + 1);
      break;
    }
  }
  nSpaces(lvl * 2); printf("<GlobalStmtList>\n");
}
void showNodeGlobalStmt(GlobalStmt* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      DeclFun* s0 = no->u.op0.declFun;  showNodeDeclFun(s0, lvl + 1);
      break;
    }
    case 1:{      
      DefFun* s1 = no->u.op1.defFun;  showNodeDefFun(s1, lvl + 1);
      nSpaces((lvl+1) * 2); showError(no->u.op1.error);
      break;
    }
    case 2:{
      DefFun* s2 = no->u.op2.defFun;  showNodeDefFun(s2, lvl + 1);      
      break;
    }
    case 3:{
      DeclVar* s3 = no->u.op3.declVar;  showNodeDeclVar(s3, lvl + 1);      
      break;
    }
    case 4:{
      DeclVar* s4 = no->u.op4.declVar;  showNodeDeclVar(s4, lvl + 1);
      nSpaces((lvl+1) * 2); showError(no->u.op4.error);    
      break;
    }
    case 5:{
      AttrVar* s5 = no->u.op5.attrVar;  showNodeAttrVar(s5, lvl + 1);
      break;
    }
    case 6:{
      Block* s6 = no->u.op6.block;  showNodeBlock(s6, lvl + 1);
      break;
    }
    default:
      break;
  }
  nSpaces(lvl * 2); printf("<global-stmt>\n");
}
void showNodeMatType(MatType* no, int lvl){
  switch (no->tag)
  {
    default:
      break;
  }
  nSpaces(lvl * 2); printf("<mat-type>\n");
}
void showNodeDefFun(DefFun* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      BaseType * baseType = no->u.op0.baseType; showNodeBaseType(baseType, lvl + 1);
      char * id = no->u.op0.id; showNodeBaseType(id, lvl + 1);
      ParamListVoid * paramListVoid = no->u.op0.paramListVoid; showNodeBaseType(paramListVoid, lvl + 1);
      Block* block = no->u.op0.block; showNodeBlock(block, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<def-fun>\n");
}
void showNodeDeclFun(DeclFun* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      BaseType* s0 = no->u.op0.baseType; showNodeBaseType(s0, lvl + 1);
      Id* s1 = no->u.op0.id; showId(s1);
      ParamListVoid* s2 = no->u.op0.paramListVoid; showNodeParamListVoid(s2, lvl + 1);  
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<decl-fun>\n");
}
void showNodeDeclVar(DeclVar* no, int lvl){
  switch (no->tag)
  {
    case 0:{      
      MatType* mat_type = no->u.op0.mat_type; showNodeMatType(mat_type, lvl + 1);
      BaseType* baseType = no->u.op0.baseType; nSpaces((lvl+1)*2); showBaseType(baseType->u.op0.ival);
      Id* id = no->u.op0.id; showNodeId(id, lvl + 1);
      Num* num0 = no->u.op0.num0; showNodeNum(num0, lvl + 1);
      Num* num1 = no->u.op0.num1; showNodeNum(num1, lvl + 1);
      break;
    }
    case 1:{      
      BaseType* baseType = no->u.op1.baseType; nSpaces((lvl+1)*2); showBaseType(baseType->u.op0.ival);
      IdArr* idArr = no->u.op1.idArr; showNodeIdArr(idArr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<decl-var>\n");
}
void showNodeIdArr(IdArr* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; showNodeId(id, lvl + 1);
      NumId* numId = no->u.op0.numId; showNodeNumId(numId, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; showNodeId(id, lvl + 1);
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<id-arr>\n");
}
void showNodeAttrVar(AttrVar* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      MatAttr* matAttr = no->u.op0.matAttr; showNodeMatAttr(matAttr, lvl + 1);
      break;
    }
    case 1:{      
      IndexAttr* indexAttr = no->u.op1.indexAttr; showNodeIndexAttr(indexAttr, lvl + 1);
      break;
    }
    case 2:{      
      SimpleAttr* simpleAttr = no->u.op2.simpleAttr; showNodeSimpleAttr(simpleAttr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<attr-var>\n");
}
void showNodeSimpleAttr(SimpleAttr* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; showId(id);
      Expr* expr = no->u.op0.expr; showNodeExpr(expr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<simple-attr>\n");
}
void showNodeIndexAttr(IndexAttr* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; showId(id);
      NumId* numId = no->u.op0.numId; showNodeNumId(numId, lvl + 1);
      Expr* expr = no->u.op0.expr; showNodeExpr(expr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<index-attr>\n");
}
void showNodeMatAttr(MatAttr* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; showNodeId(id, lvl + 1);
      NumListList* numListList = no->u.op0.numListList; showNodeNumListList(numListList, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; showNodeId(id, lvl + 1);
      NumId* numId = no->u.op1.numId; showNodeNumId(numId, lvl + 1);
      NumList* numList = no->u.op1.numList; showNodeNumList(numList, lvl + 1);
      break;
    }
    case 2:{
      Id* id = no->u.op2.id; showNodeId(id, lvl + 1);
      NumId* numId0 = no->u.op2.numId0; showNodeNumId(numId0, lvl + 1);
      NumId* numId1 = no->u.op2.numId1; showNodeNumId(numId1, lvl + 1);
      Expr* expr = no->u.op2.expr; showNodeExpr(expr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<mat-attr>\n");
}
void showNodeNumListList(NumListList* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      NumListList* numListList = no->u.op0.numListList; showNodeNumListList(numListList, lvl + 1);
      NumList* numList = no->u.op0.numList; showNodeNumList(numList, lvl + 1);
      break;
    }
    case 1:{
      NumList* numList = no->u.op1.numList; showNodeNumList(numList, lvl + 1);
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<num-list-list>\n");
}
void showNodeNumList(NumList* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      NumList* numList = no->u.op0.numList; showNodeNumList(numList, lvl + 1);
      Num* num = no->u.op0.num; showNodeNum(num, lvl + 1);
      break;
    }
    case 1:{
      Num* num = no->u.op1.num; showNodeNum(num, lvl + 1);
      break;
    }
    case 2:{
      Id* id = no->u.op2.id; showNodeId(id, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<num-list>\n");
}
void showNodeStmt(Stmt* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Expr* expr = no->u.op0.expr; showNodeExpr(expr, lvl + 1);
      break;
    }
    case 1:{
      Id* id0 = no->u.op1.id0; showNodeId(id0, lvl + 1);
      Id* id1 = no->u.op1.id1; showNodeId(id1, lvl + 1);
      break;
    }
    case 2:{
      Id* id = no->u.op2.id; showNodeId(id, lvl + 1);
      NumId* numId0 = no->u.op2.numId0; showNodeNumId(numId0, lvl + 1);
      NumId* numId1 = no->u.op2.numId1; showNodeNumId(numId1, lvl + 1);
      break;
    }
    case 3:{
      Id* id = no->u.op3.id; showNodeId(id, lvl + 1);
      NumId* numId = no->u.op3.numId; showNodeNumId(numId, lvl + 1);
      break;
    }
    case 4:{
      Id* id = no->u.op4.id; showNodeId(id, lvl + 1);
      break;
    }
    case 5:{
      Expr* expr = no->u.op5.expr; showNodeExpr(expr, lvl + 1);
      break;
    }
    case 6:{
      Call* call = no->u.op6.call; showNodeCall(call, lvl + 1);
      break;
    }
    case 7:{
      DeclVar* declVar = no->u.op7.declVar; showNodeDeclVar(declVar, lvl + 1);
      break;
    }
    case 8:{
      AttrVar* attrVar = no->u.op8.attrVar; showNodeAttrVar(attrVar, lvl + 1);
      break;
    }
    case 9:{
      FlowControl* flowControl = no->u.op9.flowControl; showNodeFlowControl(flowControl, lvl + 1);
    }
    case 10:{
      Loop* loop = no->u.op10.loop; showNodeLoop(loop, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<stmt>\n");
}
void showNodeParamListVoid(ParamListVoid* no, int lvl){
  switch (no->tag)
  {
    case 0:{  // dummy case
      nSpaces((lvl + 1)*2); printf("<void>\n");
      break;
    }
    case 1:{ 
      ParamList* paramList = no->u.op1.paramList; showNodeParamList(paramList, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<param-list-void>\n");
}
void showNodeParamList(ParamList* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      ParamList* paramList = no->u.op0.paramList; showNodeParamList(paramList, lvl + 1);
      Param* param = no->u.op0.param; showNodeParam(param, lvl + 1);
      break;
    }
    case 1:{
      Param* param = no->u.op1.param; showNodeParam(param, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<param-list>\n");
}
void showNodeParam(Param* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      BaseType* baseType = no->u.op0.baseType; showNodeBaseType(baseType, lvl + 1);
      Id* id = no->u.op0.id; showNodeId(id, lvl + 1);
      break;
    }
    case 1:{
      MatType* mat_type = no->u.op1.mat_type; showNodeMatType(mat_type, lvl + 1);
      BaseType* baseType = no->u.op1.baseType; showNodeBaseType(baseType, lvl + 1);
      Id* id = no->u.op1.id; showNodeId(id, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<param>\n");
}
void showNodeLoop(Loop* no, int lvl){
  switch (no->tag)
  {
    case 0:{      
      Expr* expr = no->u.op0.expr; showNodeExpr(expr, lvl + 1);
      Block* block = no->u.op0.block; showNodeBlock(block, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<loop>\n");
}
void showNodeFlowControl(FlowControl* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Expr* expr = no->u.op0.expr; showNodeExpr(expr, lvl + 1);
      Block* block = no->u.op0.block; showNodeBlock(block, lvl + 1);
      FlowControl* flowControl = no->u.op0.flowControl; showNodeFlowControl(flowControl, lvl + 1);
      break;
    }
    case 1:{
      Expr* expr = no->u.op1.expr; showNodeExpr(expr, lvl + 1);
      Block* block0 = no->u.op1.block0; showNodeBlock(block0, lvl + 1);
      Block* block1 = no->u.op1.block1; showNodeBlock(block1, lvl + 1);
      break;
    }
    case 2:{
      Error* error = no->u.op2.error; nSpaces((lvl + 1) * 2); showError(error);
      Block* block0 = no->u.op2.block0; showNodeBlock(block0, lvl + 1);
      Block* block1 = no->u.op2.block1; showNodeBlock(block1, lvl + 1);
      break;
    }
    case 3:{
      Expr* expr = no->u.op3.expr; showNodeExpr(expr, lvl + 1);
      Error* error = no->u.op3.error; nSpaces((lvl + 1) * 2); showError(error);
      Block* block0 = no->u.op3.block0; showNodeBlock(block0, lvl + 1);
      Block* block1 = no->u.op3.block1; showNodeBlock(block1, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<flow-control>\n");
}
void showNodeBlock(Block* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      StmtList* stmtList = no->u.op0.stmtList; showNodeStmtList(stmtList, lvl + 1); break;
    }
    case 1:{
      // Bloco vazio {}
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<block>\n");
}
void showNodeStmtList(StmtList* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      StmtList* stmtList = no->u.op0.stmtList; showNodeStmtList(stmtList, lvl + 1);
      Stmt* stmt = no->u.op0.stmt; showNodeStmt(stmt, lvl + 1);
      break;
    }
    case 1:{
      Stmt* stmt = no->u.op1.stmt; showNodeStmt(stmt, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<stmt-list>\n");
}
void showNodeExpr(Expr* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      AddExpr* addExpr0 = no->u.op0.addExpr0; showNodeAddExpr(addExpr0, lvl + 1);
      Relop* relop = no->u.op0.relop; showNodeRelop(relop, lvl + 1);
      AddExpr* addExpr1 = no->u.op0.addExpr1; showNodeAddExpr(addExpr1, lvl + 1);
      break;
    }
    case 1:{
      AddExpr* addExpr = no->u.op1.addExpr; showNodeAddExpr(addExpr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<expr>\n");
}
void showNodeRelop(Relop* no, int lvl){
  switch (no->tag)
  {
    default:{
      nSpaces( ( lvl + 1 ) * 2); showRelOp(no->tag);
      break;
    }
  }
  nSpaces(lvl * 2); printf("<relop>\n");
}
void showNodeAddExpr(AddExpr* no, int lvl){
  switch (no->tag)
  {
    case 0:{ 
      AddExpr* addExpr = no->u.op0.addExpr; showNodeAddExpr(addExpr, lvl + 1);
      Addop* addop = no->u.op0.addop; showNodeAddop(addop, lvl + 1);
      Term* term = no->u.op0.term; showNodeTerm(term, lvl + 1);
      break;
    }
    case 1:{ 
      Term* term = no->u.op1.term; showNodeTerm(term, lvl + 1);
      break;
    }
    default:{ // dummy
      break;
    }
  }
  nSpaces(lvl * 2); printf("<add-expr>\n");
}
void showNodeAddop(Addop* no, int lvl){
  switch (no->tag)
  {
    default:{
      nSpaces((lvl + 1) * 2); showAddOp(no->tag);
      break;
    }
  }
  nSpaces(lvl * 2); printf("<addop>\n");
}
void showNodeTerm(Term* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Mulop* mulop = no->u.op0.mulop; showNodeMulop(mulop, lvl + 1);
      Bin* bin = no->u.op0.bin; showNodeBin(bin, lvl + 1);
      break;
    }
    case 1:{
      Bin* bin = no->u.op1.bin; showNodeBin(bin, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<term>\n");
}
void showNodeMulop(Mulop* no, int lvl){
  switch (no->tag)
  {
    default:{ // dummy
      nSpaces((lvl + 1) * 2); showMulOp(no->tag);
      break;
    }
  }
  nSpaces(lvl * 2); printf("<mulop>\n");
}
void showNodeBin(Bin* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      BinLogi* binLogi = no->u.op0.binLogi; showNodeBinLogi(binLogi, lvl + 1);
      Unary* unary = no->u.op0.unary; showNodeUnary(unary, lvl + 1);
      break;
    }
    case 1:{
      Unary* unary = no->u.op1.unary; showNodeUnary(unary, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<bin>\n");
}
void showNodeBinLogi(BinLogi* no, int lvl){
  switch (no->tag)
  {
    default:{
      showBinLogi(no->tag);
      break;
    }
  }
  nSpaces(lvl * 2); printf("<bin-logi>\n");
}
void showNodeUnary(Unary* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      UnaryOp* unaryOp = no->u.op0.unaryOp; showNodeUnaryOp(unaryOp, lvl + 1);
      Factor* factor = no->u.op0.factor; showNodeFactor(factor, lvl + 1);
      break;
    }
    case 1:{
      Factor* factor = no->u.op1.factor; showNodeFactor(factor, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<unary>\n");
}
void showNodeUnaryOp(UnaryOp* no, int lvl){
  switch (no->tag)
  {
    default:{
      showNodeUnaryOp(no->tag, lvl + 1);
      break;
    }
  }
  nSpaces(lvl * 2); printf("<unary-op>\n");
}
void showNodeFactor(Factor* no, int lvl){
  switch (no->tag)
  {
    case 0: {
      Expr* expr = no->u.op0.expr; showNodeExpr(expr, lvl + 1);
      break;      
    }
    case 1: {
      Aux* aux = no->u.op1.aux; showNodeAux(aux, lvl + 1);
      break;      
    }
    case 2: {
      Call* call = no->u.op2.call; showNodeCall(call, lvl + 1);
      break;      
    }
    case 3: {
      Ascii* ascii = no->u.op3.ascii; showNodeAscii(ascii, lvl + 1);
      break;      
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<factor>\n");
}
void showNodeAux(Aux* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; showNodeId(id, lvl + 1);
      Expr* expr0 = no->u.op0.expr0; showNodeExpr(expr0, lvl + 1);
      Expr* expr1 = no->u.op0.expr1; showNodeExpr(expr1, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; showNodeId(id, lvl + 1);
      Expr* expr = no->u.op1.expr; showNodeExpr(expr, lvl + 1);
      break;
    }
    case 2:{
      NumId* numId = no->u.op2.numId; showNodeNumId(numId, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<aux>\n");
}
void showNodeNumId(NumId* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Num* num = no->u.op0.num; showNodeNum(num, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; showNodeId(id, lvl + 1);
      break;
    }
    default:{
      break;
    }

  }
  nSpaces(lvl * 2); printf("<num-id>\n");
}
void showNodeCall(Call* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; showNodeId(id, lvl + 1);
      ArgList* argList = no->u.op0.argList; showNodeArgList(argList, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; showNodeId(id, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<call>\n");
}
void showNodeArgList(ArgList* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      ArgList* argList = no->u.op0.argList; showNodeArgList(argList, lvl + 1);
      Arg* arg = no->u.op0.arg; showNodeArg(arg, lvl + 1);
      break;
    }
    case 1:{
      Arg* arg = no->u.op1.arg; showNodeArg(arg, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<arg-list>\n");
}
void showNodeArg(Arg* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      MatArg* matArg = no->u.op0.matArg; showNodeMatArg(matArg, lvl + 1);
      break;
    }
    case 1:{
      Aux* aux = no->u.op1.aux; showNodeAux(aux, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<arg>\n");
}
void showNodeMatArg(MatArg* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; showNodeId(id, lvl + 1);
      int int0 = no->u.op0.int0; showInt(int0);
      int int1 = no->u.op0.int1; showInt(int1);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<mat-arg>\n");
}
void showNodeAscii(Ascii* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      char cval = no->u.op0.cval; showChar(cval);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<ascii>\n");
}
void showNodeBaseType(BaseType* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      showBaseType(no->u.op0.ival);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<base-type>\n");
}
void showNodeNum(Num* no, int lvl){
  switch (no->tag)
  {
    case 0:{
      showFloat(no->u.op0.fval);
      break;
    }
    case 1:{
      showInt(no->u.op0.fval);
      break;
    }
    default:{
      break;
    }
  }
  nSpaces(lvl * 2); printf("<num>\n");
}

// Daqui para baixo, coisas que sao terminais como ID
void showId(Id* no){
  printf("%s", no);
  printf("\n");
}

void showError(char* e) {
  printf("Error: %s", e);
}
// Depende semi-COMPLETAMENTE da gramatica...

void showMulOp(int op){
  switch (op)
  {
  case MAT_MUL:  printf("< mat-mul, @@ >");    break;
  case MUL:      printf("< mul, * >"); break;
  case DIV:      printf("< div, / >"); break;
  default: break;
  }
  printf("\n");
}
void showAddOp(int op){
  switch (op)
  {
  case ADD:  printf("< addop, + >");    break;
  case SUB:  printf("< addop, - >"); break;
  default: break;
  }
  printf("\n");
}


void showRelOp(int op){
  switch (op)
  {
  case LE:  printf("< relop, <= >");    break;
  case GE:  printf("< relop, >= >");    break;
  case NEQ: printf("< relop, != >");    break;
  case EQ:  printf("< relop, == >");    break;
  case GT:  printf("< relop, > >");    break;
  case LT:  printf("< relop, < >");    break;
  default:  printf("< relop, UNKNOWN >");    break;
  }
  printf("\n");
}

void showInt(int num){
  printf("< int, %d >\n", num);
}

void showFloat(float num){
  printf("< float, %f >\n", num);
}

void showChar(char c){
  printf("< char, %c >\n", c);
}

void showBaseType(char c){
  switch (c)
  {
  case 'i':  printf("< base-type, int >"); break;
  case 'f':  printf("< base-type, float >"); break;
  case 'c':  printf("< base-type, char>"); break;
  default:   printf("< base-type, UNKNOWN>"); break;
  }
  printf("\n");
}

void showBinLogi(int op) {
  switch (op)
  {
  case AND: printf("< bin-logi, && >");   break;
  case OR:  printf("< bin-logi, || >");   break;
  default:  break;
  }
}

void showNodeId(Id* id, int lvl) {
  nSpaces(lvl);
  printf("<id, %s>\n", id);
}

// main(){}