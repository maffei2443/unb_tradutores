### Instruções

Foi utilizado Ubuntu 18.04,  bison 3.0.4 e flec 2.6.4

Para compilar:


```
	make
```

Para executar:

```
	./all < <caminho-para-arquivo>

```

Caso não seja passado arquivo algum, será lido da entrada padrão. Porém, nesse caso não será gerada a árvore sintática visto que não será nunca detectado o caractere de final de arquivo.