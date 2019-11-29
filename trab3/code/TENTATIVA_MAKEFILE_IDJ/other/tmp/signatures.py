"""
  Este módulos gera um arquivo chamado "signature_call.c",
  contendo chamadas às funções definidas em "signature.c".
"""

import re

with open('signatures_call.h', 'w') as newFp:
  with open('signatures.h', 'r') as fp:
    for signature in fp:
      funName = re.findall(r'[^ ] ([^(]+)', signature)[0]
      params = re.findall(r'[^(]+\(([^)]+)', signature)[0]
      paramList = params.split(',')
      call = f'{funName}('
      for num in range(len(paramList)):
        call += f"${num}, "
      call = call[:-2] + ');'
      newFp.write(call + '\n')
