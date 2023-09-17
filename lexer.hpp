#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

namespace lexer {
	struct Token {
		int type, sentence;
		std::string token;
	};

	std::string type_to_string(int type);
	void lex(std::string text, std::vector<Token> &output);
}

#endif