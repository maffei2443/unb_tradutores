#include "SemanticChecker.h"
#include "new_grammar.tab.h"
#include "Common.h"
extern int temp;    // usado para enumerar os temporarios. Deve ser zerado e restaurado cada vez que entra em definicao de funcao
extern char* currScope;
extern char* GLOBAL_SCOPE;
extern int numlines;
extern int currCol;

int BLUE_tam = 0;
int BLUE_qtd = 0;

SymEntry** BLUE;
// Retorna 1 se a lista da match.
// -2 se ambos sao NULL
// -1 se noh eh NULL
// TODO: FIX IT
int match_paramList(No* oldParam, No* param) {
  // printf("sym: %p vs no: %p\n", sym, no);
  if(!oldParam && !param) return 1;   // ambas funcoes sem argumento
  if(!oldParam || !param) return 0;   // apenas 1 eh sem argumento
  printf("%s vs %s\n", type2string(oldParam->type), type2string(param->type));
  printf("%s vs %s\n", oldParam->sval, param->sval);
  while (oldParam && param){
    if(oldParam->type != param->type){
      printf("[match_paramList]%s vs %s\n", 
        type2string(oldParam->type), type2string(param->type)
      );
      break;
    }
    else {
      printf("pametro igual!\n");
      // Alterar os ponteiros por fora, aqui nao estah dando nada certo.
    }
    oldParam = oldParam->nextAux;
    param = param->nextAux;
  }
  printf("OK, FOI mach_paramList\n");
  printf("\t %p %p\n", oldParam, param);
  return !oldParam && !param;
}

void link_symentry_no(SymEntry** sym, No** no) {
  assert(*no && *sym);
  // printf("(BI directional) linking... ( %p )%s <--> %p\n", *sym,(*sym)->id, *no);
  (*no)->symEntry = *sym;
  (*sym)->astNode = *no;
  // fprintf(stderr, "\t[link_symentry_no]\t %p %p\n", *sym, *no);	  // fprintf(stderr, "\t[link_symentry_no]\t %p %p\n", *sym, *no);
}


// Utilizado em caso de utilização MAS nao de declaracao de variavel local
void point_no_symentry(SymEntry** sym, No** no) {
  assert(*no && *sym);
  // printf("(UNI directional) linking... %s <--> %p\n", (*sym)->id, *no);
  (*no)->symEntry = *sym;
  (*no)->type = (*sym)->type;
}

/* 
void set_type_and_uni_link(SymEntry** old, No** tok) {
    (*tok)->type = (*old)->type;
    point_no_symentry(old, tok);
}
*/


//  Retorna TYPE_UNDEFINED nos casos:
// - left/right ser TYPE_UNDEFINED
// - left/right ser TYPE_ARRAY
// - expressão mal formada (definida nas funcoes expr_*)
// Otherwise, infere tipo da expressao
// escalar por matriz
Type bin_expr_type(Type left, Type right, int op) {
  Type leftClass = Type_Class(left);
  Type rightClass = Type_Class(right);
  if(op <= 127){
    // DBG(printf("\n[bin_expr_type] tipos:  = %s <<%c>> %s\n", type2string(left),op, type2string(right)));
    // DBG(printf("[bin_expr_type] classes:  = %s <<%c>> %s\n", type2string(leftClass),op, type2string(rightClass)));
  } else {
    // DBG(printf("\n[bin_expr_type] tipos:  = %s <<%d>> %s\n", type2string(left),op, type2string(right)));
    // DBG(printf("[bin_expr_type] classes:  = %s <<%d>> %s\n", type2string(leftClass),op, type2string(rightClass)));
  }
  if(left == TYPE_CHAR || right == TYPE_CHAR){
    ERRSHOW(printf("ERRO: TIPO <CHAR> NAO PODE SER USADO PARA REALIZACAO DE OPERACOES\n"));
    return TYPE_UNDEFINED;
  }
  if(left == TYPE_UNDEFINED || right == TYPE_UNDEFINED) {
    ERRSHOW(printf("Erro cascata... \n"));
    return TYPE_UNDEFINED;
  }
  else if(leftClass == TYPE_ARRAY || rightClass == TYPE_ARRAY) {
    ERRSHOW(printf("ERRO: TIPO <ARRAY> NAO PODE SER USADO PARA REALIZACAO DE OPERACOES\n"));
    return TYPE_UNDEFINED;
  }
  else if(left == TYPE_MAT_CHAR || right == TYPE_MAT_CHAR) {
    ERRSHOW(printf("ERRO: TIPO <MAT_CHAR> NAO PODE SER USADO PARA REALIZACAO DE OPERACOES\n"));
    return TYPE_UNDEFINED;
  }
  // NAO SE PODE OPERAR SOBRE ARRAYS.
  // printf("**** %s %s\n\n", type2string(leftClass), type2string(rightClass));  
  switch (op)  {
    case '%': return expr_mod(left, right);
    case '+': return expr_add(left, right);
    case '-': return expr_sub(left, right);
    case '*': return expr_mul(left, right);
    case '/': return expr_div(left, right);
    case '@': return expr_mat_mul(left, right);
    case MAT_POW: return expr_mat_pow(left, right);
    case '=': return expr_attr(left, right);
    default:  return expr_bool(left, right, op);

  }
}

