# Esse script deve gerar o código boilerplate do tipo:;
# regra = make<nº Regra>_regra(token1, token2, ...)
import re


def GetTokens(fileName = 'grammar.y'):
  """
  Retorna lista atualizada dos Tokens, baseado no
  arquivo de nome recebido
  """
  lis = []
  for line in open(fileName, 'r'):
    if line.startswith('%token'):
      lis.extend(re.findall(r'%token ([^\n]+)', line)[0].split())
  global tokens
  tokens = lis.copy()
  return lis

def GetRules(fileName = 'grammar.y'):
  """
  Gera lista das regras de produção da gramática,
  baseado no arquivo de nome recebido.
  """
  lis = [] 
  for l in open(fileName): 
    if re.findall(' : ', l) and '//' not in l:  
      head = re.findall(r'(.+ : )', l)[0] 
      lis.append(re.findall(r'([^{\n]+)', l)[0].strip()) 
    elif l.startswith('|'): 
      lis.append(head + re.findall(r'([^{\n]+)', l)[0][2:].strip())
  global rules
  rules = lis.copy() 
  return lis

def GetHeads(filename = 'grammar.y'):
  tok = GetRules(filename)
  global heads
  heads = [i.split(' : ')[0] for i in tok]
  return heads

def GetPtrTypes(st): 
  """
    Retorna lista com os tipos dos ponteiros.
    Ex:
    st = 'str {str V_float* _v_float;} op0;'
    GetPtrTypes(st) -> ['V_float']
  """
  return re.findall( r'([\w_]+?)(?=\*)' , st)       

