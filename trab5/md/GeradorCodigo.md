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
  - [x]criar label e retorno ao final independente de ter retorno a função

- numListList
  - [] fazer cast para o tipo base ao qual serah atribuido
- numList
  - [] fazer cast para o tipo base ao qual serah atribuido
- block
  - [x] rotulo removido

- declList
  - [x] varios 'declOrInitVar' (soh concatenar os codigos)
- expr
  - fazer conversoes
    + escalar x escalar: quase pronto
    + matriz x matriz: nem sei por onde começar
    + matriz x escalar: é operação elemento a elemento SSE for add/sub (debito), então gera matrix auxiliar 
- call
  - [x] empilhar parametros na ordem natural (obrigado, interpretador TAC)
  - [x] PROBLEMA: passar parametros de TAMANHO DE MATRIZ.

- argList
  - PROBLEMA: passar argumento de tamanho da matriz
    - SOLUÇÃO: empilhar o valor da expressão logo após empilhar o endereço da matriz

- arg
  - [~] em caso de matriz, empilhar a dimensão q representa tamanho da linha

- num
  - [x] inserir diretamente o valor constante

- lvalue
  - [] ao se detectar lvalue em expressão, alterar *currBasyType* pra saber
    qual *cast* fazer nos casos de :
      - [] atribuição com rvalue = expr
      - [] atribuição com rvalue = numList ou numListList
      - 
- rvalue
  - [] por si só, não gera código pois acessar sem atribuir a coisa alguma
    não sera código (mini "otimização")