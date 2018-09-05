#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

#define MAX_CONSTS 100
#define MAX_ID_LEN 100
#define MAX_STR_LEN 100
#define MAX_NUM_LEN 100

#define wahey "wahey"

using namespace std;

typedef enum {
	//reserved words (0 ~ 17)
	ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCTION, IF, INTEGER, OF, STRING, STRUCT, TRUE, TYPE, VAR, WHILE, 

	//simbolos (18 ~ 43)
	COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL, NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, TIMES, DIVIDE, DOT, NOT,

	//regular tokens (44 ~ 47)
	CHARACTER, NUMERAL, STRINGVAL, ID,

	//unknown token (48)
	UNKNOWN
} t_token;

//TODO use a vector of reserved words instead of map, and use binary search
map<string, t_token> reserved_words;

t_token searchKeyWord(char *name) {
	return reserved_words[name];
}

//Se uma palavra não for reservada, o analisador deve determinar
//o token secundário (nome).
//Tabela de identificadores com o token ID e o token secundário 
//com o nome daquele identificador, que pode ser um número inteiro
//que indica a ordem em que ele foi lido no arquivo de entrada.
//Cada identificador pode aparecer somente uma vez nessa tabela
//Hash é a melhor implementação dessa tabela

vector<string> identifiers;

int searchName( char *name ) {
	vector<string>::iterator it = find(identifiers.begin(), identifiers.end(), name);
	if( it == identifiers.end() ) {
		cout << "Element not found" << endl;
		identifiers.push_back(name);
		return identifiers.size() - 1;
	} else {
		return it - identifiers.begin();
	}
}

//literais são CHARACTER, NUMERAL e STRINGVAL
//também devem ser armazenados para fácil acesso posterior no programa.
typedef  struct {
	char type; //0-char, 1-int, 2-string
	union {
		char   cVal;
		int    nVal;
		char * sVal;
	}   val;
}   t_const;

//constantes - posição indicará token secundário
t_const vConsts[MAX_CONSTS];
int nNumConsts = 0; //número total de constantes

int addCharConst (char c) {
	t_const new_const;
	new_const.type = '0';
	new_const.val.cVal = c;

	vConsts[nNumConsts] = new_const;
	nNumConsts++;

	return nNumConsts - 1;
}
int addIntConst (char *n) { //The number it is actually a string of digits
	t_const new_const;
	new_const.type = '1';
	stringstream value(n);
	value >> new_const.val.nVal;

	vConsts[nNumConsts] = new_const;
	nNumConsts++;

	return nNumConsts - 1;
} 
int addStringConst (char *c) {
	t_const new_const;
	new_const.type = '2';
	new_const.val.sVal = c;

	vConsts[nNumConsts] = new_const;
	nNumConsts++;

	return nNumConsts - 1;
}

char getCharConst (int n) {
	return vConsts[n].val.cVal;
}
int getIntConst (int n) {
	return vConsts[n].val.nVal;
}
char *getStringConst (int n) {
	return vConsts[n].val.sVal;
}

ifstream file;
char readChar(void) {
	char c;
	file.get(c);
	return c;
}

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
		} while( isalnum(nextChar) || nextChar == '_' );
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

			case ';':
				nextChar = readChar();
				token = SEMI_COLON;
				break;

			case ',':
				nextChar = readChar();
				token = COMMA;
				break;

			case '=':
				nextChar = readChar();
				if(nextChar == '=') {
					token = EQUAL_EQUAL;
					nextChar = readChar();
				} else {
					token = EQUALS;
				}
				break;

			case '[':
				nextChar = readChar();
				token = LEFT_SQUARE;
				break;

			case ']':
				nextChar = readChar();
				token = RIGHT_SQUARE;
				break;

			case '{':
				nextChar = readChar();
				token = LEFT_BRACES;
				break;

			case '}':
				nextChar = readChar();
				token = RIGHT_BRACES;
				break;

			case '(':
				nextChar = readChar();
				token = LEFT_PARENTHESIS;
				break;

			case ')':
				nextChar = readChar();
				token = RIGHT_PARENTHESIS;
				break;

			case '&':
				nextChar = readChar();
				if(nextChar == '&') {
					token = AND;
					nextChar = readChar();
				}
				break;

			case '|':
				nextChar = readChar();
				if(nextChar == '|') {
					token = OR;
					nextChar = readChar();
				}
				break;

			case '<':
				nextChar = readChar();
				if(nextChar == '=') {
					token = LESS_OR_EQUAL;
					nextChar = readChar();
				} else {
					token = LESS_THAN;
				}
				break;

			case '>':
				nextChar = readChar();
				if(nextChar == '=') {
					token = GREATER_OR_EQUAL;
					nextChar = readChar();
				} else {
					token = GREATER_THAN;
				}
				break;

			case '!':
				nextChar = readChar();
				if(nextChar == '=') {
					token = NOT_EQUAL;
					nextChar = readChar();
				} else {
					token = NOT;
				}
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

			case '-':
				nextChar = readChar();
				if(nextChar == '-') {
					token = MINUS_MINUS;
					nextChar = readChar();
				} else {
					token = MINUS;
				}
				break;

			case '*':
				nextChar = readChar();
				token = TIMES;
				break;

			case '/':
				nextChar = readChar();
				token = DIVIDE;
				break;

			case '.':
				nextChar = readChar();
				token = DOT;
				break;

			//TODO ALL the other cases

			default:
				cout << "Unknown token" << endl;
				token = UNKNOWN;
		}

	cout << token << endl;
	return token;
}
