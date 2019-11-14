import re

f = open('gramaticas/new_grammar.tab.h').read()
gambs = re.sub(r'([A-Z_]+|yytokentype)',r'_\1', re.findall(r'enum yytokentype(?:.|\n)+?};', f)[0])

f2 = open('SemanticChecker.c').read()
f3 = re.sub('(// REPLACE FROM HERE\n)(.|\n)+(// UNTIL HERE)', '// REPLACE FROM HERE\n' + gambs + '\n// UNTIL HERE\n', f2)

with open('SemanticChecker.c', 'w', encoding='utf-8') as ff:
  ff.write(f3)