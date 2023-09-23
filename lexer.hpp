#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

namespace lexer {
	struct Token {
		int type, sentenceNum;
		std::string token;
	};

	enum TokenType {
		// comparison operators
		EQUAL, NOT_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,
		// logical operators
		NEGATE, AND, OR,
		// arithmetic operators
		ADD, SUBTRACT, MULTIPLY, DIVIDE, EXPONENT,
		// assignment
		LET, BE,
		// quotation marks
		SINGLE_QUOTE, DOUBLE_QUOTE, 
		// vectors
		UNDERSCORE, DIMENSIONS, FORGET, LBKT, RBKT,
		// goto and if
		REFER_TO, IF,
		// IO
		OUTPUT, 
		// data types
		INTEGER, FLOAT, CHARACTER, VECTOR,
		// functions
		BTFDF, ADB,
		// literals
		INT_LIT, FLOAT_LIT, STR_LIT, CHAR_LIT,
		// miscellaneous
		PERIOD, LPAR, RPAR, COMMENT, COMMA, ARROW, IDENTIFIER,
	};

	const std::string TOKEN_NAME[] = {
		"EQUAL", "NOT_EQUAL", "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL",
		"NEGATE", "AND", "OR",
		"ADD", "SUBTRACT",	"MULTIPLY", "DIVIDE", "EXPONENT",
		"LET", "BE",
		"SINGLE_QUOTE", "DOUBLE_QUOTE", 
		"UNDERSCORE", "DIMENSIONS", "FORGET", "LBKT", "RBKT",
		"REFER_TO", "IF",
		"OUTPUT", 
		"INTEGER", "FLOAT", "CHARACTER", "VECTOR",
		"BTFDF", "ADB",
		"INT_LIT", "FLOAT_LIT", "STR_LIT", "CHAR_LIT",
		"PERIOD", "LPAR", "RPAR", "COMMENT", "COMMA", "ARROW", "IDENTIFIER",
	};

	const std::unordered_map<std::string, int> KEYWORDS = {
		{ "Let", LET },
		{ "be", BE },
		{ "be the function defined for", BTFDF },
		{ "and defined by", ADB },
		{ "integer", INTEGER },
		{ "dimensions", DIMENSIONS },
		{ "float", FLOAT },
		{ "vector", VECTOR },
		{ "refer to sentence", REFER_TO },
		{ "if", IF },
		{ "output", OUTPUT },
	};

	struct MultiWordKeyword {
		std::string keyword;
		int tokenType;
		size_t wordCount;
		std::vector<std::string> split;
	};
	extern std::vector<MultiWordKeyword> multiWordKeywords;

	void init();
	std::string type_to_string(int type);
	void lex(std::string text, std::vector<Token> &output);
}

#endif