.table
.code
// Espera 2 parametros:
// - endereco simbolico
// - qtd de enderecos alocados
// Retorna referencia para NOVA area de memoria
// em que os conteudos sao os da antiga mas convertidos
// de inteiro para float.
// REQUER FREE PELO CHAMADOR
mat_i2f_temp:
	mov $1, #1		// tamanho da matriz
	mema $2, $1		// aloca matriz de mesmo tamanho
	mov $3, $1		// iterador
	sub $3, $3, 1	// se tem tamanho n, comece pela posicao n-1
	// setar todas as posicoes de memoria para inteiro
start2:			
	mov $4, #0[$3]	// copia n-esimo termo para entao converter
	inttofl $4, $4	
	// mov #0[$3], $5   // modifica matriz passada como parametro
	mov $2[$3], $4    // soh salva a conversao na nova matriz alocada dinamicamente
	brz mat_i2f_temp_end, $3 
	sub $3, $3, 1				
	jump start2
mat_i2f_temp_end:
  return $2
// END_FUN


// Espera 2 parametros:
// - endereco simbolico
// - qtd de enderecos alocados
// Retorna referencia para antiga area de memoria alocada
// a qual contem os valores convertidos para inteiro

mat_i2f:
	mov $1, #1		// tamanho da matriz
	mov $3, $1		// iterador
	sub $3, $3, 1	// se tem tamanho n, comece pela posicao n-1
	// setar todas as posicoes de memoria para inteiro
start3:			
	
  mov $4, #0[$3]	// copia n-esimo termo para entao converter
	inttofl $4, $4	
	mov #0[$3], $4   // modifica matriz passada como parametro

	brz mat_i2f_temp_end, $3 
	sub $3, $3, 1				
	jump start3

mat_i2f_end:
  return #0
// END_FUN
