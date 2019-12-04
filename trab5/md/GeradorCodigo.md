- program
- globalStmtList
- globalStmt
- declFun
- typeAndNameSign
  - [x] alocacao dinamica em caso de array
- declOrdeclInitVar
  - typeAndNameSign 
  - [] checar os TIPOS e fazer CAST se necessario

- paramListVoid
- paramList
- param
- localStmtList
- localStmt
- flowControl
- loop
  - [x] **TODO: descobrir como tratar isso sem backpatching**
- defFun
  - criar label e retorno ao final independente de ter retorno a função

- numListList
  - [] fazer cast para o tipo base ao qual serah atribuido
- numList
  - [] fazer cast para o tipo base ao qual serah atribuido
- block
  - [] rotulo?

- declList
  - varios 'declOrInitVar' (soh concatenar os codigos)
- expr
  - fazer conversoes
    + escalar x escalar: quase pronto
    + matriz x matriz: nem sei por onde começar
    + matriz x escalar: é operação elemento a elemento, então gera matrix auxiliar 
- call
  - [] empilhar parametros na ordem natural (obrigado, interpretador TAC)
  - PROBLEMA: passar parametros de TAMANHO DE MATRIZ.
    - SOLUÇÃO: associar o intermediário **logo após o associado aa identificador** com o valor inteiro da expressão passada como argumento de tamanho da matriz

  
- argList
  - PROBLEMA: passar argumento de tamanho da matriz
    - SOLUÇÃO: empilhar o valor da expressão logo após empilhar o endereço da matriz

- arg
  - [] em caso de matriz, empilhar a dimensão q representa tamanho da linha

- num
  - [] inserir diretamente o valor constante

- lvalue
  - [] ao se detectar lvalue em expressão, alterar *currBasyType* pra saber
    qual *cast* fazer nos casos de :
      - [] atribuição com rvalue = expr
      - [] atribuição com rvalue = numList ou numListList
      - 
- rvalue
  - [] por si só, não gera código pois acessar sem atribuir a coisa alguma
    não sera código (mini "otimização")