#include "ShowTree.h"

#include <stdio.h>
#include <stdlib.h>

void t_nSpaces(int qtd){
  char*  p = malloc(sizeof(char) * qtd+1);
  memset(p, ' ', qtd);
  p[qtd] = '\0';  
  printf(p);
  free(p);  p = NULL;
}

void t_showNodeProgram(Program* no, int lvl){
  //printf("\tt_showNodeProgram\n"); fflush(stdout);
  t_nSpaces(lvl * 2); printf("<Program>\n");
  // return;
  switch (no->tag)
  {
    case 0:{
      GlobalStmtList* s0 = no->u.op0.globalStmtList;
      t_showNodeGlobalStmtList(s0, lvl + 1);
      break;
    }
    default:{
      break;
    };
  }

}
void t_showNodeGlobalStmtList(GlobalStmtList* no, int lvl){
  //printf("\tt_showNodeGlobalStmtList\n"); fflush(stdout);
  t_nSpaces(lvl * 2); printf("<GlobalStmtList>\n");
  // return;
  switch (no->tag)
  {
    case 0:{
      GlobalStmtList* s0 = no->u.op0.globalStmtList; t_showNodeGlobalStmtList(s0, lvl + 1);
      GlobalStmt* s1 = no->u.op0.globalStmt; t_showNodeGlobalStmt(s1, lvl + 1);
      break;
    }
    default:{
      GlobalStmt* s1 = no->u.op0.globalStmt; t_showNodeGlobalStmt(s1, lvl + 1);
      break;
    }
  }
  // t_nSpaces(lvl * 2); printf("<GlobalStmtList>\n"); return;
}
void t_showNodeGlobalStmt(GlobalStmt* no, int lvl){
  t_nSpaces(lvl * 2); printf("<global-stmt>\n");
  return;
  // printf("tag: %d\n", no->tag); fflush(stdout);
  //printf("\tt_showNodeGlobalStmt\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      DeclFun* s0 = no->u.op0.declFun;  t_showNodeDeclFun(s0, lvl + 1);
      break;
    }
    case 1:{      
      DefFun* s1 = no->u.op1.defFun;  t_showNodeDefFun(s1, lvl + 1);
      t_nSpaces((lvl+1) * 2); t_showError(no->u.op1.error);
      break;
    }
    case 2:{
      DefFun* s2 = no->u.op2.defFun;  t_showNodeDefFun(s2, lvl + 1);      
      break;
    }
    case 3:{
      DeclVar* s3 = no->u.op3.declVar;  t_showNodeDeclVar(s3, lvl + 1);      
      break;
    }
    case 4:{
      DeclVar* s4 = no->u.op4.declVar;  t_showNodeDeclVar(s4, lvl + 1);
      t_nSpaces((lvl+1) * 2); t_showError(no->u.op4.error);    
      break;
    }
    case 5:{
      AttrVar* s5 = no->u.op5.attrVar;  t_showNodeAttrVar(s5, lvl + 1);
      break;
    }
    case 6:{
      Block* s6 = no->u.op6.block;  t_showNodeBlock(s6, lvl + 1);
      break;
    }
    default:
      break;
  }
  t_nSpaces(lvl * 2); printf("<global-stmt>\n"); return;
}
void t_showNodeMatType(MatType* no, int lvl){
  //printf("\tt_showNodeMatType\n"); fflush(stdout);
  switch (no->tag)
  {
    default:
      break;
  }
  t_nSpaces(lvl * 2); printf("<mat-type>\n");
}
void t_showNodeDefFun(DefFun* no, int lvl){
  //printf("\tt_showNodeDefFun\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      BaseType * baseType = no->u.op0.baseType; t_showNodeBaseType(baseType, lvl + 1);
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1) * 2 );
      ParamListVoid * paramListVoid = no->u.op0.paramListVoid; t_showNodeParamListVoid(paramListVoid, lvl + 1);
      Block* block = no->u.op0.block; t_showNodeBlock(block, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<def-fun>\n");
}
void t_showNodeDeclFun(DeclFun* no, int lvl){
  //printf("\tt_showNodeDeclFun\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      BaseType* s0 = no->u.op0.baseType; t_showNodeBaseType(s0, lvl + 1);
      Id* s1 = no->u.op0.id; t_showId(s1);
      ParamListVoid* s2 = no->u.op0.paramListVoid; t_showNodeParamListVoid(s2, lvl + 1);  
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<decl-fun>\n");
}
void t_showNodeDeclVar(DeclVar* no, int lvl){
  //printf("\tt_showNodeDeclVar\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{      
      MatType* mat_type = no->u.op0.mat_type; t_showNodeMatType(mat_type, lvl + 1);
      BaseType* baseType = no->u.op0.baseType; t_nSpaces((lvl+1)*2); t_showBaseType(baseType->u.op0.ival);
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1)*2);
      Num* num0 = no->u.op0.num0; t_showNodeNum(num0, lvl + 1);
      Num* num1 = no->u.op0.num1; t_showNodeNum(num1, lvl + 1);
      break;
    }
    case 1:{      
      BaseType* baseType = no->u.op1.baseType; t_nSpaces((lvl+1)*2); t_showBaseType(baseType->u.op0.ival);
      IdArr* idArr = no->u.op1.idArr; t_showNodeIdArr(idArr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<decl-var>\n");
}
void t_showNodeIdArr(IdArr* no, int lvl){
  //printf("\tt_showNodeIdArr\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1)*2);
      NumId* numId = no->u.op0.numId; t_showNodeNumId(numId, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; t_showNodeId(id, (lvl + 1)*2);
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<id-arr>\n");
}
void t_showNodeAttrVar(AttrVar* no, int lvl){
  //printf("\tt_showNodeAttrVar\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      MatAttr* matAttr = no->u.op0.matAttr; t_showNodeMatAttr(matAttr, lvl + 1);
      break;
    }
    case 1:{      
      IndexAttr* indexAttr = no->u.op1.indexAttr; t_showNodeIndexAttr(indexAttr, lvl + 1);
      break;
    }
    case 2:{      
      SimpleAttr* simpleAttr = no->u.op2.simpleAttr; t_showNodeSimpleAttr(simpleAttr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<attr-var>\n");
}
void t_showNodeSimpleAttr(SimpleAttr* no, int lvl){
  //printf("\tt_showNodeSimpleAttr\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; t_showId(id);
      Expr* expr = no->u.op0.expr; t_showNodeExpr(expr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<simple-attr>\n");
}
void t_showNodeIndexAttr(IndexAttr* no, int lvl){
  //printf("\tt_showNodeIndexAttr\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; t_showId(id);
      NumId* numId = no->u.op0.numId; t_showNodeNumId(numId, lvl + 1);
      Expr* expr = no->u.op0.expr; t_showNodeExpr(expr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<index-attr>\n");
}
void t_showNodeMatAttr(MatAttr* no, int lvl){
  //printf("\tt_showNodeMatAttr\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1)*2);
      NumListList* numListList = no->u.op0.numListList; t_showNodeNumListList(numListList, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; t_showNodeId(id, (lvl + 1)*2);
      NumId* numId = no->u.op1.numId; t_showNodeNumId(numId, lvl + 1);
      NumList* numList = no->u.op1.numList; t_showNodeNumList(numList, lvl + 1);
      break;
    }
    case 2:{
      Id* id = no->u.op2.id; t_showNodeId(id, (lvl + 1)*2);
      NumId* numId0 = no->u.op2.numId0; t_showNodeNumId(numId0, lvl + 1);
      NumId* numId1 = no->u.op2.numId1; t_showNodeNumId(numId1, lvl + 1);
      Expr* expr = no->u.op2.expr; t_showNodeExpr(expr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<mat-attr>\n");
}
void t_showNodeNumListList(NumListList* no, int lvl){
  //printf("\tt_showNodeNumListList\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      NumListList* numListList = no->u.op0.numListList; t_showNodeNumListList(numListList, lvl + 1);
      NumList* numList = no->u.op0.numList; t_showNodeNumList(numList, lvl + 1);
      break;
    }
    case 1:{
      NumList* numList = no->u.op1.numList; t_showNodeNumList(numList, lvl + 1);
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<num-list-list>\n");
}
void t_showNodeNumList(NumList* no, int lvl){
  //printf("\tt_showNodeNumList\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      NumList* numList = no->u.op0.numList; t_showNodeNumList(numList, lvl + 1);
      Num* num = no->u.op0.num; t_showNodeNum(num, lvl + 1);
      break;
    }
    case 1:{
      Num* num = no->u.op1.num; t_showNodeNum(num, lvl + 1);
      break;
    }
    case 2:{
      Id* id = no->u.op2.id; t_showNodeId(id, (lvl + 1)*2);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<num-list>\n");
}
void t_showNodeStmt(Stmt* no, int lvl){
  //printf("\tt_showNodeStmt\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Expr* expr = no->u.op0.expr; t_showNodeExpr(expr, lvl + 1);
      break;
    }
    case 1:{
      Id* id0 = no->u.op1.id0; t_showNodeId(id0, (lvl + 1) * 2);
      Id* id1 = no->u.op1.id1; t_showNodeId(id1, (lvl + 1) * 2);
      break;
    }
    case 2:{
      Id* id = no->u.op2.id; t_showNodeId(id, (lvl + 1)*2);
      NumId* numId0 = no->u.op2.numId0; t_showNodeNumId(numId0, lvl + 1);
      NumId* numId1 = no->u.op2.numId1; t_showNodeNumId(numId1, lvl + 1);
      break;
    }
    case 3:{
      Id* id = no->u.op3.id; t_showNodeId(id, (lvl + 1)*2);
      NumId* numId = no->u.op3.numId; t_showNodeNumId(numId, lvl + 1);
      break;
    }
    case 4:{
      Id* id = no->u.op4.id; t_showNodeId(id, (lvl + 1)*2);
      break;
    }
    case 5:{
      Expr* expr = no->u.op5.expr; t_showNodeExpr(expr, lvl + 1);
      break;
    }
    case 6:{
      Call* call = no->u.op6.call; t_showNodeCall(call, lvl + 1);
      break;
    }
    case 7:{
      DeclVar* declVar = no->u.op7.declVar; t_showNodeDeclVar(declVar, lvl + 1);
      break;
    }
    case 8:{
      AttrVar* attrVar = no->u.op8.attrVar; t_showNodeAttrVar(attrVar, lvl + 1);
      break;
    }
    case 9:{
      FlowControl* flowControl = no->u.op9.flowControl; t_showNodeFlowControl(flowControl, lvl + 1);
    }
    case 10:{
      Loop* loop = no->u.op10.loop; t_showNodeLoop(loop, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<stmt>\n");
}

void t_showNodeParamListVoid(ParamListVoid* no, int lvl){
  //printf("\tt_showNodeParamListVoid\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{  // dummy case
      t_nSpaces((lvl + 1)*2); printf("<void>\n");
      break;      
    }
    case 1:{ 
      ParamList* paramList = no->u.op1.paramList; t_showNodeParamList(paramList, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<param-list-void>\n");
}

void t_showNodeParamList(ParamList* no, int lvl){
  //printf("\tt_showNodeParamList\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      ParamList* paramList = no->u.op0.paramList; t_showNodeParamList(paramList, lvl + 1);
      Param* param = no->u.op0.param; t_showNodeParam(param, lvl + 1);
      break;
    }
    case 1:{
      Param* param = no->u.op1.param; t_showNodeParam(param, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<param-list>\n");
}
void t_showNodeParam(Param* no, int lvl){
  //printf("\tt_showNodeParam\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      BaseType* baseType = no->u.op0.baseType; t_showNodeBaseType(baseType, lvl + 1);
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1)*2);
      break;
    }
    case 1:{
      MatType* mat_type = no->u.op1.mat_type; t_showNodeMatType(mat_type, lvl + 1);
      BaseType* baseType = no->u.op1.baseType; t_showNodeBaseType(baseType, lvl + 1);
      Id* id = no->u.op1.id; t_showNodeId(id, (lvl + 1)*2);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<param>\n");
}
void t_showNodeLoop(Loop* no, int lvl){
  //printf("\tt_showNodeLoop\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{      
      Expr* expr = no->u.op0.expr; t_showNodeExpr(expr, lvl + 1);
      Block* block = no->u.op0.block; t_showNodeBlock(block, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<loop>\n");
}
void t_showNodeFlowControl(FlowControl* no, int lvl){
  //printf("\tt_showNodeFlowControl\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Expr* expr = no->u.op0.expr; t_showNodeExpr(expr, lvl + 1);
      Block* block = no->u.op0.block; t_showNodeBlock(block, lvl + 1);
      FlowControl* flowControl = no->u.op0.flowControl; t_showNodeFlowControl(flowControl, lvl + 1);
      break;
    }
    case 1:{
      Expr* expr = no->u.op1.expr; t_showNodeExpr(expr, lvl + 1);
      Block* block0 = no->u.op1.block0; t_showNodeBlock(block0, lvl + 1);
      Block* block1 = no->u.op1.block1; t_showNodeBlock(block1, lvl + 1);
      break;
    }
    case 2:{
      Error* error = no->u.op2.error; t_nSpaces((lvl + 1) * 2); t_showError(error);
      Block* block0 = no->u.op2.block0; t_showNodeBlock(block0, lvl + 1);
      Block* block1 = no->u.op2.block1; t_showNodeBlock(block1, lvl + 1);
      break;
    }
    case 3:{
      Expr* expr = no->u.op3.expr; t_showNodeExpr(expr, lvl + 1);
      Error* error = no->u.op3.error; t_nSpaces((lvl + 1) * 2); t_showError(error);
      Block* block0 = no->u.op3.block0; t_showNodeBlock(block0, lvl + 1);
      Block* block1 = no->u.op3.block1; t_showNodeBlock(block1, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<flow-control>\n");
}
void t_showNodeBlock(Block* no, int lvl){
  //printf("\tt_showNodeBlock\n"); 
  t_nSpaces(lvl * 2); printf("<block>\n"); fflush(stdout);
  return;
  switch (no->tag)
  {
    case 0:{
      StmtList* stmtList = no->u.op0.stmtList; t_showNodeStmtList(stmtList, lvl + 1); break;
    }
    case 1:{
      // Bloco vazio {}
      break;
    }
    default:{
      break;
    }
  }
}
void t_showNodeStmtList(StmtList* no, int lvl){
  // //printf("\tt_showNodeStmtList\n"); fflush(stdout);
  t_nSpaces(lvl * 2); printf("<stmt-list>\n"); return;
  switch (no->tag)
  {
    case 0:{
      StmtList* stmtList = no->u.op0.stmtList; t_showNodeStmtList(stmtList, lvl + 1);
      Stmt* stmt = no->u.op0.stmt; t_showNodeStmt(stmt, lvl + 1);
      break;
    }
    case 1:{
      Stmt* stmt = no->u.op1.stmt; t_showNodeStmt(stmt, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
}
void t_showNodeExpr(Expr* no, int lvl){
  //printf("\tt_showNodeExpr\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      AddExpr* addExpr0 = no->u.op0.addExpr0; t_showNodeAddExpr(addExpr0, lvl + 1);
      Relop* relop = no->u.op0.relop; t_showNodeRelop(relop, lvl + 1);
      AddExpr* addExpr1 = no->u.op0.addExpr1; t_showNodeAddExpr(addExpr1, lvl + 1);
      break;
    }
    case 1:{
      AddExpr* addExpr = no->u.op1.addExpr; t_showNodeAddExpr(addExpr, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<expr>\n");
}
void t_showNodeRelop(Relop* no, int lvl){
  //printf("\tt_showNodeRelop\n"); fflush(stdout);
  switch (no->tag)
  {
    default:{
      t_nSpaces( ( lvl + 1 ) * 2); t_showRelOp(no->tag);
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<relop>\n");
}
void t_showNodeAddExpr(AddExpr* no, int lvl){
  //printf("\tt_showNodeAddExpr\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{ 
      AddExpr* addExpr = no->u.op0.addExpr; t_showNodeAddExpr(addExpr, lvl + 1);
      Addop* addop = no->u.op0.addop; t_showNodeAddop(addop, lvl + 1);
      Term* term = no->u.op0.term; t_showNodeTerm(term, lvl + 1);
      break;
    }
    case 1:{ 
      Term* term = no->u.op1.term; t_showNodeTerm(term, lvl + 1);
      break;
    }
    default:{ // dummy
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<add-expr>\n");
}
void t_showNodeAddop(Addop* no, int lvl){
  //printf("\tt_showNodeAddop\n"); fflush(stdout);
  switch (no->tag)
  {
    default:{
      t_nSpaces((lvl + 1) * 2); t_showAddOp(no->tag);
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<addop>\n");
}
void t_showNodeTerm(Term* no, int lvl){
  //printf("\tt_showNodeTerm\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Mulop* mulop = no->u.op0.mulop; t_showNodeMulop(mulop, lvl + 1);
      Bin* bin = no->u.op0.bin; t_showNodeBin(bin, lvl + 1);
      break;
    }
    case 1:{
      Bin* bin = no->u.op1.bin; t_showNodeBin(bin, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<term>\n");
}
void t_showNodeMulop(Mulop* no, int lvl){
  //printf("\tt_showNodeMulop\n"); fflush(stdout);
  switch (no->tag)
  {
    default:{ // dummy
      t_nSpaces((lvl + 1) * 2); t_showMulOp(no->tag);
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<mulop>\n");
}
void t_showNodeBin(Bin* no, int lvl){
  //printf("\tt_showNodeBin\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      BinLogi* binLogi = no->u.op0.binLogi; t_showNodeBinLogi(binLogi, lvl + 1);
      Unary* unary = no->u.op0.unary; t_showNodeUnary(unary, lvl + 1);
      break;
    }
    case 1:{
      Unary* unary = no->u.op1.unary; t_showNodeUnary(unary, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<bin>\n");
}
void t_showNodeBinLogi(BinLogi* no, int lvl){
  //printf("\tt_showNodeBinLogi\n"); fflush(stdout);
  switch (no->tag)
  {
    default:{
      t_showBinLogi(no->tag);
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<bin-logi>\n");
}
void t_showNodeUnary(Unary* no, int lvl){
  //printf("\tt_showNodeUnary\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      UnaryOp* unaryOp = no->u.op0.unaryOp; t_showNodeUnaryOp(unaryOp, lvl + 1);
      Factor* factor = no->u.op0.factor; t_showNodeFactor(factor, lvl + 1);
      break;
    }
    case 1:{
      Factor* factor = no->u.op1.factor; t_showNodeFactor(factor, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<unary>\n");
}
void t_showNodeUnaryOp(UnaryOp* no, int lvl){
  //printf("\tt_showNodeUnaryOp\n"); fflush(stdout);
  switch (no->tag)
  {
    default:{
      t_nSpaces( (lvl+1) * 2 ); t_showUnaryOp(no->tag);
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<unary-op>\n");
}
void t_showNodeFactor(Factor* no, int lvl){
  //printf("\tt_showNodeFactor\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0: {
      Expr* expr = no->u.op0.expr; t_showNodeExpr(expr, lvl + 1);
      break;      
    }
    case 1: {
      Aux* aux = no->u.op1.aux; t_showNodeAux(aux, lvl + 1);
      break;      
    }
    case 2: {
      Call* call = no->u.op2.call; t_showNodeCall(call, lvl + 1);
      break;      
    }
    case 3: {
      Ascii* ascii = no->u.op3.ascii; t_showNodeAscii(ascii, lvl + 1);
      break;      
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<factor>\n");
}
void t_showNodeAux(Aux* no, int lvl){
  //printf("\tt_showNodeAux\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1)*2);
      Expr* expr0 = no->u.op0.expr0; t_showNodeExpr(expr0, lvl + 1);
      Expr* expr1 = no->u.op0.expr1; t_showNodeExpr(expr1, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; t_showNodeId(id, (lvl + 1)*2);
      Expr* expr = no->u.op1.expr; t_showNodeExpr(expr, lvl + 1);
      break;
    }
    case 2:{
      NumId* numId = no->u.op2.numId; t_showNodeNumId(numId, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<aux>\n");
}
void t_showNodeNumId(NumId* no, int lvl){
  //printf("\tt_showNodeNumId\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Num* num = no->u.op0.num; t_showNodeNum(num, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; t_showNodeId(id, (lvl + 1)*2);
      break;
    }
    default:{
      break;
    }

  }
  t_nSpaces(lvl * 2); printf("<num-id>\n");
}
void t_showNodeCall(Call* no, int lvl){
  //printf("\tt_showNodeCall\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1)*2);
      ArgList* argList = no->u.op0.argList; t_showNodeArgList(argList, lvl + 1);
      break;
    }
    case 1:{
      Id* id = no->u.op1.id; t_showNodeId(id, (lvl + 1)*2);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<call>\n");
}
void t_showNodeArgList(ArgList* no, int lvl){
  //printf("\tt_showNodeArgList\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      ArgList* argList = no->u.op0.argList; t_showNodeArgList(argList, lvl + 1);
      Arg* arg = no->u.op0.arg; t_showNodeArg(arg, lvl + 1);
      break;
    }
    case 1:{
      Arg* arg = no->u.op1.arg; t_showNodeArg(arg, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<arg-list>\n");
}
void t_showNodeArg(Arg* no, int lvl){
  //printf("\tt_showNodeArg\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      MatArg* matArg = no->u.op0.matArg; t_showNodeMatArg(matArg, lvl + 1);
      break;
    }
    case 1:{
      Aux* aux = no->u.op1.aux; t_showNodeAux(aux, lvl + 1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<arg>\n");
}
void t_showNodeMatArg(MatArg* no, int lvl){
  //printf("\tt_showNodeMatArg\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      Id* id = no->u.op0.id; t_showNodeId(id, (lvl + 1)*2);
      int int0 = no->u.op0.int0;t_showInt(int0);
      int int1 = no->u.op0.int1;t_showInt(int1);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<mat-arg>\n");
}
void t_showNodeAscii(Ascii* no, int lvl){
  //printf("\tt_showNodeAscii\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      char cval = no->u.op0.cval; t_showChar(cval);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<ascii>\n");
}
void t_showNodeBaseType(BaseType* no, int lvl){
  //printf("\tt_showNodeBaseType\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      t_showBaseType(no->u.op0.ival);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<base-type>\n");
}
void t_showNodeNum(Num* no, int lvl){
  //printf("\tt_showNodeNum\n"); fflush(stdout);
  switch (no->tag)
  {
    case 0:{
      t_showFloat (no->u.op0.fval);
      break;
    }
    case 1:{
     t_showInt(no->u.op0.fval);
      break;
    }
    default:{
      break;
    }
  }
  t_nSpaces(lvl * 2); printf("<num>\n");
}

// Daqui para baixo, coisas que sao terminais como ID
void t_showId(Id* no){
  //printf("\tt_showId\n"); fflush(stdout);
  printf("%s", no);
  printf("\n");
}

void t_showError(char* e) {
  //printf("\tt_showError\n"); fflush(stdout);
  printf("Error: %s", e);
}
// Depende semi-COMPLETAMENTE da gramatica...

void t_showMulOp(int op){
  switch (op)
  {
  case tMAT_MUL:  printf("< mat-mul, @@ >");    break;
  case tMUL:      printf("< mul, * >"); break;
  case tDIV:      printf("< div, / >"); break;
  default: break;
  }
  printf("\n");
}
void t_showAddOp(int op){
  switch (op)
  {
  case tADD:  printf("< addop, + >");    break;
  case tSUB:  printf("< addop, - >"); break;
  default: break;
  }
  printf("\n");
}


void t_showRelOp(int op){
  switch (op)
  {
  case tLE:  printf("< relop, <= >");    break;
  case tGE:  printf("< relop, >= >");    break;
  case tNEQ: printf("< relop, != >");    break;
  case tEQ:  printf("< relop, == >");    break;
  case tGT:  printf("< relop, > >");    break;
  case tLT:  printf("< relop, < >");    break;
  default:  printf("< relop, UNKNOWN >");    break;
  }
  printf("\n");
}

void t_showInt(int num){
  printf("< int, %d >\n", num);
}

void t_showFloat(float num){
  printf("< float, %f >\n", num);
}

void t_showChar(char c){
  printf("< char, %c >\n", c);
}

void t_showBaseType(char c){
  switch (c)
  {
  case 'i':  printf("< base-type, int >"); break;
  case 'f':  printf("< base-type, float >"); break;
  case 'c':  printf("< base-type, char>"); break;
  default:   printf("< base-type, UNKNOWN>"); break;
  }
  printf("\n");
}

void t_showBinLogi(int op) {
  switch (op)
  {
  case tAND: printf("< bin-logi, && >");   break;
  case tOR:  printf("< bin-logi, || >");   break;
  default:  break;
  }
}
void t_showUnaryOp(int op) {
  switch (op)
  {
  case tNOT: printf("< bin-logi, && >");   break;
  case tADDR:  printf("< bin-logi, || >");   break;
  default:  break;
  }
}

void t_showNodeId(Id* id, int lvl) {
  t_nSpaces(lvl);
  printf("<id, %s>\n", id);
}

// main(){}