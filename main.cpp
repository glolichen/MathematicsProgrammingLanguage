#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"

int main() {
	std::ifstream fin("samplecode.mpl");
	
	std::stringstream ss;
	ss << fin.rdbuf();
	std::string text = ss.str();

	std::vector<lexer::Token> tokens;
	lexer::lex(text, tokens);

	for (lexer::Token token : tokens) {
		std::cout << token.token << " ";
		std::cout << lexer::type_to_string(token.type) << " ";
		std::cout << token.sentence << "\n";
	}

	return 0;
}
