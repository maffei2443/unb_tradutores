+ Declaração *com* inicialização

+ remoção de palavra **void** quando a função não tinha parâmetros ou argumentos

+ remoção do tipo char: char só pode aparecer dentro do *statement* **PRINT**

+ pode ter ponto e virgula sobrando nos *statements*

+ precedência dos operadores é feita por meio das diretivas %left e %right, não mais por meio de *n+1* para casa *n* níveis

+ remoção de regras que serviam como multiplexadoras para tipos de operadores

+ novas regras:

  +  **typeAndNameSign**

  + **regra para parâmetro** != regra para declarar

  + passagem de matriz para função

  + **notação para dizer que parametro é vetor**

  + **declaração de variáveis e inicialização ANTES dos demais statements de uma função** (para simplificar a implementação)

<!--  -->
# GERAÇÃO DE CÓDIGO

- passagem de dimensão de matriz requer agora apenas 1 parâmetro
  (bem como em *C*, para vetores de 2 dimensões)

- alteração da regra **flowControl** e **localStmt**, de modo a 
permitir ações semânticas no meio da regra de produção do _if_
  - foi adicionada uma nova regra de produção: **newFlowControl**,
  para saber onde colocar o label que finaliza uma cadeia de _if/else

- remove declaração com inicialização.
  - motivo: naõ deu tempo de fazer direito