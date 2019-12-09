/* QUEBRADO */

.table
.code
// Espera 2 parametros:
// - endereco simbolico
// - qtd de enderecos alocados
// Retorna referencia para NOVA area de memoria
// em que os conteudos sao os da antiga mas convertidos
// de float para inteiro.
// REQUER FREE PELO CHAMADOR
mat_f2i_temp:
	mov $1, #1		// tamanho da matriz
	mema $2, $1		// aloca matriz de mesmo tamanho
	mov $3, $1		// iterador
	sub $3, $3, 1	// se tem tamanho n, comece pela posicao n-1
	// setar todas as posicoes de memoria para inteiro
start0:			
	mov $4, #0[$3]	// copia n-esimo termo para entao converter
	fltoint $4, $4	
	// mov #0[$3], $5   // modifica matriz passada como parametro
	mov $2[$3], $4    // soh salva a conversao na nova matriz alocada dinamicamente
	brz mat_f2i_temp_end, $3 
	sub $3, $3, 1				
	jump start0
mat_f2i_temp_end:
  return $2
// END_FUN


// Espera 2 parametros:
// - endereco simbolico
// - qtd de enderecos alocados
// Retorna referencia para ANTIGA area de memoria alocada
// a qual contem os valores convertidos para inteiro

mat_f2i:
	mov $1, #1		// tamanho da matriz
	mov $3, $1		// iterador
	sub $3, $3, 1	// se tem tamanho n, comece pela posicao n-1
	// setar todas as posicoes de memoria para inteiro
start1:			
	
  mov $4, #0[$3]	// copia n-esimo termo para entao converter
	fltoint $4, $4	
	mov #0[$3], $4   // modifica matriz passada como parametro

	brz mat_f2i_temp_end, $3 
	sub $3, $3, 1				
	jump start1

mat_f2i_end:
  return #0
// END_FUN


main:
	mema $0, 2
	mov $0[0], 1.11
	mov $0[1], 5.4
	param $0
	param 2

	call mat_f2i_temp, 2
  pop $2
  println 'R'

	mov $1, $2[0]
  println $1

	mov $1, $2[1]
  println $1

  print 'O'
  print 'L'
  println 'D'

	mov $1, $0[0]
  println $1

	mov $1, $0[1]
  println $1

  param $0
  param 2
  call mat_f2i, 2

  print 'O'
  print 'L'
  print 'D'
  println '2'

	mov $1, $0[0]
  println $1

	mov $1, $0[1]
  println $1


  memf $0
