#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <regex>

#define KEYWORD 0
#define IDENTIFIER 1

#define LPAR 2
#define RPAR 3
#define LBKT 4
#define RBKT 5

#define INT 6
#define FLOAT 7
#define CHAR 8

#define PERIOD 9
#define COMMA 10

#define PLUS 11
#define MINUS 12
#define MULTIPLY 13
#define DIVIDE 14

#define LITERAL 15

const std::string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";
const std::string KEYWORDS[] = {
	"Let",
	"let",
	"be",
	"For each",
	"in"	
};

const std::string TYPES[] = {
	"KEYWORD",
	"IDENTIFIER",
	"LPAR",
	"RPAR",
	"LBKT",
	"RBKT",
	"INT",
	"FLOAT",
	"CHAR",
	"PERIOD",
	"COMMA",
	"PLUS",
	"MINUS",
	"MULTIPLY",
	"DIVIDE",
	"LITERAL",
};

struct Token {
	int type, sentence;
	std::string token;
};

bool is_letter(char c) {
	for (char letter : LETTERS) {
		if (c == letter)
			return true;
	}
	return false;
}
bool is_number(char c) {
	for (char number : NUMBERS) {
		if (c == number)
			return true;
	}
	return false;
}

bool is_keyword(std::string token) {
	for (std::string keyword : KEYWORDS) {
		if (token == keyword)
			return true;
	}
	return false;
}

std::string scan(std::string file, int *index, std::function<bool(std::string, int)> valid) {
	std::string ret(1, file[(*index)++]);
	for (; (*index) < file.size(); (*index)++) {
		if (!valid(file, *index)) {
			(*index)--;
			return ret;
		}
		ret += file[*index];
	}
	(*index)--;
	return ret;
}

int main(int argc, char **argv) {
	std::ifstream fin("samplecode.mpl");
	
	std::stringstream ss;
	ss << fin.rdbuf();
	std::string file = ss.str();

	int curSentence = 0;
	bool isComment = false;
	std::vector<Token> tokens;
	for (int i = 0; i < file.size(); i++) {
		if (file.substr(i, 8) == "COMMENT:")
			isComment = true;

		char c = file[i];
		std::string token = "";

		if (c == '.' && (i == file.size() - 1 || file[i + 1] == ' ' || file[i + 1] == '\n')) {
			curSentence++;
			if (!isComment)
				tokens.push_back({ PERIOD, curSentence, "." });
			isComment = false;
		}
		else if (!isComment) {
			if (is_letter(c)) {
				std::string token = scan(file, &i, [](std::string string, int index) {
					return is_letter(string[index]) || is_number(string[index]);
				});
				if (is_keyword(token))
					tokens.push_back({ KEYWORD, curSentence, token });
				else
					tokens.push_back({ IDENTIFIER, curSentence, token });
			}
			else if (is_number(c)) {
				std::string token = scan(file, &i, [](std::string string, int index) {
					return is_number(string[index]) || (string[index] == '.' && index < string.size() && is_number(string[index + 1]));
				});
				bool isFloat = false;
				for (char ch : token) {
					if (ch == '.') {
						isFloat = true;
						break;
					}
				}
				if (isFloat)
					tokens.push_back({ FLOAT, curSentence, token });
				else
					tokens.push_back({ INT, curSentence, token });
			}
			else if (c == '"') {
				bool isClosed = false;
				std::string ret = "\"";
				i++;
				for (; i < file.size(); i++) {
					ret += file[i];
					if (file[i] == '"' && (i == 0 || file[i - 1] != '\\')) {
						isClosed = true;
						break;
					}
				}
				if (!isClosed)
					throw std::invalid_argument("unclosed string literal");
				tokens.push_back({ LITERAL, curSentence, ret });
			}
			else if (c == '\'') {
				if (file[i + 2] == '\'') {
					std::string ret(1, file[++i]);
					ret = "'" + ret + "'";
					tokens.push_back({ CHAR, curSentence, ret });
					i++;
				}
				else if (file[i + 1] == '\\' && file[i + 3] == '\'') {
					std::string ret = "'\\";
					// copied from https://stackoverflow.com/a/22185359
					switch (file[i + 2]) {
						case '\\': ret += "\\"; break;
						case '\"': ret += "\""; break;
						case '\'': ret += "'"; break;
						case '?': ret += "?"; break;
						case 'a': ret += "a"; break;
						case 'b': ret += "b"; break;
						case 'f': ret += "f"; break;
						case 'n': ret += "n"; break;
						case 'r': ret += "r"; break;
						case 't': ret += "t"; break;
						case 'v': ret += "v"; break;
						case '0': ret += "0"; break;
					}
					ret += "'";
					tokens.push_back({ CHAR, curSentence, ret });
					i += 3;
				}
				else
					throw std::invalid_argument("unclosed character");
			}
			else {
				std::string ret(1, c);
				if (c == ',')
					tokens.push_back({ COMMA, curSentence, ret });
				else if (c == '(')
					tokens.push_back({ LPAR, curSentence, ret });
				else if (c == ')')
					tokens.push_back({ RPAR, curSentence, ret });
				else if (c == '[')
					tokens.push_back({ LBKT, curSentence, ret });
				else if (c == ']')
					tokens.push_back({ RBKT, curSentence, ret });
				else if (c == '+')
					tokens.push_back({ PLUS, curSentence, ret });
				else if (c == '-')
					tokens.push_back({ MINUS, curSentence, ret });
				else if (c == '*')
					tokens.push_back({ MULTIPLY, curSentence, ret });
				else if (c == '/')
					tokens.push_back({ DIVIDE, curSentence, ret });
			}
		}
	}

	for (Token token : tokens) {
		std::cout << token.token << " " << TYPES[token.type] << "\n";
	}

	return 0;
}