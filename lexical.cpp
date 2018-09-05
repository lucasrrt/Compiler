#include <iostream>
#include "lexical.h"

using namespace std;

int main() {
	reserved_words["array"] = ARRAY;
	reserved_words["boolean"] = BOOLEAN;
	reserved_words["break"] = BREAK;
	reserved_words["char"] = CHAR;
	reserved_words["continue"] = CONTINUE;
	reserved_words["do"] = DO;
	reserved_words["else"] = ELSE;
	reserved_words["false"] = FALSE;
	reserved_words["function"] = FUNCTION;
	reserved_words["if"] = IF;
	reserved_words["integer"] = INTEGER;
	reserved_words["of"] = OF;
	reserved_words["string"] = STRING;
	reserved_words["struct"] = STRUCT;
	reserved_words["true"] = TRUE;
	reserved_words["type"] = TYPE;
	reserved_words["var"] = VAR;
	reserved_words["while"] = WHILE;


	//simbolos
	reserved_words["colon"] = COLON;
	reserved_words["semi_colon"] = SEMI_COLON;
	reserved_words["comma"] = COMMA;
	reserved_words["equals"] = EQUALS;
	reserved_words["left_square"] = LEFT_SQUARE;
	reserved_words["right_square"] = RIGHT_SQUARE;
	reserved_words["left_braces"] = LEFT_BRACES;
	reserved_words["right_braces"] = RIGHT_BRACES;
	reserved_words["left_parenthesis"] = LEFT_PARENTHESIS;
	reserved_words["right_parenthesis"] = RIGHT_PARENTHESIS;
	reserved_words["and"] = AND;
	reserved_words["or"] = OR;
	reserved_words["less_than"] = LESS_THAN;
	reserved_words["greater_than"] = GREATER_THAN;
	reserved_words["less_or_equal"] = LESS_OR_EQUAL;
	reserved_words["greater_or_equal"] = GREATER_OR_EQUAL;
	reserved_words["not_equal"] = NOT_EQUAL;
	reserved_words["equal_equal"] = EQUAL_EQUAL;
	reserved_words["plus"] = PLUS;
	reserved_words["plus_plus"] = PLUS_PLUS;
	reserved_words["minus"] = MINUS;
	reserved_words["minus_minus"] = MINUS_MINUS;
	reserved_words["times"] = TIMES;
	reserved_words["divide"] = DIVIDE;
	reserved_words["dot"] = DOT;
	reserved_words["not"] = NOT;

	//regular tokens
	reserved_words["character"] = CHARACTER;
	reserved_words["numeral"] = NUMERAL;
	reserved_words["stringval"] = STRINGVAL;
	reserved_words["id"] = ID;

	//unknown token
	reserved_words["unknown"] = UNKNOWN;

	file.open("example");
	
	while(nextToken() != 48);
}

