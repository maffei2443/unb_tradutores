s = '{MatType* mat_type; BaseType* baseType; char* id;  Num* num0;  Num* num1; } op0;'

def GeraPrintsArvore(lis: "lista de strings"):
  l2 = []
  for s in lis:
    s = s.replace('struct {', '')
    ps, op = s.strip('{').strip('}').split('}') 
    for i in ps.split(';'): 
      ax = i.strip(' ').split(' ') 
      if len(ax) < 2: 
        continue 
      suf = op.strip(';').strip(' ').strip('op') 
      tipo = ax[1][0].upper() + ax[1][1:]
      l2.append(6*' '+ tipo + f'* {ax[1]} = no->u.op{suf}.{ax[1]}; showNode{tipo}({ax[1]});')
  return l2