// Decisao: nada de tirar modulo de matriz
// Operacao modulo se aplica apenas a dois inteiros
Type expr_mod(Type le, Type ri){
  if(le == ri && le == TYPE_INT) return TYPE_INT;
  // else if (le == TYPE_MAT_INT && ri == TYPE_INT) return TYPE_MAT_INT;
  else {
    ERRSHOW(printf(" Erro: operandos invahlidos para operador %%: %s e %s. Ambos devem ser TYPE_INT ou TYPE_MAT_INT\n",
    type2string(le), type2string(ri)));
    return TYPE_UNDEFINED;
  }
}

Type expr_add(Type le, Type ri){
  Type le_class = Type_Class(le), ri_class = Type_Class(ri);
  if(le_class == ri_class) return max(le, ri);
  critical_error++;
  BoldRed();
  ERRSHOW(printf(" Soma/subtracao soh eh possivel entre mat/mat ou escalar/escalar\n"));
  printf("\t encontrado: %s [+-] %s\n", type2string(le), type2string(ri));
  Reset();
  return TYPE_UNDEFINED;
}

Type expr_sub(Type le, Type ri){
  return expr_add(le, ri);
}

Type expr_mul(Type le, Type ri){
  Type le_class = Type_Class(le), ri_class = Type_Class(ri);  
  if(le_class == ri_class) {
    if(le_class = TYPE_SCALAR) {
      return max(le, ri);
    }
  } else if (le_class == TYPE_SCALAR && ri_class == TYPE_MAT){
      if(le == TYPE_FLOAT) return TYPE_MAT_FLOAT;
      else return ri;
  }
  ERRSHOW(printf(" Erro: divisao %s / %s\n", type2string(le), type2string(ri)));
  return TYPE_UNDEFINED;  
}

Type expr_div(Type le, Type ri){
  Type le_class = Type_Class(le), ri_class = Type_Class(ri);  
  if(le_class == ri_class) {
    if(le_class = TYPE_SCALAR) {
      return max(le, ri);
    }
  } else if (le_class == TYPE_MAT && ri_class == TYPE_SCALAR){
      if(ri == TYPE_FLOAT) return TYPE_MAT_FLOAT;
      else return ri;
  }
  ERRSHOW(printf(" Erro: multiplicacao %s * %s\n",
      type2string(le), type2string(ri))
  );
  return TYPE_UNDEFINED;

}

Type expr_mat_mul(Type le, Type ri){
  Type le_class = Type_Class(le), ri_class = Type_Class(ri);
  if(le_class == TYPE_MAT && ri_class == TYPE_MAT) return max(le, ri);
  else {
    ERRSHOW(printf(" Erro: operandos invahlidos para operador @: %s e %s. Ambos devem ser do tipo matriz\n",
     type2string(le), type2string(ri)));
    return TYPE_UNDEFINED;
  }
}

Type expr_mat_pow(Type le, Type ri){
  if( Type_Class(le) == TYPE_MAT && ri == TYPE_INT)  return ri;
  else {
    ERRSHOW(printf(" Erro: operandos invahlidos para operador @@: %s e %s (esperado matriz e int)\n",
     type2string(le), type2string(ri)));
    return TYPE_UNDEFINED;
  }
}

