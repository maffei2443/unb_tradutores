+ 'tt' : mensagem de erro zuada quando tem mais de um caractere
entre aspas.

+ para simplificar o trabalho, para mostrar nova linha deve-se
    fazer PRINT('')

+ em operações entre matriz/escalar, o ESCALAR SOFRE UPPER/DOWN cast conforme o tipo da matriz

+ lista de parametros e de argumentos sao encadeadas pelo ponteiro *next_aux*

+ comparações booleanas apenas entre escalares [nao implementado]

+ em caso de redeclaracao de variavel/funcao, mantem-se na symTable a antiga
(além de dar erro)

+ temporário **$1023** reservado para operações de casting (buffer)

+ 