```sh
make
```

### Para apenas gerar o código:
  ./all < caminho_do_arquivo
### Para mostrar além do código de três endereços a árvore abstrata
  ./all 0 < caminho_do_arquivo
### Para mostrar além do código de três endereços a tabela de símbolos
  ./all 0 1 < caminho_do_arquivo
### Para mostrar além do código de três endereços a árvore abstrata E tabela de símbolos
  ./all 0 1 2 < caminho_do_arquivo

# Na pasta "prelude", encontram-se diversos procedimentos em códigos de três endereços implementados e testados. Os mesmos, juntamente com outros não desenvolvidos a tempo, seriam inseridos SEMPRE no início de cada programa gerado.