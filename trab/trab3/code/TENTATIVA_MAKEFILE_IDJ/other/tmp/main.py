from rules import rules, heads, tokens
import re
def hifen2Type(text):
  aux = text.split('-')
  return ''.join(map(str.capitalize, aux))

def token2Type(text):
  aux = text.split('_')
  return "t"+''.join(map(str.capitalize, aux))

def hifen2VarName(text, firstLower=True , prefix = '', suffix = ''):
  aux = hifen2Type(text)
  if firstLower:
    return prefix + aux[0].lower() + aux[1:] + suffix
  else:
    return prefix + aux + suffix


def toUnion(listOfBodies, baseIdent=2, spaces=-1):
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

def make_Nodes(tipo, text):
  """
  text is expected to have the pattern:
  struct { ... } op<NUM>;
  This function returns a stardardized  C-like function sig
  nature. Example:
    + tipo = "Num"
    + text = "struct {Float* float;} op0;"
    make_Nodes(tipo, text) -> "Num* make_Num_op0(Float* float);"
  """
  attrs, opNum = re.findall(r'struct *{(.*)} (op\d+)', text)[0]
  funName = tipo + f"* make_{tipo}_{opNum}("
  funName = funName + ','.join(attrs.strip(';').strip().split(';')) + ');'
  return funName
def make_Nodes_call(tipo, text):
  """
  Gerador automatizado para chamada das funções geradas pela
  função acima, seguindo a ORDEM dos parâmetros (bison; not-labeled)
  """
  attrs, opNum = re.findall(r'struct *{(.*)} (op\d+)', text)[0]
  funName = f"make_{tipo}_{opNum}("
  for s in range(1, len(attrs.split(','))+1):
    funName = funName + f"${s}, "
  funName = funName[:-2] + ')'
  return funName


def tokens2Structs(tokens = tokens):
  """
  Cria structs, uma para cada token. Todas são dummies.
  Requer manualmente alterar quais não o são.

  """
  with open('TokenStructs.h', 'w') as fp: 
    for t in tokens: 
      fp.write("typedef struct{} " + t.capitalize() + ";\n") 
                                                                                    

def generateMap():
  splited = [ r.split(' : ') for r in rules ]
  mapa = {}
  for x in splited:
    x0 = x[0]
    mapa[x0] = mapa.get(x0, [])

    tail = x[1]
    for t in tokens:
      tail = tail.replace(t, '')
    
    tail = x[1].split()
    tail = ' '.join(
      map( lambda p : "{}* {};".format( hifen2Type(p), hifen2VarName(p)), tail )
    )
    mapa[x0].append( 'struct {' + tail + '} op' + str((len(mapa[x0]))) + ';' )  
  return mapa
mapa = generateMap()

# Salva as structs necessarias, AH MENOS das que se referem aos
# tokens.
with open('types.h', 'w') as fp: 
  for k, item in mapa.items(): 
    fp.write( 'typedef struct {\n'+toUnion(mapa[k]) +'\n' + '} ' + f'{hifen2Type(k)};'
  + '\n' )