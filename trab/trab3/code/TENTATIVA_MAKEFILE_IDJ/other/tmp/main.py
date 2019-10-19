from rules import rules, heads, tokens

def hifen2Type(text):
  aux = text.split('-')
  return ''.join(map(str.capitalize, aux))

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

def make_Nodes(mapa):

  pass
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

with open('unions.c', 'w') as fp:
  for k, item in mapa.items():
    fp.write( 'typedef struct {\n'+toUnion(mapa[k]) +'\n' + '} ' + f'{hifen2Type(k)};' + '\n' )


