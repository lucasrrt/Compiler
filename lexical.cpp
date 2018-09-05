#include<iostream>

#define MAX_CONSTS 100
#define MAX_ID_LEN 100
#define MAX_STR_LEN 100
#define MAX_NUM_LEN 100

using namespace std;

typedef enum {
	//reserved words
	ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCTION, IF, INTEGER, OF, STRING, STRUCT, TRUE, TYPE, VAR, WHILE, 

	//simbolos
	COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL, NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, TIMES, DIVIDE, DOT, NOT,

	//regular tokens
	CHARACTER, NUMERAL, STRINGVAL, ID,

	//unknown token
	UNKNOWN
} t_token;

t_token searchKeyWord(char *name);
//TODO return the enum
//use a vector of reserved words, and use binary search
//token is the position of the word

//Se uma palavra não for reservada, o analisador deve determinar
//o token secundário (nome).
//Tabela de identificadores com os token ID e o token secundário 
//com o nome daquele identificador, que pode ser um número inteiro
//que indica a ordem em que ele foi lido no arquivo de entrada.
//Cada identificador pode aparecer somente uma vez nessa tabela
//Hash é a melhor implementação dessa tabela

int searchName( char *name );
//TODO Inserir ou buscar identificadores na tabela de nomes.

//literais são CHARACTER, NUMERAL e STRINGVAL
//também devem ser armazenados para fácil acesso posterior no programa.
typedef  struct {
	char type; //0-char, 1-int, 2-string
	union {
		char   cVal;
		int    nVal;
		char * sVal;
	}   _;
}   t_const;

//constantes - posição indicará token secundário
t_const vConsts[MAX_CONSTS];
int nNumConsts = 0; //número total de constantes

//TODO Inclusão de constantes de cada tipo e retornar
//a posição onde foram inseridas (nNumConsts)
int addCharConst (char c);
int addIntConst (char *n); //The number it is actually a string of digits
int addStringConst (char *c);

//TODO Recuperação do valor de uma constante
int getCharConst (int n);
int getIntConst (int n);
int getStringConst (int n);

//TODO Lê os caracteres do arquivo de entrada
char readChar(void);

//armazenar o caractere lido em uma variável
char nextChar = '\x20'; // para garantir o funcionamento na 1ª chamada da nextToken()

t_token nextToken(void);
t_token token;
int tokenSecundario;

t_token nextToken(void) {
	//loop do estado inicial para pular os separadores
	while(isspace(nextChar)) {
		nextChar = readChar();
	}
	if( isalpha(nextChar) ) {
		char text[MAX_ID_LEN+1];
		int i = 0;
		do {
			text[i++] = nextChar;
			nextChar = readChar();
		} while( isalnum(nextChar || nextChar == '_') );
	text[i] = '\0';

		token = searchKeyWord( text );
		if( token == ID ) {
			tokenSecundario = searchName( text );
		}
	} else if (isdigit(nextChar)){
		char numeral[MAX_NUM_LEN+1];
		int i = 0;
		do {
			numeral[i++] = nextChar;
			nextChar = readChar();
		} while( isdigit(nextChar) );
		numeral[i] = '\0';

		token = NUMERAL;
		tokenSecundario = addIntConst( numeral );
	} else if( nextChar == '"' ) {
		char string[MAX_STR_LEN+1];
		int i = 1;
		do{
			string[i++] = nextChar;
			nextChar = readChar();
		} while( nextChar != '"' );
		string[i++] = '"';
		string[i] = '\0';

		token = STRING;
		tokenSecundario = addStringConst(string);
	} else 
		//TODO check where i have to call the nextChar = readChar();
		switch(nextChar) {
			case '\'':
				nextChar = readChar();
				token = CHARACTER;
				tokenSecundario = addCharConst(nextChar);
				nextChar = readChar(); //pular o fechamento de '
				nextChar = readChar();
				break;

			case ':':
				nextChar = readChar();
				token = COLON;
				break;

			case '+':
				nextChar = readChar();
				if(nextChar == '+') {
					token = PLUS_PLUS;
					nextChar = readChar();
				} else {
					token = PLUS;
				}
				break;

			//TODO ALL the other cases

			default:
				token = UNKNOWN;
		}

	return token;
}

int main() {
	cout << "wahey" << endl;
}