Type expr_bool(Type le, Type ri, int op){
  Type c1 = Type_Class(le), c2 = Type_Class(ri);
  switch(op) {
    case GE:  case LE:
    case '<':  case '>':
    case AND:  case OR:
      if(c1 == c2) {
        if(c1 == TYPE_SCALAR) return TYPE_INT;
        else return TYPE_MAT_INT;
      }
      else {
        critical_error++;
        ERRSHOW(printf(" Erro: comparacao entre %s <?> %s\n", 
          type2string(le), type2string(ri)));
        return TYPE_UNDEFINED;
      }
    default:
    critical_error++;
      ERRSHOW(printf(" Expressao com tipos %s, %s e operacao %c sem tipo definido!\n",
        type2string(le), type2string(ri), op));
      return TYPE_UNDEFINED;
  }
}

Type expr_attr(Type le, Type ri) {
  Type le_class = Type_Class(le), ri_class = Type_Class(ri);
  if(le_class != ri_class) {
    ERRSHOW(printf(" Erro: operandos invahlidos para operador =: %s e %s (esperado operadores de mesma classe)\n",
     type2string(le), type2string(ri)));
    return TYPE_UNDEFINED;
  }
  return max(le, ri);
}

// Cast pode ser feito APENAS entre coisas de mesma class.
// Ex: scalar/saclar, array/array, umat/umat/, mat/mat
int can_cast(Type from, Type to) {
  return Type_Class(from) == Type_Class(to);
}

// Retorna true sse le == re == TYPE_INT
int can_cast_mod(Type le, Type ri) {
  Type le_class = Type_Class(le), ri_class = Type_Class(ri);
  if(le == ri && ri == TYPE_INT) return 1;
  return 0;
}

// Retorna NULL caso nao o tenha sido;senao,
// retorna ponteiro para declracao mais prohxima.
SymEntry* last_decl(SymEntry** reshi, char* id){
  // fprintf(stderr, "[last_decl] para %s", id);
  SymEntry* oldEntry = NULL;
  SymEntry* last_same_id = oldEntry;
  HASH_FIND_STR((*reshi), id, oldEntry);
  while( oldEntry ) {
    if(strcmp(oldEntry->escopo, currScope) == 0){  // declaracao sob mesmo escopo
      // fprintf(stderr," retornou (%p, %s)\n", oldEntry, oldEntry->id);
      return oldEntry;
    }
    else if(strcmp(oldEntry->escopo, GLOBAL_SCOPE) == 0){  // mesmo nome e escopo global
      last_same_id = oldEntry;
    }
    oldEntry = oldEntry->next;
  }
  // fprintf(stderr, " retornou [outWhile] (%p, %s)\n", last_same_id, last_same_id->id);
  return last_same_id;
}
// TODO: diferenciar da funcao de cima!
int was_declared(SymEntry** reshi, char* id){
  SymEntry* oldEntry = NULL;
  SymEntry* last_same_id = oldEntry;
  HASH_FIND_STR((*reshi), id, oldEntry);
  while( oldEntry ) {
    if(strcmp(oldEntry->escopo, currScope) == 0){  // declaracao sob mesmo escopo
      return !!oldEntry;
    }
    else if(strcmp(oldEntry->escopo, GLOBAL_SCOPE) == 0){  // mesmo nome e escopo global
      last_same_id = oldEntry;
    }
    oldEntry = oldEntry->next;
  }
  return !!last_same_id;
}

