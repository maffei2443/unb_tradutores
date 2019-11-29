<!-- SEMÂNTICO -->
- [x] adicionar dimensões da matriz à **tabela de símbolos**
- [x] adicionar dimensões do vetor à **tabela de símbolos**

- [x] diferenciar linha de matriz de COLUNA
  + Solução: campos _line_ e _col_ em _SymEntry_

- [x] testar redeclaração de PARAMETROS em TODOS os locais:
  + **typeAndNameSign** na parte de ARRAY e MATRIZ
- [] Checar tipo em TODAS as expressões

- [] Garantir que utilização do operador de indexação é feito apenas em *matriz* ou *array*
- [] operador **_!_ SÓ PODE SER APLICADO A ESCALARES**
- [] **checar tipo quando definir funcao jah pre-declarada !!!**

<!-- GERAÇÃO DE CODIGO -->
- [] **informar erro sobre impossibilidade de declaração de variáveis que não sejam no início de funções OU global**
- [] fazer o gerenciamento dos temporários enquanto variáveis locais
- [] Fazer os CASTs sempre que necessário
- [] Gerar label para *controles de fluxo*
- [] tudo mais xD

- [] Como lidar com variáveis locais?
  + Um temporário para cada variável local
  + Uma tabela HASH para fazer essa associação
    + A tabela hash pode ser a mesma usada hoje, pois suporta decla-
      rações de mesmo nome em escopos distintos
