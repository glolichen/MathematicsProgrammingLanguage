#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <regex>

#include "lexer.hpp"

#define KEYWD 0
#define IDENT 1

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
#define ARROW 16
const std::string TYPES[] = {
	"KEYWD",
	"IDENT",
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
	"ARROW",
};

const std::string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string NUMBERS = "0123456789";
const std::string KEYWORDS[] = {
	"Let",
	"let",
	"be",
	"For each",
	"in",
	"be the function defined for",
	"and defined by",
	"integer",
	"float",
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

std::string lexer::type_to_string(int type) {
	return TYPES[type];
}
void lexer::lex(std::string text, std::vector<lexer::Token> &output) {
	int curSentence = 0;
	bool isComment = false;
	for (int i = 0; i < text.size(); i++) {
		if (text.substr(i, 8) == "COMMENT:")
			isComment = true;

		char c = text[i];
		std::string token = "";

		if (c == '.' && (i == text.size() - 1 || text[i + 1] == ' ' || text[i + 1] == '\n')) {
			curSentence++;
			if (!isComment)
				output.push_back({ PERIOD, curSentence, "." });
			isComment = false;
		}
		else if (!isComment) {
			if (is_letter(c)) {
				std::string token = scan(text, &i, [](std::string string, int index) {
					return is_letter(string[index]) || is_number(string[index]);
				});
				if (is_keyword(token))
					output.push_back({ KEYWD, curSentence, token });
				else
					output.push_back({ IDENT, curSentence, token });
			}
			else if (is_number(c)) {
				std::string token = scan(text, &i, [](std::string string, int index) {
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
					output.push_back({ FLOAT, curSentence, token });
				else
					output.push_back({ INT, curSentence, token });
			}
			else if (c == '"') {
				bool isClosed = false;
				std::string ret = "\"";
				i++;
				for (; i < text.size(); i++) {
					ret += text[i];
					if (text[i] == '"' && (i == 0 || text[i - 1] != '\\')) {
						isClosed = true;
						break;
					}
				}
				if (!isClosed)
					throw std::invalid_argument("unclosed string literal");
				output.push_back({ LITERAL, curSentence, ret });
			}
			else if (c == '\'') {
				if (text[i + 2] == '\'') {
					std::string ret(1, text[++i]);
					ret = "'" + ret + "'";
					output.push_back({ CHAR, curSentence, ret });
					i++;
				}
				else if (text[i + 1] == '\\' && text[i + 3] == '\'') {
					std::string ret = "'\\";
					// copied from https://stackoverflow.com/a/22185359
					switch (text[i + 2]) {
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
					output.push_back({ CHAR, curSentence, ret });
					i += 3;
				}
				else
					throw std::invalid_argument("unclosed character");
			}
			else {
				std::string ret(1, c);
				if (c == ',')
					output.push_back({ COMMA, curSentence, ret });
				else if (c == '(')
					output.push_back({ LPAR, curSentence, ret });
				else if (c == ')')
					output.push_back({ RPAR, curSentence, ret });
				else if (c == '[')
					output.push_back({ LBKT, curSentence, ret });
				else if (c == ']')
					output.push_back({ RBKT, curSentence, ret });
				else if (c == '+')
					output.push_back({ PLUS, curSentence, ret });
				else if (c == '-') {
					if (i < text.size() - 1 && text[i + 1] == '>') {
						output.push_back({ ARROW, curSentence, ret + ">" });
					}
					else
						output.push_back({ MINUS, curSentence, ret });
				}
				else if (c == '*')
					output.push_back({ MULTIPLY, curSentence, ret });
				else if (c == '/')
					output.push_back({ DIVIDE, curSentence, ret });
			}
		}
	}

	for (int i = 0; i < output.size(); i++) {
		if (i < output.size() - 1 && output[i].token == "For" && output[i + 1].token == "each") {
			output[i] = { KEYWD, output[i].sentence, "For each" };
			output.erase(std::next(output.begin(), i + 1));
			i--;
		}
		if (i < output.size() - 4 && output[i].token == "be" && output[i + 1].token == "the"
			&& output[i + 2].token == "function" && output[i + 3].token == "defined" && output[i + 4].token == "for") {

			output[i] = { KEYWD, output[i].sentence, "be the function defined for" };
			output.erase(std::next(output.begin(), i + 1), std::next(output.begin(), i + 5));
			i -= 4;
		}
		if (i < output.size() - 2 && output[i].token == "and" && output[i + 1].token == "defined" && output[i + 2].token == "by") {
			output[i] = { KEYWD, output[i].sentence, "and defined by" };
			output.erase(std::next(output.begin(), i + 1), std::next(output.begin(), i + 3));
			i -= 2;
		}
	}

	for (lexer::Token token : output) {
		std::cout << token.token << " " << TYPES[token.type] << "\n";
	}
}