SymEntry* add_entry(SymEntry** reshi, char* id, int tag) {
    SymEntry* neoEntry = NULL;
    HASH_FIND_STR((*reshi), id, neoEntry);/* id already in the hash? */
    if (neoEntry == NULL) {
      neoEntry = SymEntry_New(id, tag, currScope);
      if( !strcmp(currScope, GLOBAL_SCOPE) ) {
        neoEntry->is_global = 1;
        printf("\t\t%s eh GLOBAL!\n", id);
      } else {
        neoEntry->is_global = 0;
        neoEntry->addr = temp_next();
        printf("%s:%s com $%d associado\n", neoEntry->id, currScope, neoEntry->addr);

      }
      // printf("\t\tNEO_ENTRY: %p\n", neoEntry);
      // printf("<<<<<< add (%p) id, tag: %s, %s\n", neoEntry, id, type2string(tag));
      neoEntry->local.line = numlines;
      neoEntry->local.col = currCol;
      HASH_ADD_STR( (*reshi), id, neoEntry );/* id: name of key field */
    }
    else {    // Checar se eh declaracao no msm escopo. Se for, nao adiciona e dah pau (retorna NULL);
      // printf("Possivel conflito com %s:%s\n", id, neoEntry->escopo);
      for(;neoEntry->next;neoEntry = neoEntry->next) {
        if(strcmp(id, neoEntry->id) == 0 && strcmp(currScope, neoEntry->escopo)) {
          ERRSHOW(printf("[Semantico1] Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
            currScope, id, neoEntry->local.line, neoEntry->local.col));
          return NULL;
        }
      }
      if( strcmp(id, neoEntry->id) == 0 && !strcmp(currScope, neoEntry->escopo) ) {          
        if(tag == TAG_DEF_FUN && neoEntry->tag == TAG_DECL_FUN) {
          printf("Caso especial de declaracao previa de %s\n", id);
        }
        else
          printf("[Semantico2] Erro: redeclaracao de %s:%s em l.%d, r.%d\n",
            currScope, id, neoEntry->local.line, neoEntry->local.col);
        return NULL;
      }
      else {
        neoEntry->next = SymEntry_New(id, tag, currScope);
        printf(">>>>> add (%p) id, tag: %s, %s\n", neoEntry->next, id, type2string(tag));
        neoEntry->next->local.line = numlines;
        neoEntry->next->local.col = currCol;
        return neoEntry->next;
      }
    }
    return neoEntry;
}

int id_has_type(SymEntry** reshi, char* id, Type type) {
  SymEntry* sym = last_decl(reshi, id);
  if(!sym) return -1;
  assert(sym->type == sym->astNode->type);
  return sym->type == type;
}

// Retorna 1 de t1 pode ser promovido a t2, e 0 caso contrario

Type to_base_type(Type t) {
  assert(t != TYPE_LIST && t != TYPE_LIST_LIST);
  switch(t) {
    case TYPE_SCALAR:
    case TYPE_MAT:
    case TYPE_ARRAY:
      printf("Impossivel enferir tipo base a partir de <%s>:/\n", type2string(t));
      return TYPE_UNDEFINED;
    case TYPE_MAT_CHAR:
    case TYPE_ARRAY_CHAR:
    case TYPE_CHAR:
      return TYPE_CHAR;
    case TYPE_MAT_INT:
    case TYPE_ARRAY_INT:
    case TYPE_INT:
      return TYPE_INT;
    case TYPE_ARRAY_FLOAT:
    case TYPE_MAT_FLOAT:
    case TYPE_FLOAT:
      return TYPE_FLOAT;
  }
}

// Problema: como lidar com indexacao dupla (matriz) ?
// Talvez seja melhor fazer isso direto no .y mesmo.
Type reduce_dim_type(Type t) {
  Type t_class = Type_Class(t);
  if(t_class != TYPE_MAT && t_class != TYPE_ARRAY) {
    printf("Nao pode reduzir dimensao de tipo <%s>\n", type2string(t) );
  }
  switch(t) {
    case TYPE_ARRAY_CHAR: return TYPE_CHAR;
    case TYPE_ARRAY_INT: return TYPE_INT;
    case TYPE_ARRAY_FLOAT: return TYPE_FLOAT;

    default:
      ERRSHOW(printf("TENTANDO REDUZIR DIMENSAO DE %s", type2string(t)));
    return TYPE_UNDEFINED;
  }
}

void delBLUE() {
  printf("QTD : %d\n", BLUE_qtd);
  for(int i = 0;i < BLUE_qtd;i++){
    printf("id, addr: %s, %p\n", (BLUE[i])->id, BLUE[i]);
    SymEntry_Destroy(BLUE[i]);
    BLUE[i] = NULL;
  }
  if(BLUE)
    free(BLUE);
  BLUE = NULL;
}

void delete_all(SymEntry* tab) {
  SymEntry *current_user, *tmp;

  HASH_ITER(hh, tab, current_user, tmp) {
    HASH_DEL(tab, current_user);  /* delete; users advances to next */
    printf("__calling__... %p\n", current_user);
    if (current_user)
      SymEntry_Destroy(current_user);            /* optional- if you want to free  */
  }
  // free(tab);
}
// msg_erros

void mensagem_redeclaracao(SymEntry* s) {
    ERRSHOW(printf(" Identificador %s jah foi definida em l.%d, c.%d como nao-funcao!\n",
      s->id, s->local.line, s->local.col));
}