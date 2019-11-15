import re
import string
import os
from rules import GetRules, GetHeads, GetTokens
mapa = {}
rules = GetRules()
heads = GetHeads()
tokens = GetTokens()
storage = 'C_code'
try:
  os.mkdir(storage)
except Exception:
  pass
def hifen2Type(text):
  aux = text.split('-')
  return ''.join(map(str.capitalize, aux))

def token2Type(text):
  aux = text.split('_')
  return "t"+''.join(map(str.capitalize, aux))

def hifen2VarName(text, firstLower=True , prefix = '', suffix = ''):
  aux = hifen2Type(text)
  if firstLower:
    return prefix + '_'+aux[0].lower() + aux[1:] + suffix
  else:
    return prefix + '_'+aux + suffix


def toUnion(listOfBodies, baseIdent=2, spaces=-1):
  """
  Cria contendo uma struct para cada possivel corpo de regra.
  """
  _basic = baseIdent * ' '
  _spaces = spaces * ' ' if spaces > 0 else 2 * baseIdent * ' '
  return (
    _basic 
    + 'union {\n' 
    + _spaces 
    + f'\n{_spaces}'.join(listOfBodies) 
    + '\n'
    + f'{_basic}'
    + '}u;'
  )

def createMakeSignature(tipo, text, alias='STR'):
  """
  text is expected to have the pattern:
  struct { ... } op<NUM>;
  This function returns a stardardized  C-like function sig
  nature. Example:
    + tipo = "Num"
    + text = "STR {STR BaseType* _baseType; V_id* _v_id; Lp* _lp;} op0;"
    make_Nodes(tipo, text) -> "Num* make_Num_op0(STR BaseType* _baseType, V_id* _v_id,
          Lp* _lp);"
  OBS: utilizacao apohs processamento de generateMap
  """
  text = text.replace('\n', '')
  attrs, opNum = re.findall(f'{alias}' +r' *{(.*)} *(op\d+)', text)[0]
  funName = hifen2Type(tipo) + f"* make_{hifen2Type(tipo)}_{opNum}("
  funName = funName + ','.join(attrs.strip(';').strip().split(';')).strip(',') + ');'
  return re.sub( r' +', ' ', funName)



def createMakeCall(tipo, text, alias='STR'):
  """
  Gerador automatizado para chamada das funções geradas pela
  função acima, seguindo a ORDEM dos parâmetros (bison; not-labeled).
  Exemplo:
    + tipo = ''
    + text = ''  
  """
  text = text.replace('\n', '')
  attrs, opNum = re.findall(f'{alias}'+ r' *{(.*)} (op\d+)', text)[0]
  funName = f"make_{hifen2Type(tipo)}_{opNum}("
  for s in range(1, len(attrs.split(';'))):
    funName = funName + f"${s}, "
  funName = funName[:-2] + ');'
  return funName

def GenerateMakeCall(file = storage+'calls.h', mapa=mapa):
  lis = []
  with open(file, 'w') as fp:  
    for ret, lisParam in mapa.items():
      for l in lisParam:
        fp.write( createMakeCall(ret, l) + '\n' )
        lis.append(createMakeCall(ret, l))
  return lis



def tokens2Structs(file = storage+'TokenStruct.h', tokens = tokens):
  """
  Cria structs, uma para cada token. Todas são dummies.
  Requer manualmente alterar quais não o são.

  """
  lis = []
  with open(file, 'w') as fp: 
    fp.write("typedef struct {} Dummy" + ';\n')
    for t in tokens: 
      aux = '_' + t.capitalize()
      lis.append(aux)
      if not '_V_' in aux:
        fp.write("typedef Dummy " + aux + ";\n") 
      else:
        fp.write("typedef struct {/*PREENCHE MANUALMENTE*/} " + aux + ';\n')
  return lis
                                                                                    

def generateMap(structAlias = 'STR', tokens = tokens):
  """
  structAlias aparece pois aparecer "struct" toda hora é um saco
  """
  splited = [ r.split(' : ') for r in rules ]
  mapa = {}
  for x in splited:
    x0 = x[0]
    mapa[x0] = mapa.get(x0, [])

    tail = x[1]
    for t in tokens:
      tail = tail.replace(t, '')
    
    tail = x[1].split()
    sign = ' '.join(
      map( lambda p : (f"{structAlias} " if p not in tokens else '_') 
        + f"{hifen2Type(p)}* {'_' if p in tokens else ''}{hifen2VarName(p)};\n    ", tail )
    )

    mapa[x0].append( f'{structAlias} '+ '{' + sign + '} op' + str((len(mapa[x0]))) + ';' )
  return mapa
# mapa = generateMap()
# lmap = list(mapa.items())
# print(lmap[13][1])
# Salva as structs necessarias, AH MENOS das que se referem aos
# tokens.
def GenerateNodes(file = storage+"Nodes.h", mapa = mapa):
  with open(file, 'w') as fp: 
    fp.write('#include "TokenStruct.h"' + '\n')
    fp.write('typedef struct {} Dummy;' + '\n')
    fp.write('#define STR struct' + '\n')
    for k, item in mapa.items(): 
      fp.write( 'typedef struct {\n'+toUnion(item) +'\n' + '} ' + f'{hifen2Type(k)};'
    + '\n' )

def separateTypeParam(text):
  """
    Retorna lista com os nomes dos parametros da funcao.
    Esta é suposta estar na forma:
      Fun(Type1* arg1, Type2* arg2, Type3* arg3).
    Retorno:
      [ 
        ('Type1*', 'Type2*', 'Type3*'),
        ('arg1', 'arg2', 'arg3')
      ]
    Feito para depois ser executada a CORREÇÃO para caso
    de conflito de nomes.
  """
  tuplas = re.findall(r'((?:STR )?[\w_]+\*) +(_[^,]+?);', text)
  return list(zip(*tuplas))

def solveSameParamName(text):
  types_names = list(map(list, separateTypeParam(text)))
  ll = types_names[1]
  for name in set(types_names[1]):
    if ll.count(name) > 1: 
      ct = 0 
      for ix in range(len(types_names[1])): 
        if types_names[1][ix] == name: 
          ll[ix] += str(ct) 
          ct += 1
  ll = types_names
  new_types_names = ''
  for i in range(len(ll[0])):
    new_types_names = new_types_names + ll[0][i] + ' ' +ll[1][i] + '; '
  return new_types_names