letter_		[_a-zA-Z]
digit		[0-9]
id			{letter_}({letter_}|{digit})*
int			{digit}+
float		{digit}*"."?{digit}*|{int}+e{int}
num			{float}|int

%%

{id} printf("%s\n", yytext);
.+ printf("NAO EH ID: %s\n", yytext);
%%

main() {
	printf("Digite ses roles\n");
	yylex();
}